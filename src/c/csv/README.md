# 写个csv的解析器

## 「写个csv的解析器吧。」

也许是因为有闲，也许是因为有病。总之，要写个csv的解析器。正经地，写一个，优雅的。

我知道csv全称是comma-separated values。顾名思义，不难。有一个「一行」的计划已经蠢蠢欲动。

不急，先到世界上最大的同性交友平台上去看看。找到一个，不计测试代码，2000行。又找到一个，14000+。又找到一个，1200+。

对不起，是在下浅薄了。

## 先搞搞清楚需求

非常轻松就找到了rfc4180。讲「没有标准」、「很多实现」，给出了「大多数实现遵循的规则」：

``` abnf
file = [header CRLF] record *(CRLF record) [CRLF]
header = name *(COMMA name)
name = field
record = field *(COMMA field)
field = (escaped / non-escaped)
escaped = DQUOTE *(TEXTDATA / COMMA / CR / LF / 2DQUOTE) DQUOTE
non-escaped = *TEXTDATA
CR = %x0D
LF = %x0A
CRLF = CR LF
DQUOTE = %x22
COMMA = %x2C
TEXTDATA = %x20-21 / %x23-2B / %x2D-7E
```

这大概就是需求了。读到几个特别的：

 1. charset = 0x20-0x7E,CR,LF; 此为ASCII
 2. 行称record，字段称field而不是value
 3. file至少有一个record，record至少有一个field，而field可以是空字符串但不可以为空(null)
 4. 行结束符CR LF一定成对出现，但这两字符可以单独出现在field里。字段可以包含charset里字符构成的任意序列
 5. header语法与record相同

所以，csv是一个包装，它只规定包装的格式——所有的包装都理应如此。

一开始，csv只需要两种特殊字符：字段结束符和记录结束符。但由于这两种符号都可能存在于记录之中，于是需要第三种特殊符号来标记前两者的「转义」。此外还有通用的文件结束符。

### 提问？回答！

 1. 看起来是ascii文本。为什么tab不在其中？中文怎么办？
 2. csv的v不是v，那c是不是c？
 3. 如何判定首行是否是header？

rfc4180发布于2005年10月。世易时移，变法宜矣。基础输入应为Unicode字符流，至不济为字节流。应支持配置字段结束符。没办法自动判断首行是不是header；相较而言，假设没有header更合理。

至此，如果听说过CFG/PEG/LL(k)什么的，找工具跑个前端出来，基本就可以结束了。然而我什么都没听说过。

没关系，野修有野路子！

## 设计

设计api必须用到语言特性。语言的标准库是非常好的参考。

谨记。优雅的api很难误用。优雅的api自己就是文档。

注意，面向对象非常好用，也非常容易导致过度设计。抽象隐藏了细节，同时收紧了灵活、放松了性能要求。

很好。找到了合适的理由，就可以开心地用c语言了。

先从简单的开始。

### serialize()

``` c
// return numProduced
int serialize(byte * field, int i, int j, byte * dst, int start, boolean endsRecord);
```

一次写入一个record是比较符合直觉的。但是c语言的内存管理不太方便要求传入多个字符串。就按字段写罢。

输入和输出都是字节缓冲而不是任何形式的文件。文件处理比较繁琐又是旁枝，不宜在偏题处花费笔墨。字符缓冲也许很好，会浪费很多内存。

注意最后一个参数，没有给`byte separator`或者`int separatorType`，因为无法保证用户调用时给出的字段结束符是一致的。这意味着字段结束符和记录结束符内定。

「内定」有个说法。解析器两条线，低线是自己写的自己能读，高线是自己写的别人能读、别人写的自己也能读。这里，「内定」定的是「主流」，即字段结束符`,`，记录结束符`CR LF`。

返回写入的字节数，负值代表错误码。常见技巧。

另外，`NULL`值的`dst`用于指示dryrun行为，便于预分配足够的内存。

注意这个函数是幂等的，这非常重要。

顺便讲讲，在想不清怎么设计的时候，不妨期待一下用户如何使用。

``` c
for (int i = 0; i < record->size; i++) {
    field = record->fields[i];
    int dstSize = Csv_serialize(field->bytes, 0, field->size, dst, dstStart, i == record->numFields - 1);
    if (dstSize < 0) {
        // ... error
        break;
    }
    dstStart += dstSize;
}
```

### deserialize()

反序列化尤其要考虑清楚粒度。假如一次读入一个文件的话，用户需要写的代码固然很少；但如果文件比较大，就容易OOM。

``` c
// int deserialize(byte * src, byte * field);
```

这个函数不太可能设计得很优雅，因为它需要返回三个值：

- 成功时：读入的字节数，写入的字节数。
- 失败时：错误代码。

这三个值不正交，没办法表达在一个变量里。

这时候有几种选择：

 1. 定义结构`CsvDeserializeResult`。这带来另外的问题：
    1. 自行malloc传出。那么用户不free怎么办？
    2. 要求用户传入。
    3. 静态变量。需要考虑线程安全吗？
 2. 定义结构`CsvDeserializer`，内含读指针，相当于为输入流做了一个标记。要求用户传入。
 3. 定义用于输出的参数。
 4. 找个不在charset里的字节写在`field`的最后作为结束标志。需要用户自己再扫一遍。

还有，必须想清楚，此api要不要消耗分隔符。如果不消耗，那么需提供另一api完成此事。任何时候消耗分隔符，必须表明消耗掉的是字段结束还是记录结束。

没有满分，如何设计就取决于作者的审美。

我的选择是，保证幂等、可重入、提供成对的malloc/free，提供尽量少的api、引入尽量少的结构。

令deserialize()与serialize()「同构」：

- 处理分隔符
- 单api，无状态，保证所有的信息一致
- 用于输出的参数有明显标识

``` c
// return numProduced
int deserialize(byte * src, int i, int j, byte * field, int start,
        int * outNumConsumed, byte * outEndsRecord);
```

也写一个用法示例。

``` c
while (i < j) {
    int fieldSize = Csv_deserialize(src, i, j, NULL, 0, NULL, NULL);
    if (fieldSize < 0) {
        // ... error
        break;
    }
    byte * field = malloc(fieldSize);
    i += Csv_deserialize(src, i, j, field, 0, &numConsumed, &endsRecord);
    // ... do with field
    if (endsRecord) {
        break;
    }
}
```

## 实现

行为确定、边界清晰、参数明白，实现起来应该有如行云流水。要想外面正确呢，须定好用例、写好各种测试。要想里面漂亮呢，只需要一点：状态机。

``` c
int state = 0;
switch (state) {
    case 0:
        // read ch
        // do with ch and change state
        break;
    case 1:
        // ...
        break;
    // ...
}
```

要想更好一点，可以为复杂范式单独写状态机。

> 行云流水中

痛快！

## 后记

「写个csv的解析器吧。」

「好的。」

``` javascript
function f(line) {
    return line.split(',');
}
```

「。。。再见！」

我对很多面试者出过这个。虽然想像中的对话并没有发生，令人十分惋惜，但结果没有区别。

这道题不考编码也没有算法，它验的是厘定需求的本事和思维的完备。如果没想清楚，写一半回头来问需求，最后多半会败在某个用例上。还有api的设计——结果给哪些、怎么给，有哪些非法，吃多少内存——这些都不用问，一眼就看出来了。

我一直觉得io相关的题都是好题，看上去惊喜写起来恶心。算法之类，巧则巧矣，实际应用几近于无，屠龙之术也。反而，如何把弯弯绕绕的业务逻辑实现得简明圆润，是真见功力的。

不过现在呢，就连最简单的版本我也不问了：真心劝退。

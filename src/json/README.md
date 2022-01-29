# json

主要有两部分工作
  - Json及其派生类的关系
  - 与原生类型的转化

#### `IJson`

json.org规定了四种类型`object`/`array`/`string`/`number`和三个常量`true`/`false`/`null`，化为六种Json数据类型。它们必有一个共同抽象，记为`IJson`。

各`IJson`实例需要知道
  - 我实际上是谁
  - 我如何变成他

各Json数据类型的`set`方法须返回本实例，以允许`builder`风格的赋值

各`get`/`set`方法的签名须不同，以允许有all-in-one的Json数据类型的实现

#### `JsonCodec`

面向接口编程，因此需要`IJsonFactory`隔离Json数据类型的实现

需要静态类`JsonCodec`以封装`serialize()`/`deserialize()`方法

转化时以`IJson`作为中间变量 Json code <=> `IJson` <=> Java object

需要可配置的转化方法
  - 必有的属性
  - 默认值
  - 接口的对应实现类

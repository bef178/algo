# Interview Code Ask

Regular expression matching, limiting to '.' and '*'

Wildcard matching

两单链求交点
> 都无环时，必有共同的终点。各取链长，相减之，较长者前移。之后同时前进，等则为交点。
>
> 都有环时，分别求环，任取环中一点，必在另一环上。环入口即为交点。

环链求环入口
> 设链首为A，环入口为B。有快指针p步长为2、慢指针q步长为1，必相遇于环上，记为C。令a=AB，b=BC，环长为c。又当q至B时，p必然已在环上，两者距离小于环长；p每次追1，则追及时q不会再次经过B，意即q必不能绕环一周。因此p经过距离为a+b+kc；q经过距离为a+b；故a+b+kc=2(a+b)，即a=kc-b。即，若另有步长均为1的两指针，分别从A、C起始，将相遇于B。

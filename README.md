# muduo_source_read
开始时间  : 2016-8月-16日

muduo版本：1.0.1
源码地址：http://code.google.com/p/muduo/

linux内核版本 >= 2.6.28.


muduo源码的阅读和注释。

##2016-08-19 
Timestamp 时间类 (less_than_comparable 要求实现 < ，可自动实现 >,<=,>=,模板元编程思想)

##2016-08-21 Atomic
 原子整数类（原子操作函数）

##2016-08-22 
1.Exception 异常类(backstrace(获取堆栈) backtrace_symbols(将堆地址转化为函数名称) __cxa_demangle(解析混淆))

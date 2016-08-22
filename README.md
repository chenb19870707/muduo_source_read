# muduo_source_read
开始时间  : 2016-8月-16日

muduo版本：1.0.1
源码地址：http://code.google.com/p/muduo/

linux内核版本 >= 2.6.28.


muduo源码的阅读和注释。

##2016-08-19 
Timestamp 时间类 (less_than_comparable 要求实现 < ，可自动实现 >,<=,>=,模板元编程思想)

##2016-08-21 
Atomic 原子整数类（原子操作函数）

##2016-08-22 
  1.Exception 异常类(backstrace(获取堆栈) backtrace_symbols(将堆地址转化为函数名称) __cxa_demangle(解析混淆))  
  2.Thread 线程类  
  
  int nanosleep(const struct timespec *req, struct timespec *rem) 函数会导致当前的线程将暂停执行,直到rqtp参数所指定的时间间隔
  __thread gcc内置的线程局部存储设施  __thread 修饰的变量是线程内局部存储的，每个线程都有一份，不会共享 ，只能修饰POD类型：基本类型或指针
  
  int pthread_atfork(void (*prepare)(void), void (*parent)(void),void (*child)(void)); 调用fork之前在 父线程内调用prepare，调用fork之后，在子线程内调用child，在父线程内调用parent
  
  
    在Linux中，父进程在复制子进程的时候，只会复制当前线程的执行状态，其它线程不会复制，对于多线程程序来说，我们最好不要用fork,会引起死锁，比如当前线程的锁处于lock状态，fork时当前线程的锁会被拷贝为lock状态，fork之后当前线程会作为子进程的主线程，如果再次调用lock，当前进程将死锁，参考test/deadlock_test.cc
  
  int prctl ( int option,unsigned long arg2,unsigned long arg3,unsigned long arg4,unsigned long arg5 ) PR_SET_NAME :把参数arg2作为调用进程的经常名字

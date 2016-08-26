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
###1.Exception 异常类(backstrace(获取堆栈) backtrace_symbols(将堆地址转化为函数名称) __cxa_demangle(解析混淆))  
###2.Thread 线程类  
  
  int nanosleep(const struct timespec *req, struct timespec *rem) 函数会导致当前的线程将暂停执行,直到rqtp参数所指定的时间间隔
  __thread gcc内置的线程局部存储设施  __thread 修饰的变量是线程内局部存储的，每个线程都有一份，不会共享 ，只能修饰POD类型：基本类型或指针
  
  int pthread_atfork(void (*prepare)(void), void (*parent)(void),void (*child)(void)); 调用fork之前在 父线程内调用prepare，调用fork之后，在子线程内调用child，在父线程内调用parent
  
  
    在Linux中，父进程在复制子进程的时候，只会复制当前线程的执行状态，其它线程不会复制，对于多线程程序来说，我们最好不要用fork,会引起死锁，比如当前线程的锁处于lock状态，fork时当前线程的锁会被拷贝为lock状态，fork之后当前线程会作为子进程的主线程，如果再次调用lock，当前进程将死锁，参考test/deadlock_test.cc
  
  int prctl ( int option,unsigned long arg2,unsigned long arg3,unsigned long arg4,unsigned long arg5 ) PR_SET_NAME :把参数arg2作为调用进程的经常名字
##2016-08-24

###1.MutexLock类
pthread_mutex的类封装，构造函数调用pthread_mutex_init，析构函数pthread_mutex_destroy,加锁调用pthread_mutex_lock,解锁调用pthread_mutex_unlock  

###2.MutexLockGuard类
内有一个MutexLock的引用，由外部传入，不负责其生命周期，属于关联，构造函数调用lock，析构函数调用unlock

###3.Condition类 
临界区，对pthread_cond_t的封装，构造函数调用pthread_cond_init，析构函数调用pthread_cond_destroy，wait调用pthread_cond_wait，notify调用pthread_cond_signal，notifyAll调用pthread_cond_broadcast

###4.CountDownLatch
既可以用于所有子线程发起"起跑",子线程调用wait,主线程调用run  
也可以用于主线程等待子线程初始化完成才开始工作,主线程调用wait,子线程调用run

##2016-08-25
###1.BlockingQueue
无边界队列
###2.BoundedBlockingQueue
有边界队列

##2016-08-26
###1.Singleton类
typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];  
T_must_be_complete_type 完整类型  
class A;  
A  p  
delete p;  
A就是不完整的类型，sizeof(A) == 0  
这样 A[-1] 编译就会报错

pthread_once函数首先检查控制变量，判断是否已经完成初始化，如果完成就简单地返回；否则，pthread_once调用初始化函数，并且记录下初始化被完成。
 * 如果在一个线程初始时，另外的线程调用pthread_once，则调用线程等待，直到那个现成完成初始

  ::atexit(destroy);						//注册销毁函数        


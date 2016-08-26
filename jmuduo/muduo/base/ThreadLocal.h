// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_THREADLOCAL_H
#define MUDUO_BASE_THREADLOCAL_H

#include <muduo/base/Mutex.h>  // MCHECK

#include <boost/noncopyable.hpp>
#include <pthread.h>

/*
 * 1.在单线程程序中，我们经常要用到"全局变量"以实现多个函数间共享数据
 * 2.在多线程环境中，由于数据空间是共享的，因此全局变量也为所有线程共有
 * 3.但有时应用程序设计有必要提供线程私有的全局变量，仅在线程中有效，但可以跨多个函数访问
 * 4.POSIX 县城库通过维护一定的数据结构来解决这个问题，这个数据称为(Thread-specific Data,TSD)
 * 5.线程特定的数据也称为本地存储TLS(thread-local storage)
 * 6.对于POD类型的线程本地存储，可以用_thread关键字，非POD用TSD来解决
 *
 * phread操作TSD函数
 * pthread_key_create 创建线程私有数据，一旦创建，每个线程都有一个自己的这个key数据
 * pthread_key_delete
 * pthread_getspecific
 * pthread_setspecific
 *
 */

namespace muduo
{

template<typename T>
class ThreadLocal : boost::noncopyable
{
 public:
  ThreadLocal()
  {
    MCHECK(pthread_key_create(&pkey_, &ThreadLocal::destructor));
  }

  ~ThreadLocal()
  {
    MCHECK(pthread_key_delete(pkey_));
  }

  T& value()
  {
    T* perThreadValue = static_cast<T*>(pthread_getspecific(pkey_));
    if (!perThreadValue)
    {
      T* newObj = new T();
      MCHECK(pthread_setspecific(pkey_, newObj));
      perThreadValue = newObj;
    }
    return *perThreadValue;
  }

 private:

  static void destructor(void *x)
  {
    T* obj = static_cast<T*>(x);
    typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
    T_must_be_complete_type dummy; (void) dummy;
    delete obj;
  }

 private:
  pthread_key_t pkey_;
};

}
#endif

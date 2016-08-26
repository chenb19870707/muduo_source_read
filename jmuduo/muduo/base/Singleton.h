// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_SINGLETON_H
#define MUDUO_BASE_SINGLETON_H

#include <boost/noncopyable.hpp>
#include <assert.h>
#include <stdlib.h> // atexit
#include <pthread.h>

/*
 * pthread_once函数首先检查控制变量，判断是否已经完成初始化，如果完成就简单地返回；否则，pthread_once调用初始化函数，并且记录下初始化被完成。
 * 如果在一个线程初始时，另外的线程调用pthread_once，则调用线程等待，直到那个现成完成初始话返回。
 *
 * */

namespace muduo
{

namespace detail
{
// This doesn't detect inherited member functions!
// http://stackoverflow.com/questions/1966362/sfinae-to-check-for-inherited-member-functions
template<typename T>
struct has_no_destroy
{
  template <typename C> static char test(typeof(&C::no_destroy)); // or decltype in C++11
  template <typename C> static int32_t test(...);
  const static bool value = sizeof(test<T>(0)) == 1;
};
}

template<typename T>
class Singleton : boost::noncopyable
{
 public:
  static T& instance()
  {
    pthread_once(&ponce_, &Singleton::init);
    assert(value_ != NULL);
    return *value_;
  }

 private:
  Singleton();									//构造函数和析构函数都私有
  ~Singleton();

  static void init()
  {
    value_ = new T();
    if (!detail::has_no_destroy<T>::value)
    {
      ::atexit(destroy);						//注册销毁函数
    }
  }

  static void destroy()
  {
	/**
	 *
	 * typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
	 *
	 * T_must_be_complete_type 完整类型
	 * class A;
	 * A *p
	 * delete p;
	 *
	 * A就是不完整的类型，sizeof(A) == 0
	 * 这样 A[-1] 编译就会报错
	 *
	 */
    typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
    T_must_be_complete_type dummy; (void) dummy;

    delete value_;
    value_ = NULL;
  }

 private:
  static pthread_once_t ponce_;
  static T*             value_;
};

template<typename T>
pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

template<typename T>
T* Singleton<T>::value_ = NULL;

}
#endif


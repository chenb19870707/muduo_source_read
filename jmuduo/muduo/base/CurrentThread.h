// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_CURRENTTHREAD_H
#define MUDUO_BASE_CURRENTTHREAD_H

#include <stdint.h>

namespace muduo
{
namespace CurrentThread
{
  // internal
  extern __thread int t_cachedTid;
  extern __thread char t_tidString[32];
  extern __thread int t_tidStringLength;
  extern __thread const char* t_threadName;
  void cacheTid();

  inline int tid()
  {
	 /**
	  *  __builtin_expect() �� GCC (version >= 2.96���ṩ������Աʹ�õģ�Ŀ���ǽ�����֧ת�ơ�����Ϣ�ṩ�����������������������ԶԴ�������Ż����Լ���ָ����ת�����������½���
	  *  __builtin_expect((x),1) ��ʾ x ��ֵΪ��Ŀ����Ը���
	  *  __builtin_expect((x),0) ��ʾ x ��ֵΪ�ٵĿ����Ը���
	  */
    if (__builtin_expect(t_cachedTid == 0, 0))
    {
      cacheTid();
    }
    return t_cachedTid;
  }

  inline const char* tidString() // for logging
  {
    return t_tidString;
  }

  inline int tidStringLength() // for logging
  {
    return t_tidStringLength;
  }

  inline const char* name()
  {
    return t_threadName;
  }

  bool isMainThread();

  void sleepUsec(int64_t usec);
}
}

#endif

// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)

#include <muduo/base/Logging.h>
#include <muduo/net/Channel.h>
#include <muduo/net/EventLoop.h>

#include <sstream>

#include <poll.h>

using namespace muduo;
using namespace muduo::net;

/*
    EPOLL 和 POLLIN 定义值相同，所以可以定义kNoneEvent，kReadEvent，kWriteEvent
    EPOLLIN = 0x001,EPOLLPRI = 0x002,EPOLLOUT = 0x004,
    #define POLLIN          0x001          There is data to read.
	#define POLLPRI         0x002          There is urgent data to read.
	#define POLLOUT         0x004           Writing now will not block.
**/

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(EventLoop* loop, int fd__)
  : loop_(loop),
    fd_(fd__),
    events_(0),
    revents_(0),
    index_(-1),
    logHup_(true),
    tied_(false),
    eventHandling_(false)
{
}

Channel::~Channel()
{
  assert(!eventHandling_);
}

void Channel::tie(const boost::shared_ptr<void>& obj)
{
  tie_ = obj;
  tied_ = true;
}

void Channel::update()
{
  loop_->updateChannel(this);
}

// 调用这个函数之前确保调用disableAll
void Channel::remove()
{
  assert(isNoneEvent());
  loop_->removeChannel(this);
}

void Channel::handleEvent(Timestamp receiveTime)
{
  boost::shared_ptr<void> guard;
  if (tied_)
  {
    guard = tie_.lock();
    if (guard)
    {
      LOG_TRACE << "[6] usecount=" << guard.use_count();
      handleEventWithGuard(receiveTime);
	  LOG_TRACE << "[12] usecount=" << guard.use_count();
    }
  }
  else
  {
    handleEventWithGuard(receiveTime);
  }
}

void Channel::handleEventWithGuard(Timestamp receiveTime)
{
  eventHandling_ = true;
  //POLLHUP  指定的文件描述符挂起事件。Hang up.output only，读的时间不会产生
  if ((revents_ & POLLHUP) && !(revents_ & POLLIN))
  {
    if (logHup_)
    {
      LOG_WARN << "Channel::handle_event() POLLHUP";
    }
    if (closeCallback_) closeCallback_();
  }

  //POLLNVAL fd not open
  if (revents_ & POLLNVAL)
  {
    LOG_WARN << "Channel::handle_event() POLLNVAL";
  }

  //错误
  if (revents_ & (POLLERR | POLLNVAL))
  {
    if (errorCallback_) errorCallback_();
  }

  //POLLRDHUP 对端关闭连接
  if (revents_ & (POLLIN | POLLPRI | POLLRDHUP))
  {
    if (readCallback_) readCallback_(receiveTime);
  }

  //可写事件
  if (revents_ & POLLOUT)
  {
    if (writeCallback_) writeCallback_();
  }
  eventHandling_ = false;
}

string Channel::reventsToString() const
{
  std::ostringstream oss;
  oss << fd_ << ": ";
  if (revents_ & POLLIN)
    oss << "IN ";
  if (revents_ & POLLPRI)
    oss << "PRI ";
  if (revents_ & POLLOUT)
    oss << "OUT ";
  if (revents_ & POLLHUP)
    oss << "HUP ";
  if (revents_ & POLLRDHUP)
    oss << "RDHUP ";
  if (revents_ & POLLERR)
    oss << "ERR ";
  if (revents_ & POLLNVAL)
    oss << "NVAL ";

  return oss.str().c_str();
}

add_executable(timestamp_unittest Timestamp_unittest.cc)
target_link_libraries(timestamp_unittest muduo_base)
add_test(NAME timestamp_unittest COMMAND timestamp_unittest)

add_executable(atomic_unittest Atomic_unittest.cc)
target_link_libraries(atomic_unittest muduo_base)
add_test(NAME atomic_unittest COMMAND atomic_unittest)

add_executable(exception_test Exception_test.cc)
target_link_libraries(exception_test muduo_base)
add_test(NAME exception_test COMMAND exception_test)

add_executable(thread_test Thread_test.cc)
target_link_libraries(thread_test muduo_base)
add_test(NAME thread_test COMMAND thread_test)

add_executable(mutex_test Mutex_test.cc)
target_link_libraries(mutex_test muduo_base)
add_test(NAME mutex_test COMMAND mutex_test)

add_executable(blockingQueue_test BlockingQueue_test.cc)
target_link_libraries(blockingQueue_test muduo_base)
add_test(NAME blockingQueue_test COMMAND blockingQueue_test)

add_executable(blockingqueue_bench BlockingQueue_bench.cc)
target_link_libraries(blockingqueue_bench muduo_base)
add_test(NAME blockingqueue_bench COMMAND blockingqueue_bench)

add_executable(boundedblockingqueue_test BoundedBlockingQueue_test.cc)
target_link_libraries(boundedblockingqueue_test muduo_base)
add_test(NAME boundedblockingqueue_test COMMAND boundedblockingqueue_test)

add_executable(threadpool_test ThreadPool_test.cc)
target_link_libraries(threadpool_test muduo_base)
add_test(NAME threadpool_test COMMAND threadpool_test)

add_executable(singleton_test Singleton_test.cc)
target_link_libraries(singleton_test muduo_base)
add_test(NAME singleton_test COMMAND singleton_test)

add_executable(threadlocal_test ThreadLocal_test.cc)
target_link_libraries(threadlocal_test muduo_base)
add_test(NAME threadlocal_test COMMAND threadlocal_test)

add_executable(singletonthreadlocal_test SingletonThreadLocal_test.cc)
target_link_libraries(singletonthreadlocal_test muduo_base)
add_test(NAME singletonthreadlocal_test COMMAND singletonthreadlocal_test)


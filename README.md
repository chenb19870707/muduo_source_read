# muduo_source_read
��ʼʱ��  : 2016-8��-16��

muduo�汾��1.0.1
Դ���ַ��http://code.google.com/p/muduo/

linux�ں˰汾 >= 2.6.28.


muduoԴ����Ķ���ע�͡�

##2016-08-19 
Timestamp ʱ���� (less_than_comparable Ҫ��ʵ�� < �����Զ�ʵ�� >,<=,>=,ģ��Ԫ���˼��)

##2016-08-21 
Atomic ԭ�������ࣨԭ�Ӳ���������

##2016-08-22 
  1.Exception �쳣��(backstrace(��ȡ��ջ) backtrace_symbols(���ѵ�ַת��Ϊ��������) __cxa_demangle(��������))  
  2.Thread �߳���  
  
  int nanosleep(const struct timespec *req, struct timespec *rem) �����ᵼ�µ�ǰ���߳̽���ִͣ��,ֱ��rqtp������ָ����ʱ����
  __thread gcc���õ��ֲ߳̾��洢��ʩ  __thread ���εı������߳��ھֲ��洢�ģ�ÿ���̶߳���һ�ݣ����Ṳ�� ��ֻ������POD���ͣ��������ͻ�ָ��
  
  int pthread_atfork(void (*prepare)(void), void (*parent)(void),void (*child)(void)); ����fork֮ǰ�� ���߳��ڵ���prepare������fork֮�������߳��ڵ���child���ڸ��߳��ڵ���parent
  
  
    ��Linux�У��������ڸ����ӽ��̵�ʱ��ֻ�Ḵ�Ƶ�ǰ�̵߳�ִ��״̬�������̲߳��Ḵ�ƣ����ڶ��̳߳�����˵��������ò�Ҫ��fork,���������������統ǰ�̵߳�������lock״̬��forkʱ��ǰ�̵߳����ᱻ����Ϊlock״̬��fork֮��ǰ�̻߳���Ϊ�ӽ��̵����̣߳�����ٴε���lock����ǰ���̽��������ο�test/deadlock_test.cc
  
  int prctl ( int option,unsigned long arg2,unsigned long arg3,unsigned long arg4,unsigned long arg5 ) PR_SET_NAME :�Ѳ���arg2��Ϊ���ý��̵ľ�������

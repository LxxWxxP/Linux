#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>//pthread_self()
#include <unistd.h>
#include <iostream>
using namespace std;
void * tfn(void * arg)
{
	cout << "tfn--pid=" << getpid() << ",tid=" << pthread_self() << endl;//��ȡ����ip���߳�ip 
	return (void *)0;
}
int main()
{
	pthread_t tid;
	cout << "main--pid" << getpid() << ",tid=" << pthread_self() << endl;
	int ret=pthread_create(&tid,NULL,tfn,NULL); //�����߳�(�߳�id,�߳�����,�������߳�����,�����߳�ִ�к����Ĳ���)
	if(ret!=0)
	{
	//	fprintf(stderr,"pthread_create error:%s\n",strerror(ret));
		exit(1);
	}
	sleep(1);
	return 0;
}

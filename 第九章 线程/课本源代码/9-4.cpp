#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
void * tfn(void *arg)
{
	while(1)
	{
		cout << "child thread..." << endl;
		pthread_testcancel();                   //pthread_testcancel()���ڴ���ȡ���� 
	}
}
int main()
{
	pthread_t tid;
	void * tret=NULL;
	pthread_create(&tid,NULL,tfn,NULL);   //�����߳�tid 
	sleep(1);
	pthread_cancel(tid);        //ɱ���߳�tid
	pthread_join(tid,&tret);    //���𲢵ȴ��߳�tid����
	cout << "child thread exit code=" << (long int)tret << endl;
	return 0; 
}

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
		pthread_testcancel();                   //pthread_testcancel()用于创造取消点 
	}
}
int main()
{
	pthread_t tid;
	void * tret=NULL;
	pthread_create(&tid,NULL,tfn,NULL);   //创建线程tid 
	sleep(1);
	pthread_cancel(tid);        //杀死线程tid
	pthread_join(tid,&tret);    //挂起并等待线程tid结束
	cout << "child thread exit code=" << (long int)tret << endl;
	return 0; 
}

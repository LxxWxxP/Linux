#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
void * tfn(void * arg)
{
	long int i;
	i=(long int)arg;   //��void *���͵�argǿ��ת��Ϊlong int����
	if(i==2)
		pthread_exit(NULL);
	sleep(i);          //ͨ��i������ÿһ���߳� 
	cout << "I'm " << i+1 << "th thread, Thread_ID=" << pthread_self() << endl;
	return NULL;
}
int main(int argc, char * argv[])
{
	long int n=5,i;    //��������5���̵߳ģ�����ɾ��һ��ֻʣ��4�� 
	pthread_t tid;
	if(argc==2)        //�� 
		n=atoi(argv[1]);   //�� 
	for(i=0;i<n;i++)
		pthread_create(&tid,NULL,tfn,(void *)i);//��iת��Ϊ(void *)ָ�룬����tfn��ת�������� 
	sleep(n);
	cout << "I am main, I'm a thread!" << endl << "main_thread_ID=" << pthread_self() << endl;
	return 0;
}

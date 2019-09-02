#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
pthread_mutex_t m;
void err_thread(int ret, char * str)
{
	if (ret!=0)
	{
		fprintf(stderr,"%s:%s\n",str,strerror(ret));
		pthread_exit(NULL);
	}
}
void * tfn(void * arg)
{
	srand(time(NULL));
	while(1)
	{
		pthread_mutex_lock(&m);       //����:m-- 
		printf("hello ");
		//ģ�ⳤʱ�����������Դ������CPU������������ʱ���йصĴ���
		sleep(rand()%3);
		printf("world\n");
		pthread_mutex_unlock(&m);    //����:m++ 
		sleep(rand()%3); 
	}
	return NULL;
}
int main()
{
	pthread_t tid;
	srand(time(NULL));
	int flag=5;
	pthread_mutex_init(&m,NULL);//��ʼ��mutex:m=1
	int ret=pthread_create(&tid,NULL,tfn,NULL);//�����߳�tid������ret 
	err_thread(ret,"pthread_create error");//�ж��߳��Ƿ񴴽�ʧ�� 
	while(flag--)
	{
		pthread_mutex_lock(&m);   //����:m-- 
		printf("HELLO ");
		sleep(rand()%3);
		printf("WORLD\n");
		pthread_mutex_unlock(&m); //����:m++ 
		sleep(rand()%3);
	} 
	pthread_cancel(tid);          //ɱ���߳� 
	pthread_join(tid,NULL);       //�����߳� 
	pthread_mutex_destroy(&m);    //����������Դ 
		
}

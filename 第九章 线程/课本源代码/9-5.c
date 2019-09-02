#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
typedef struct 
{
	int a;
	int b;
}exit_t;
void * tfn(void * arg)
{
	exit_t * ret;
	ret=malloc(sizeof(exit_t));           //Ϊret��̬�����ڴ� 
	ret->a=100;
	ret->b=300;
	pthread_exit((void *)ret);            //�߳���ֹ
	return NULL;                          //�̷߳��� 
}
int main(void)
{
	pthread_t tid;
	exit_t * retval;                      //�߳���ֹ�������� 
	pthread_create(&tid,NULL,tfn,NULL);   //�����߳� 
	pthread_join(tid,(void **)&retval);   //����pthread_join���Ի�ȡ�̵߳��˳�״̬
	printf("a=%d, b=%d\n",retval->a,retval->b);
	return 0; 
}

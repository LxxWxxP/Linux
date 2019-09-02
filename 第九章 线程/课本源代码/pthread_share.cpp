#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>//srand()rand()
void * tfn(void * arg)
{
	srand(time(NULL));
	while(1)
	{
		printf("hello ");
		sleep(rand()%3);    //模拟长时间操作共享资源，导致CPU易主，产生与时间有关的错误 
		printf("world\n");
		sleep(rand()%3);
	}
	return NULL;
}
int main(void)
{
	pthread_t tid;
	srand(time(NULL));
	pthread_create(&tid,NULL,tfn,NULL);
	while(1)
	{
		printf("HELLO ");
		sleep(rand()%3);
		printf("WORLD\n");
		sleep(rand()%3);
	}
	pthread_join(tid,NULL);
	return 0;
}

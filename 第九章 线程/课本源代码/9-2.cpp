#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
using namespace std;
int var=100;
void * tfn(void * arg)
{
	var=200;
	printf("thread\n");
	return NULL;	
} 
int main()
{
	cout << "At first var=" << var << endl;
	pthread_t tid;
	pthread_create(&tid,NULL,tfn,NULL);
	sleep(1);
	cout << "after pthread_create, var=" << var << endl;
	return 0;
}

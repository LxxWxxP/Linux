#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
void * tfn(void * arg)
{
	long int i;
	i=(long int)arg;   //将void *类型的arg强制转换为long int类型
	if(i==2)
		pthread_exit(NULL);
	sleep(i);          //通过i来区别每一个线程 
	cout << "I'm " << i+1 << "th thread, Thread_ID=" << pthread_self() << endl;
	return NULL;
}
int main(int argc, char * argv[])
{
	long int n=5,i;    //本来创建5个线程的，但是删除一个只剩下4个 
	pthread_t tid;
	if(argc==2)        //？ 
		n=atoi(argv[1]);   //？ 
	for(i=0;i<n;i++)
		pthread_create(&tid,NULL,tfn,(void *)i);//将i转换为(void *)指针，再在tfn中转换回整型 
	sleep(n);
	cout << "I am main, I'm a thread!" << endl << "main_thread_ID=" << pthread_self() << endl;
	return 0;
}

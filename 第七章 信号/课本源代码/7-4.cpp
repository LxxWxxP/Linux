#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
void printset(sigset_t * ped)
{
	int i;
	for(i=1;i<32;i++)
	{
		if(sigismember(ped,i)==1)   //判断信号是否加入指定信号集 
			putchar('1');
		else
			putchar('0');
	}
	printf("\n");
}

int main()
{
	sigset_t set,oldset,ped;
	sigemptyset(&set);   //初始化自定义信号集set
	sigaddset(&set,SIGINT);    //将2号信号SIGINT加入信号集set
	sigprocmask(SIG_BLOCK,&set,&oldset);    //位操作 
	while(1)
	{
		sigpending(&ped);
		printset(&ped);
		sleep(1);
	} 
	return 0;
}

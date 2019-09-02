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
		if(sigismember(ped,i)==1)   //�ж��ź��Ƿ����ָ���źż� 
			putchar('1');
		else
			putchar('0');
	}
	printf("\n");
}

int main()
{
	sigset_t set,oldset,ped;
	sigemptyset(&set);   //��ʼ���Զ����źż�set
	sigaddset(&set,SIGINT);    //��2���ź�SIGINT�����źż�set
	sigprocmask(SIG_BLOCK,&set,&oldset);    //λ���� 
	while(1)
	{
		sigpending(&ped);
		printset(&ped);
		sleep(1);
	} 
	return 0;
}

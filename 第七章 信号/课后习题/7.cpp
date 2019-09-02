#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
int n = 0, flag = 0;
void sys_err(char *str)
{
	perror(str);
	exit(1);
}
void do_sig_child(int num)
{
	printf("I am child  %d\t%d\n", getpid(), n);
	n += 2;
	flag = 1;
	sleep(1);
}
void do_sig_parent(int num)
{
	printf("I am parent %d\t%d\n", getpid(), n);
	n += 2;
	flag = 1;
	sleep(1);
}
int main(void)
{
	pid_t pid;
	struct sigaction act;
	if ((pid = fork()) < 0)
		sys_err("fork");
	else if (pid > 0) 
	{
		n = 1;
		sleep(1);
		act.sa_handler = do_sig_parent;
		sigemptyset(&act.sa_mask);
		act.sa_flags = 0;
		//ע���Լ����źŲ�׽��������ʹ��SIGUSR2�ź�
		sigaction(SIGUSR2, &act, NULL);
		do_sig_parent(0);
		while (1) {
			/* wait for signal */;
			if (flag == 1) {          //�������������
				kill(pid, SIGUSR1);
				flag = 0;             //��־�Ѿ����ӽ��̷������ź�
			}
		}
	}
	else if (pid == 0) 
	{
		n = 2;
		act.sa_handler = do_sig_child;
		sigemptyset(&act.sa_mask);
		act.sa_flags = 0;
		sigaction(SIGUSR1, &act, NULL);
		while (1) 
		{
			//�ȴ��ź�
			if (flag == 1) 
			{
				kill(getppid(), SIGUSR2);
				flag = 0;
			}
		}
	}
	return 0;
}

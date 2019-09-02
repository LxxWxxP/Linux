#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
void sig_int(int signo)
{
	printf("..........catch you, SIGINT\n");
	signal(SIGINT,SIG_DFL);
}
int main()
{
	signal(SIGINT,sig_int);
	while(1);
	return 0;
}

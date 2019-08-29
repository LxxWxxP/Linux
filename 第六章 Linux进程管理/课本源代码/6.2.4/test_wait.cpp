#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main()
{
	pid_t pid,w;
	pid=fork();
	if(pid==-1)
	{
		perror("fork error!");
		exit(1);
	}
	else if(pid==0)
	{
		sleep(3);
		cout << "Child process:pid=" << getpid() << endl;
	}
	else if(pid>0)
	{
		w=wait(NULL);
		cout << "Catched a child process,pid=" << w << endl;
	}
	return 0;
}

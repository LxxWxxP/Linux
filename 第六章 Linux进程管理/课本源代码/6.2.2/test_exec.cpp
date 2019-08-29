#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

int main()
{
	pid_t pid;
	pid=fork();
	if(pid==-1)
	{
		cout << "fork error!" << endl;
		exit(1);
	}
	else if(pid>0)
		cout << "parent process:pid=" << getpid() << endl;
	else if(pid==0)
	{
		cout << "child process:pid=" << getpid() << endl;
		//exel("/bin/ls","-a","-l","test_fork.cpp",NULL);
		//execlp("ls","-a","-l","test_fork.cpp",NULL);
		char * arg[]={"-a","-l","test_fork.cpp",NULL};
		execvp("ls",arg);
		perror("error exec\n");
		cout << "child process:pid=" << getpid() << endl;
		return 0;
	}
}

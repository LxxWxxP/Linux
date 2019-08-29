#include <iostream>
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
		cout << "parent process,pid=" << getpid() << ",ppid=" << getppid() << endl;
	else if(pid==0)
		cout << "child process,pid=" << getpdi() << ",ppid=" << getppid() << endl;
	cout << "-----finish-----" << endl;
	return 0;
} 

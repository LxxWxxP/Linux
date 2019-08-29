#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;

int main()
{
	pid_t pid,p,w;
	pid=fork();
	if(pid==-1)
	{
		perror("fork1 error");
		exit(1);
	}
	else if(pid==0)
	{
		sleep(5);
		cout << "First child process:pid=" << getpid() << endl;
	}
	else if(pid>0)
	{
		int i;
		p=pid;
		for(i=0;i<3;i++)
		{
			if((pid=fork())==0)
				break;	
		}	
		if(pid==-1)
		{
			perror("fork error");
			exit(2);
		}
		else if(pid==0)
		{
			cout << "Child process:pid=" << getpid() << endl;
			exit(0);
		}
		else if(pid>0)
		{
			w=waitpid(p,NULL,0);
			if(w==p)
				cout << "Catch a child Process:pid=" << w << endl;
			else
				cout << "waitpid error" << endl;
		}
	} 
	return 0;
}

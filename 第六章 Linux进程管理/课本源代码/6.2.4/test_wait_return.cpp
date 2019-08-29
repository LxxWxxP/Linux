#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main()
{
	int status;
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
		exit(5);
	}
	else if(pid>0)
	{
		w=wait(&status);
		if(WIFEXITED(status))
		{
			cout << "Child process pid=" << w << " exit normally." << endl;
			cout << "Return code:" << WEXITSTATUS(status) << endl;
		}
		else
			cout << "Child process pid=" << w << " exit abnormally." << endl;
	}
	return 0;
}

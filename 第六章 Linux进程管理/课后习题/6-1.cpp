#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main()
{
	pid_t pid;
	pid=fork();
	if(pid==-1)
	{
		perror("fork error");
		exit(1);
	}
	else if(pid==0)
	{
		cout << "Child fork is created!" << endl;
	}
	else if(pid>0)
	{
		cout << "Parent fork is created!" << endl;
	}
	return 0;
}

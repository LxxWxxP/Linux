#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
	pid_t pid;
	int i;
	for(i=0;i<5;i++)
	{
		if((pid=fork())==0)
			break;	
	}	
	if(pid==-1)
	{
		cout << "fork error!" << endl;
		exit(1);
	}
	else if(pid>0)
		cout << "parent process:pid=" << getpid() << endl;
	else if(pid==0)
		cout << "I am child=" << i+1 << ",pid=" << getpid() << endl;
	return 0;
} 

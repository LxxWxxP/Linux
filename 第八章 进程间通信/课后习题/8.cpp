#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
int main()
{
	pid_t pid;
	string str="--something from child--\n";
	pid=fork();
	if(pid<0)
	{
		perror("fork error");
		exit(1);
	}
	else if(pid==0)
	{
		ofstream fd1("test.txt",ios::app);
		if(!fd1)
		{
			perror("open error");
			exit(1);
		}
		fd1 << str;
		fd1.close();
		cout << "child wrote over..." << endl;
	}
	else
	{
		ifstream fd2("test.txt");
		if(!fd2)
		{
			perror("open error");
			exit(1);
		}
		sleep(2);
		string s;
		getline(fd2,s);       //s里面有空格，如果用cin的话会值大一something而不大一空格后面的string，所以这里用getline(输入流,接收的字符串) 
		cout << s << endl;
		wait(NULL);
	}
	return 0;
}

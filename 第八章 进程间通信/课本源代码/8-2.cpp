#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> //这里为了后面wait用的，但是不知道为什么前面几个代码也不需要include这个也可以用wait()，例如example2.c 
int main()
{
	int fd[2];
	int ret=pipe(fd);
	if(ret==-1)
	{
		perror("pipe err");
		exit(1);
	}
	int i;
	pid_t pid,wpid;
	for(i=0;i<2;i++)
	{
		if((pid=fork())==0)
			break;
	}
	if(2==i)   //父进程 
	{
		close(fd[0]);   //关闭读端
		close(fd[1]);   //关闭写端 
		wpid=wait(NULL);    //等子进程1
		printf("wait child 1 success,pid=%d\n",wpid);
		pid=wait(NULL);     //等子进程2 
		printf("wait child 2 success,pid=%d\n",pid);
	}
	else if(i==0)   //子进程-写 
	{
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);  //将fd[1]所指文件内容定向到标准输出,重定向函数dup2()存在于unistd.h 
		execlp("ls","ls",NULL);     //不懂什么意思？这个函数经常用，但是还是不懂什么意思？ 
	}
	else if(i==0)
	{
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		execlp("wc","wc","-1",NULL);
	}
	return 0;
}
//本代码还没有完善，以待以后多修正 

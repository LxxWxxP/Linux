#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> //����Ϊ�˺���wait�õģ����ǲ�֪��Ϊʲôǰ�漸������Ҳ����Ҫinclude���Ҳ������wait()������example2.c 
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
	if(2==i)   //������ 
	{
		close(fd[0]);   //�رն���
		close(fd[1]);   //�ر�д�� 
		wpid=wait(NULL);    //���ӽ���1
		printf("wait child 1 success,pid=%d\n",wpid);
		pid=wait(NULL);     //���ӽ���2 
		printf("wait child 2 success,pid=%d\n",pid);
	}
	else if(i==0)   //�ӽ���-д 
	{
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);  //��fd[1]��ָ�ļ����ݶ��򵽱�׼���,�ض�����dup2()������unistd.h 
		execlp("ls","ls",NULL);     //����ʲô��˼��������������ã����ǻ��ǲ���ʲô��˼�� 
	}
	else if(i==0)
	{
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		execlp("wc","wc","-1",NULL);
	}
	return 0;
}
//�����뻹û�����ƣ��Դ��Ժ������ 

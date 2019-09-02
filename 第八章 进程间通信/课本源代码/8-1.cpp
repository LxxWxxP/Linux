#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
	int fd[2];       //�����ļ����������� 
	int ret=pipe(fd);   //unistd.h �����ܵ� 
	if(ret==-1)
	{
		perror("pipe");
		exit(1);
	}
	pid_t pid=fork();
	if(pid>0)   //������-д 
	{
		close(fd[0]);  //�رն��� fd[0]
		char * p="hello,pipe\n";
		write(fd[1],p,strlen(p)+1); 
		close(fd[1]);
		wait(NULL); //����ʲô��˼ 
	}
	else if(pid==0)  //�ӽ���-�� 
	{
		close(fd[1]);  //�ر�д�� 
		char buf[64]={0};
		ret=read(fd[0],buf,sizeof(buf));  //��fd[0]����buf����ȥ��ret�Ƿ���ֵ����СΪ���Ȱɣ� 
		close(fd[0]);
		write(STDOUT_FILENO,buf,ret); //������������д����׼��� 
	}
	return 0; 
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc,char * argv[])
{
	if(argc<2)
	{
		printf("./a.out fifoname\n");
		exit(1);
	}
	int ret=access(argv[1],F_OK);               //判断文件是否存在 
	if(ret==-1)                                 //若不存在则创建文件 
	{ 
		int r=mkfifo(argv[1],0664);
		if(r==-1)
		{
			perror("mkfifo");
			exit(1);	
		} 
		else
			printf("fifo creat success!\n");
	}
	int fd=open(argv[1],O_RDONLY);
	if(fd==-1)
	{
		perror("open");
		exit(1);
	}
	while(1)
	{
		char buf[1024]={0};
		read(fd,buf,sizeof(buf));      //通过文件指针读出到buf里面去 
		printf("buf=%s\n",buf);
	}
	close(fd);
	return 0;
}

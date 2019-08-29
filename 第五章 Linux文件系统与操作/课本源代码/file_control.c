#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>//exit()
#include <sys/stat.h>//stat()

int main()
{
	struct stat sbuf;//sbuf用于接收文件属性 
	int ret=2;//stat调用成功的时候返回0，否则返回-1 
	ret=stat("a.out",&sbuf);
	if(ret==-1)
	{
		perror("stat error:");
		exit(1);
	}
	printf("len=%ld\n",sbuf.st_size);
	return 0;
}

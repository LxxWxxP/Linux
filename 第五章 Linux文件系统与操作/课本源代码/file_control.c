#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>//exit()
#include <sys/stat.h>//stat()

int main()
{
	struct stat sbuf;//sbuf���ڽ����ļ����� 
	int ret=2;//stat���óɹ���ʱ�򷵻�0�����򷵻�-1 
	ret=stat("a.out",&sbuf);
	if(ret==-1)
	{
		perror("stat error:");
		exit(1);
	}
	printf("len=%ld\n",sbuf.st_size);
	return 0;
}

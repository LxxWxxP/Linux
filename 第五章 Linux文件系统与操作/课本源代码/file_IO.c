#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   //write() read()
#include <fcntl.h>    //open() 
#include <string.h>

int main()
{
	int fd=0;
	char filename[20]="/home/itheima/a.txt"; //路径中的目录若不存在将导致文件创建失败
	fd=open(filename,O_RDWR|O_EXCL|O_TRUNC,S_IRWXG);   //读写|不存在则创建|将文件截断为0，文件所属组对该文件有读、写和执行的权限 
	if(fd==-1)  //判断文件是否成功打开 
	{
		perror("file open error.\n");
		exit(-1);
	} 
	int len=0;
	char buf[100]={0};
	scanf("%s",buf);
	len=strlen(buf);
	write(fd,buf,len);  //写文件，将输入的字符串由buf通过文件指针fd写入a.txt中
	close(fd);
	printf("-----------------------------------\n");
	
	//读取文件
	fd=open(filename,O_RDONLY);   //只读
	if(fd==-1)
	{
		perror("file open error.\n");
		exit(-1);
	} 
	off_t f_size=0;
	f_size=lseek(fd,0,SEEK_END);//获取文件长度(0,SEEK_END)
	lseek(fd,0,SEEK_SET);//设置文件读写位置为文件的开头
	while(lseek(fd,0,SEEK_CUR)!=f_size)   //如果指针没有达到末尾
	{
		read(fd,buf,1024);//从文件指针中读到buf里面去
		printf("%s\n",buf);
	}
	close(fd);
	return 0;
} 

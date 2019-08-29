#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   //write() read()
#include <fcntl.h>    //open() 
#include <string.h>

int main()
{
	int fd=0;
	char filename[20]="/home/itheima/a.txt"; //·���е�Ŀ¼�������ڽ������ļ�����ʧ��
	fd=open(filename,O_RDWR|O_EXCL|O_TRUNC,S_IRWXG);   //��д|�������򴴽�|���ļ��ض�Ϊ0���ļ�������Ը��ļ��ж���д��ִ�е�Ȩ�� 
	if(fd==-1)  //�ж��ļ��Ƿ�ɹ��� 
	{
		perror("file open error.\n");
		exit(-1);
	} 
	int len=0;
	char buf[100]={0};
	scanf("%s",buf);
	len=strlen(buf);
	write(fd,buf,len);  //д�ļ�����������ַ�����bufͨ���ļ�ָ��fdд��a.txt��
	close(fd);
	printf("-----------------------------------\n");
	
	//��ȡ�ļ�
	fd=open(filename,O_RDONLY);   //ֻ��
	if(fd==-1)
	{
		perror("file open error.\n");
		exit(-1);
	} 
	off_t f_size=0;
	f_size=lseek(fd,0,SEEK_END);//��ȡ�ļ�����(0,SEEK_END)
	lseek(fd,0,SEEK_SET);//�����ļ���дλ��Ϊ�ļ��Ŀ�ͷ
	while(lseek(fd,0,SEEK_CUR)!=f_size)   //���ָ��û�дﵽĩβ
	{
		read(fd,buf,1024);//���ļ�ָ���ж���buf����ȥ
		printf("%s\n",buf);
	}
	close(fd);
	return 0;
} 

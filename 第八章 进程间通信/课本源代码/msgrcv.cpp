#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#define MAX_TEXT 512
struct my_msg_st
{
	long int my_msg_type;
	char anytext[MAX_TEXT];
};
int main()
{
	int idx=1;
	int msqid;
	struct my_msg_st data;
	long int msg_to_rcv=0;  //rcv=recieve
	//rcv mes
	msqid=msgget((key_t)1000,0664|IPC_CREAT);//获取消息队列
	if(msqid==-1)
	{
		perror("msgget err");
		exit(-1);	
	} 
	while(idx<5)   
	{
		//接收信息 
		if(msgrcv(msqid,(void *)&data,BUFSIZ,msg_to_rcv,0)==-1)  //接收的信息在data里面 
		{
			perror("msgrcv err");
			exit(-1);
		}
		//打印信息
		printf("msg type:%ld\n",data.my_msg_type);
		printf("msg content is:%s",data.anytext);
		idx++; 
	}
	//删除消息队列
	if(msgctl(msqid,IPC_RMID,0)==-1)
	{
		perror("msgctl err");
		exit(-1);	
	} 
	return 0;
}

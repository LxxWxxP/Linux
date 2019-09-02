#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>//msgget()
#include <string.h>
#define MAX_TEXT 512
//消息结构体 
struct my_msg_st
{
	long int my_msg_type;        //消息类型
	char anytext[MAX_TEXT]; 
};
int main()
{
	int idx=1;    //循环次数 
	int msqid;    //消息队列标识符 
	struct my_msg_st data;  //创建消息data 
	char buf[BUFSIZ];       //设置缓存变量,BUFSIZ在stdio.h 里面 
	msqid=msgget((key_t)1000,0664|IPC_CREAT);//参数表：key:键值，msgflg:设置消息队列创建方式或权限。返回值：消息队列的标识符。
	if(msqid==-1)
	{
		perror("msgget err");
		exit(1);
	} 
	while(idx<5)            //发送信息（4次） 
	{
		printf("enter some text:");
		fgets(buf,BUFSIZ,stdin);      //消息中的文本buf 
		data.my_msg_type=rand()%3+1;   //随机获取消息类型
		strcpy(data.anytext,buf);      
		//发送消息
		if(msgsnd(msqid,(void *)&data,sizeof(data),0)==-1) //将data转换成void型指针,发送的信息在data里面 
		{
			perror("msgsnd err");
			exit(1);
		}
		idx++;
	} 
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>//msgget()
#include <string.h>
#define MAX_TEXT 512
//��Ϣ�ṹ�� 
struct my_msg_st
{
	long int my_msg_type;        //��Ϣ����
	char anytext[MAX_TEXT]; 
};
int main()
{
	int idx=1;    //ѭ������ 
	int msqid;    //��Ϣ���б�ʶ�� 
	struct my_msg_st data;  //������Ϣdata 
	char buf[BUFSIZ];       //���û������,BUFSIZ��stdio.h ���� 
	msqid=msgget((key_t)1000,0664|IPC_CREAT);//������key:��ֵ��msgflg:������Ϣ���д�����ʽ��Ȩ�ޡ�����ֵ����Ϣ���еı�ʶ����
	if(msqid==-1)
	{
		perror("msgget err");
		exit(1);
	} 
	while(idx<5)            //������Ϣ��4�Σ� 
	{
		printf("enter some text:");
		fgets(buf,BUFSIZ,stdin);      //��Ϣ�е��ı�buf 
		data.my_msg_type=rand()%3+1;   //�����ȡ��Ϣ����
		strcpy(data.anytext,buf);      
		//������Ϣ
		if(msgsnd(msqid,(void *)&data,sizeof(data),0)==-1) //��dataת����void��ָ��,���͵���Ϣ��data���� 
		{
			perror("msgsnd err");
			exit(1);
		}
		idx++;
	} 
	return 0;
}

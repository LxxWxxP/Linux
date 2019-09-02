#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
//�Զ��干ͬ��
union semu
{
	int val;                   //cmdΪSETVALʱ������ָ���ź���ֵ
	struct semid_ds * buf;     //cmdΪIPC_STATʱ��IPC_SETʱ��Ч
	unsigned short * array;    //cmdΪGETALL��SETALLʱ��Ч
	struct seminfo * _buf;     //cmdΪIPC_INFOʱ��Ч 
};
static int sem_id;             //�ź�����ʶ�� 
static int set_semvalue()      //�����ź���ֵ
{
	union sem sem_union;
	sem_union.val=1;
	if(semctl(sem_id,0,SETVAL,sem_union)==-1)   //semctl()�������Զ��ź������ź��������п���,SETVAL����Ϊ��ʼ���ź�����ֵ����ֵΪsem_union.val=1 
		return 0;
	return 1;	
} 
//P����(-1)����ȡ�ź��� 
static int semaphore_p()
{
	struct sembuf sem_b;        //����Ϊ�����źż��е�ĳһ���ź���ĳ�ֲ��� 
	sem_b.sem_num=0;            //�ź������ź������еı��Ϊ0 
	sem_b.sem_op=-1;            //P����
	sem_b.sem_flg=SEM_UNDO;     //�ź�����ϵͳ�Զ��ͷ� 
	if(semop(sem_id,&sem_b,1)==-1)
	{
		perror("sem_p err");
		return 0;
	}
	return 1;
}
//V����(+1)����ȡ�ź��� 
static int semaphore_v()
{
	struct sembuf sem_b;        
	sem_b.sem_num=0;             
	sem_b.sem_op=1;            
	sem_b.sem_flg=SEM_UNDO;     
	if(semop(sem_id,&sem_b,1)==-1)
	{
		perror("sem_v err");
		return 0;
	}
	return 1;
}
//ɾ���ź���
static void del_semvalue()
{
	union semu sem_union;
	if(semctl(sem_id,0,IPC_RMID,sem_union)==-1)
		perror("del err");
} 
int main()
{
	int i;                        //����ѭ�� 
	pid_t pid;
	char ch='C';                  
	sem_id=semget((key_t)1000,1,0664|IPC_CREAT);    //�����ź���
	if(sem_id==-1)
	{
		perror("sem_c err");
		exit(-1);	
	} 
	if(!set_semvalue())           //��ʼ���ź���Ϊ1 
	{
		perror("init err");
		exit(-1);
	}
	pid=fork();                   //�����ӽ��� 
	if(pid==-1)
	{
		del_semvalue();           //�ӽ��̴���ʧ�ܣ���Ȼ�ź���Ҳ��û���� 
		exit(-1);
	}
	else if(pid==0)
		ch='Z'                    //�����ӽ��̴�ӡ���ַ�
	else 
		ch='C';                   //���ø����̴�ӡ���ַ� 
	srand((unsigned int)getpid());//�������������
	for(i=0;i<8;i++)
	{
		semaphore_p();            //��ȡ�ź��� 
		printf("%c",ch);          
		fflush(stdout);           //���ַ���ӡ����Ļ 
		sleep(rand()%4);          //��˯
		printf("%c",ch);
		fflush(stdout);
		sleep(1);
		semaphore_v(); 
	} 
	if(pid>0)
	{
		wait(NULL);               //�����ӽ��� 
		del_semvalue();           //ɾ���ź��� 
	}
	printf("\nprocess %d finished.\n",getpid());
	return 0;
}

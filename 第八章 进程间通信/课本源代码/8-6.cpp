#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
//自定义共同体
union semu
{
	int val;                   //cmd为SETVAL时，用于指定信号量值
	struct semid_ds * buf;     //cmd为IPC_STAT时或IPC_SET时生效
	unsigned short * array;    //cmd为GETALL或SETALL时生效
	struct seminfo * _buf;     //cmd为IPC_INFO时生效 
};
static int sem_id;             //信号量标识符 
static int set_semvalue()      //设置信号量值
{
	union sem sem_union;
	sem_union.val=1;
	if(semctl(sem_id,0,SETVAL,sem_union)==-1)   //semctl()函数可以对信号量或信号量集进行控制,SETVAL功能为初始化信号量的值，且值为sem_union.val=1 
		return 0;
	return 1;	
} 
//P操作(-1)，获取信号量 
static int semaphore_p()
{
	struct sembuf sem_b;        //功能为：对信号集中的某一个信号做某种操作 
	sem_b.sem_num=0;            //信号量在信号量集中的编号为0 
	sem_b.sem_op=-1;            //P操作
	sem_b.sem_flg=SEM_UNDO;     //信号量由系统自动释放 
	if(semop(sem_id,&sem_b,1)==-1)
	{
		perror("sem_p err");
		return 0;
	}
	return 1;
}
//V操作(+1)，获取信号量 
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
//删除信号量
static void del_semvalue()
{
	union semu sem_union;
	if(semctl(sem_id,0,IPC_RMID,sem_union)==-1)
		perror("del err");
} 
int main()
{
	int i;                        //用于循环 
	pid_t pid;
	char ch='C';                  
	sem_id=semget((key_t)1000,1,0664|IPC_CREAT);    //创建信号量
	if(sem_id==-1)
	{
		perror("sem_c err");
		exit(-1);	
	} 
	if(!set_semvalue())           //初始化信号量为1 
	{
		perror("init err");
		exit(-1);
	}
	pid=fork();                   //创建子进程 
	if(pid==-1)
	{
		del_semvalue();           //子进程创建失败，自然信号量也就没用了 
		exit(-1);
	}
	else if(pid==0)
		ch='Z'                    //设置子进程打印的字符
	else 
		ch='C';                   //设置父进程打印的字符 
	srand((unsigned int)getpid());//设置随机数种子
	for(i=0;i<8;i++)
	{
		semaphore_p();            //获取信号量 
		printf("%c",ch);          
		fflush(stdout);           //将字符打印到屏幕 
		sleep(rand()%4);          //沉睡
		printf("%c",ch);
		fflush(stdout);
		sleep(1);
		semaphore_v(); 
	} 
	if(pid>0)
	{
		wait(NULL);               //回收子进程 
		del_semvalue();           //删除信号量 
	}
	printf("\nprocess %d finished.\n",getpid());
	return 0;
}

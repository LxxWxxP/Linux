#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
	FILE * r_fp, * w_fp;
	char buf[100];
	r_fp=popen("ls","r");              //读取命令执行结果
	w_fp=popen("wc -l","w");           //将管道中的数据传递给进程
	while(fgets(buf,sizeof(buf),r_fp)!=NULL)      //从读指针r_fp读到buf数组里面去 
		fputs(buf,w_fp);	   //从buf数组写到写指针w_fp里面去
	pclose(r_fp);
	pclose(w_fp);
	return 0; 
} 

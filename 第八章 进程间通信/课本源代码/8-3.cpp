#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
	FILE * r_fp, * w_fp;
	char buf[100];
	r_fp=popen("ls","r");              //��ȡ����ִ�н��
	w_fp=popen("wc -l","w");           //���ܵ��е����ݴ��ݸ�����
	while(fgets(buf,sizeof(buf),r_fp)!=NULL)      //�Ӷ�ָ��r_fp����buf��������ȥ 
		fputs(buf,w_fp);	   //��buf����д��дָ��w_fp����ȥ
	pclose(r_fp);
	pclose(w_fp);
	return 0; 
} 

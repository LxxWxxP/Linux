#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
	pid_t pid;
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		exit(1);
	}
	else if (pid > 0)
	{
		printf("parent process:pid");
	}
	else if (pid == 0)
	{
		printf("child process\n");
		execlp("cat", "-b", "6-2.cpp", NULL);
		perror("error 6-2\n");
		printf("child process\n");
	}
	return 0;
}


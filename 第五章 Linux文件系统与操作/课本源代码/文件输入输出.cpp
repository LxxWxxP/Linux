#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main()
{
	int fd = 0;
	char filename[20] = "/home/itheima/a.txt";
	fd = open(filename, O_RDWR | O_EXCL | O_TRUNC, S_IRWXG);
	if (fd == -1)
	{
		perror("file open error.\n");
		exit(-1);
	}
	int len = 0;
	char buf[100] = { 0 };
	scanf("%s", buf);
	len = strlen(buf);
	write(fd, buf, len);
	close(fd);
	printf("--------------------------------\n");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("file open error.\n");
		exit(-1);
	}
	off_t f_size = 0;
	f_size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	while (lseek(fd, 0, SEEK_CUR) != f_size)
	{
		read(fd, buf, 1024);
		printf("%s\n", buf);
	}
	close(fd);
	return 0;
}
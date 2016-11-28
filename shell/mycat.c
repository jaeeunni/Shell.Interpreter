#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

int mycat(int argc,char**argv)
{
	char ch;
	int fd;

	if(argc!=2)
	{
		printf("usage : ./mycat filename\n");
	}
	
	fd=open(argv[1],O_RDONLY);

	while(read(fd,&ch,1))
	{
		write(1,&ch,1);
	}
	close(fd);
	return 0;
}

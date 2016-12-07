#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "../include/common.h"

int check_arg(char *av[], const char *opt)
{
	int count = 0;
	while(*av != '\0')
	{
		if(!strcmp(av[count], opt))
		{
			return TRUE;
		}
		av++;
	}
	return FALSE;
}

void cmd_cd(int ac, char *av[])
{
	char *path;

	if(ac > 1)
	{
		path = av[1];
	}
	
	else if((path = (char*)getenv("HOME")) == NULL)
	{
		path = ".";
	}
	
	if(chdir(path) == ERROR)
	{
		fprintf(stderr, "%s: bad directory.\n", path);
	}
}

void cmd_exit()
{
	exit(1);
}

void cmd_cp(int ac, char *av[])
{
	FILE *src;
	FILE *dst;
	char ch;
	
	if(ac < 3)
	{
		fprintf(stderr, "Not enough arguments.\n");
		return;
	}
	
	if((src = fopen(av[1], "r")) == NULL)
	{
		fprintf(stderr, "%s: Can't open file.\n", av[1]);
		return;
	}
	
	if((dst = fopen(av[2], "w")) == NULL)
	{
		fprintf(stderr, "%s: Can't open file.\n", av[2]);
		return;
	}
	
	while(!feof(src))
	{
		ch = (char) fgetc(src);
		if(ch != EOF)
		{
			fputc((int)ch, dst);
		}
	}
	
	if(check_arg(av, "-v"))
	{
		printf("cp %s %s\n", av[1], av[2]);
	}
	fclose(src);
	fclose(dst);
}

void cmd_rm(int ac, char *av[])
{
	if(ac < 2)
	{
		fprintf(stderr, "Not enough arguments.\n");
		return;
	}
	
	unlink(av[1]);
	if(check_arg(av, "-v"))
	{
		printf("rm %s\n", av[1]);
	}
}

void cmd_rmdir(int ac, char *av[])
{
	if(ac < 2)
	{
		fprintf(stderr, "Not enough arguments.\n");
		return;
	}
	
	if(rmdir(av[1]))
	{
		fprintf(stderr, "Remove directory failed.\n");
	}
}

void cmd_ls(int ac, char *av[])
{
	DIR *dp;
	struct dirent *entry;	
	char *path;
	int count;
	int opt_a;
	int opt_l;

	if(ac <2)
	{
		path=".";
	}

	else
	{
		path = av[1];
	}

	if((dp = opendir(path)) == NULL)
	{
		fprintf(stderr, "Can't open directory: %s", av[1]);
		return;
	}

	opt_a = check_arg(av, "-a");
	opt_l = check_arg(av, "-l");
	count = 0;

	while((entry = readdir(dp)) != NULL)
	{
		if(!opt_a)
		{
			if(entry->d_name[0] == '.')
			{
				continue;
			}
		}
		
		printf("%s\t", entry->d_name);
		if(opt_l)
		{
			printf("\n");
		}
		
		else
		{
			if(count > 5)
			{
				printf("\n");
				count = 0;
			}
			else
			{
				count++;
			}
		}
	}
	closedir(dp);
	printf("\n");
}

int cmd_mkdir(int argc,char **argv)
{
	if(argc!=2) //error
	{
		fprintf(stderr, "Not enough argumnets.\n");
		return 1;
	}
	
	else 
	{
		mkdir(argv[1],0755);
		return 1;
	}
}

int cmd_cat(int argc,char **argv)
{
	char c;
	int f; // file discriptor

	if(argc!=2) //error
	{
		fprintf(stderr, "Not enough arguments.\n");
		return 1;
	}
	else
	{
		f=open(argv[1],O_RDONLY); // file open for read mode
		
		while(read(f,&c,1))  
		{
			write(1,&c,1); //printf per 1 byte 
		}
		close(f);
		return 0;
	}
}


int cmd_mv(int argc, char*argv[])
{
	// cp+mv 
	int fd1,fd2; 
	int r_size,w_size;
	char buf[100];

	fd1=open(argv[1],O_RDONLY); // open for original file
	fd2=open(argv[2],O_RDWR|O_CREAT|O_EXCL,0664); // oepn for mv file

	r_size=read(fd1,buf,100); // read for original file
	w_size=write(fd2,buf,r_size); // write for mv file
	while(r_size==100)
	{
		r_size=read(fd1,buf,100);
		w_size=write(fd2,buf,r_size);
	}
	unlink(argv[1]);
	return 0;
}

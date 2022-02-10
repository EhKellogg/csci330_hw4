#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
	int fd;
	fd = open(argv[1], O_RDWR); 
	if(fd == -1)
	{
		perror("opening file");
	}
	if(!fd)
	{
		fd = open(argv[1], O_CREAT, 000);
	}


	return 0;
}

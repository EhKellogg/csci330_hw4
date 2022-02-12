#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
int main(int argc, char *argv[])
{
	bool gotc = false;
	int opt;
	int fd;
	struct stat filestatus;
	char input2[] = "\n";
	char *buffer2 = (char *) input2;
	char *buffer;

	while((opt = getopt(argc, argv, "c")) != -1)
	{
		switch(opt)
		{
			case 'c':
			gotc = true;
			break;
		}
	}	
	
	if((open(argv[optind],O_WRONLY)) == -1)
	{
		fd = open(argv[optind], O_WRONLY | O_CREAT, 000);
		close(fd);	
	}
	if(stat(argv[optind], &filestatus) == -1)
	{
		perror("Error in stat");
		exit(1);
	}

	if((filestatus.st_mode) != 32768)
	{
		std::cout << "The file is not safe!" << std::endl;
		exit(1);
	}

	buffer = argv[optind + 1];	
	if(gotc == true)
	{	
		chmod(argv[optind], 500);
		fd = open(argv[optind],O_WRONLY | O_TRUNC);
		write(fd, buffer, strlen(buffer));
		write(fd, buffer2, strlen(buffer2));
		chmod(argv[optind], 000);
		close(fd);
			
	}
	else 
	{
		chmod(argv[optind], 500);
		fd = open(argv[optind], O_APPEND | O_WRONLY);
		write(fd, buffer, strlen(buffer));
		write(fd, buffer2, strlen(buffer2));
		chmod(argv[optind], 000);
		close(fd);
	}
	return 0;
}

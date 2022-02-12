#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

/**
 * Eric Kellogg
 * z1942596
 *
 * CSCI 330 section 1
 *
 *
 * I certify that this is my own work and where
 * appropriate an extension of the starter code
 * provided for the assignment
 *
 *
 *
 *
 * *****************************************/
int main(int argc, char *argv[])
{
	bool gotc = false;
	int opt;
	int fd;
	struct stat filestatus;
	char input2[] = "\n";
	char *buffer2 = (char *) input2;
	char *buffer;
	
	while((opt = getopt(argc, argv, "c")) != -1) ///checks to see if the optional argument "-c" was added
	{					    /// and then sets the variable gotc to true	
		switch(opt)
		{
			case 'c':
			gotc = true;
			break;
		}
	}	
	
	if((open(argv[optind],O_WRONLY)) == -1) /// checks if the file exists and if not it creates a new file
	{
		fd = open(argv[optind], O_WRONLY | O_CREAT, 000);
		close(fd);	
	}
	if(stat(argv[optind], &filestatus) == -1) 
	{
		perror("Error in stat");
		exit(1);
	}

	if((filestatus.st_mode) != 32768) /// makes sure the files permisions are set to 000
	{
		std::cout << "The file is not safe!" << std::endl;
		exit(1);
	}

	buffer = argv[optind + 1];	
	if(gotc == true) /// if the "-c" was added this will run and truncate the file before running anything
	{					///takes in an argument from the command line and writes it to the file 
		chmod(argv[optind], 500);
		fd = open(argv[optind],O_WRONLY | O_TRUNC);
		write(fd, buffer, strlen(buffer));
		write(fd, buffer2, strlen(buffer2));
		chmod(argv[optind], 000);
		close(fd);
			
	}
	else  /// if no "-c" was present this runs and takes in an argument from the command line and writes it to the file
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

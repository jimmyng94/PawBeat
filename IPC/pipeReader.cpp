#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <iostream>
  
int main() 
{ 
    int fd; 
    char input[1024]; 
  
    // FIFO file path 
    char * myfifo = "/home/pi/Documents/pawpulse/webinterface/myfifo2"; 
  
    // Creating the named file(FIFO) 
    // mkfifo(<pathname>, <permission>) 
    mkfifo(myfifo, 0666); 
    if (mkfifo(myfifo, 0666)<0) {
		perror("FIFO status");
	} 
	else {
		perror("mkfifo error");
	}
	
	while(1) {
		// Open FIFO for write only 
		fd = open(myfifo, O_RDONLY); 
		if (fd==-1) {
			perror("open error");
		}
		else {
			printf("FIFO opened \n");
		}
		
		// Read the input on FIFO 
	
		read(fd, input, sizeof(input)); 
		
		if (read(fd, input, sizeof(input))==-1) {
			perror("read error");
		}
		else {
			printf("Message read: %s \n", input);
		}
		
		close(fd); 
	}
    return 0; 
} 

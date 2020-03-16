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
	 
		// Take an input from user. 
		// 1024 is maximum length 
		fgets(input, 1024, stdin); 
	 
		// Open FIFO for write only 
		fd = open(myfifo, O_WRONLY); 
		if (fd==-1) {
			perror("open error");
		}
		else {
			std::cout << "FIFO opened \n";
		}
		
		// Write the input on FIFO 
		write(fd, input, strlen(input)+1); 
		
		if (write(fd, input, strlen(input))==-1) {
			perror("write error");
		}
		else {
			printf("Message written: %s \n", input);
		}
		close(fd); 
	}
    return 0; 
} 
	

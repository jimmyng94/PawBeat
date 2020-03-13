// pipe reader sample
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

#define MAX_BUF 1024

int main() {
	
	int fd;
	char *myfifo = "/home/pi/Documents/pawpulse/webinterface/myfifo";
	char buf[MAX_BUF];
	
	while (true){
	/* open, read, and display the message from the FIFO*/
	fd = open(myfifo, O_RDONLY);
	read(fd, buf, MAX_BUF);
	std::cout<<("Received: %s\n", buf);
	close(fd);
	}
	return 0;
}

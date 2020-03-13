// pipe writer sample
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

int main () {
	
	int fd;
	char *myfifo = "/home/pi/Documents/pawpulse/webinterface/myfifo";

	/* create the FIFO (named pipe) */
	mkfifo(myfifo, 0666);

	/* write "Hi" to the FIFO */
	while(true) {
	fd = open(myfifo, O_WRONLY);
	usleep(100000);
	write(fd, "{\"eon\":{\"bpm\":10}}", sizeof("{\"eon\":{\"bpm\":10}}"));
	close(fd);
	}
	/* remove the FIFO */
	unlink(myfifo);

	return 0;
}
	

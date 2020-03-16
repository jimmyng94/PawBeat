/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */
#include "pubnub.hpp"
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>


/** This example, while using the C++ API which is "generic" will
    actually work only with the Pubnub C callback "back-end" (notification
    interface). 

    To do the same thing with the "sync back-end", the user should use
    the pubnub::futres::last_result() to check for the outcome of both
    operations that are started concurrently.
 */


int main()
{
    try {
        //Initialize pubnub
        enum pubnub_res res;
        char const *channel = "bpm";
        pubnub::context pb("pub-c-f6f91f16-a809-447a-9179-f2af45ec65f1", "sub-c-0ae8a45a-5581-11ea-b828-26d2a984a2e5");

	
        //Initialize FIFO
        int fd; 
        char input[1024]; 
        char * myfifo = "/home/pi/Documents/pawpulse/webinterface/myfifo2"; 
  
        mkfifo(myfifo, 0666); //Creating the named file(FIFO) 
        if (mkfifo(myfifo, 0666)<0) {
            perror("FIFO status");
        } 
        else {
            perror("mkfifo error");
        }
        
        //START WHILE TRUE LOOP
        while(1) { 
            //START FIFO
            fd = open(myfifo, O_RDONLY); //Open FIFO
            if (fd==-1) {
                perror("open error");
            }
            else {
                printf("FIFO opened \n");
            }
            read(fd, input, sizeof(input)); //Read from FIFO
            if (read(fd, input, sizeof(input))==-1) {
                perror("read error");
            }
            else {
                printf("Message read: %s \n", input);
            }
            close(fd); //Close FIFO
            //END FIFO

            //START PUBLISH
            printf("Start publishing \n");
            pubnub::futres fr = pb.publish(channel, input);
            printf("Await publish\n");
            res = fr.await();
            if (res == PNR_STARTED) {
                std::cout << "await() returned unexpected: PNR_STARTED" << std::endl;
                return -1;
            }
            if (PNR_OK == res) {
                std::cout << "Published! Response from Pubnub: " << pb.last_publish_result() << std::endl;
            }
            else if (PNR_PUBLISH_FAILED == res) {
                std::cout << "Published failed on Pubnub, description: " << pb.last_publish_result() << std::endl;
            }
            else {
                std::cout << "Publishing failed with code: " << (int)res << std::endl;
            }
            //END PUBLISH
        }
        //END WHILE TRUE LOOP
	
    }
    catch (std::exception &exc) {
        std::cout << "Caught exception: " << exc.what() << std::endl;
    }
	

    return 0;
}

/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */
#include "pubnub.hpp"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

#define MAX_BUF 1024

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
        /*Initialize pubnub*/
        enum pubnub_res res;
        char const *channel = "bpm";
        pubnub::context pb("pub-c-f6f91f16-a809-447a-9179-f2af45ec65f1", "sub-c-0ae8a45a-5581-11ea-b828-26d2a984a2e5");

        /*Setup message to be sent*/
        int fd;
        char *myfifo = "/home/pi/Documents/pawpulse/webinterface/myfifo";
        char bpmMsg[MAX_BUF];
	
        /* open, read, and display the message from the FIFO*/
        fd = open(myfifo, O_RDONLY);
        read(fd, bpmMsg, MAX_BUF);
        close(fd);
        
        std::cout << bpmMsg;
	
        /*Start of publish*/
        std::cout << "--------------------------" << std::endl <<
            "Publishing..." << std::endl <<
            "--------------------------";
        
        pubnub::futres fr = pb.publish(channel, bpmMsg);
        
        std::cout << "Await publish" << std::endl;
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
        /*End of publish*/
	
    }
    catch (std::exception &exc) {
        std::cout << "Caught exception: " << exc.what() << std::endl;
    }
	
    std::cout << "Publish Over" << std::endl;

    return 0;
}

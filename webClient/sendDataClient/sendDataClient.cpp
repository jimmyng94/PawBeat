#include "../pubnub/cpp/pubnub.hpp"
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <thread>
#include <iostream>
#include <stdarg.h>
#define PUBNUB_THREADSAFE


int bpm_publish(){
    //Instantiate pubnub(bpm)
    enum pubnub_res res;
    char const *channel = "bpm";
    pubnub::context pb("pub-c-f6f91f16-a809-447a-9179-f2af45ec65f1", "sub-c-0ae8a45a-5581-11ea-b828-26d2a984a2e5");
    std::string uuid("RPI_BPM");
    //Instantiate fifo(bpm)
    int fd; 
    char bpmMsg[1024]; 
    char * bpm_fifo = "bpm_fifo"; 
    mkfifo(bpm_fifo, 0666);
    if (mkfifo(bpm_fifo, 0666)<0) {
        perror("bpm_fifo status");
    } 
    else {
        perror("mkfifo error");
    }
    while(1) {
        //Start fifo(bpm)
        printf("Waiting for bpm writer... \n");
        fd = open(bpm_fifo, O_RDONLY); //blocking waits for fifo to be opened on the other end
        if (fd==-1) {
            perror("open error");
        }
        else {
            printf("bpm_fifo opened \n");
        }
        if (read(fd, bpmMsg, sizeof(bpmMsg))==-1) {
            perror("read error");
        }
        else {
            printf("Message read from bpm_fifo: %s \n", bpmMsg);
        }
        close(fd);
        printf("bpm_fifo closed \n");
        printf("---------------------- \n");
        //End fif(bpm)
        //Start publishing(bpm)
        printf("Start publishing to bpm channel \n");
        pubnub::futres fr = pb.publish(channel, bpmMsg);
        printf("Await publish... \n");
        res = fr.await();
        if (res == PNR_STARTED) {
            std::cout << "await() returned unexpected: PNR_STARTED" << std::endl;
            return -1;
        }
        if (PNR_OK == res) {
            std::cout << "Published: " << bpmMsg << " Response from Pubnub: " << pb.last_publish_result() << std::endl;
        }
        else if (PNR_PUBLISH_FAILED == res) {
            std::cout << "Published: " << bpmMsg << " failed on Pubnub, description: " << pb.last_publish_result() << std::endl;
        }
        else {
            std::cout << "Publishing: " << bpmMsg << " failed with code: " << (int)res << std::endl;
        }
        //End publishing(bpm)
    }
}

int step_publish(){
    //Instantiate pubnub(step)
    enum pubnub_res res;
    char const *channel = "step";
    pubnub::context pb_2("pub-c-f6f91f16-a809-447a-9179-f2af45ec65f1", "sub-c-0ae8a45a-5581-11ea-b828-26d2a984a2e5");
    std::string uuid("RPI_STEP");
    //Instantiate fifo(step)
    int fd; 
    char stepMsg[1024]; 
    char * step_fifo = "step_fifo"; 
    mkfifo(step_fifo, 0666);
    if (mkfifo(step_fifo, 0666)<0) {
        perror("step_fifo status");
    } 
    else {
        perror("mkfifo error");
    }
    while (1) {
        //Start fifo(step)
        printf("Waiting for step writer... \n");
        fd = open(step_fifo, O_RDONLY); //blocking waits for fifo to be opened on the other end
        if (fd==-1) {
            perror("open error");
        }
        else {
            printf("step_fifo opened \n");
        }
        if (read(fd, stepMsg, sizeof(stepMsg))==-1) {
            perror("read error");
        }
        else {
            printf("Message read from step_fifo: %s \n", stepMsg);
        }
        close(fd);
        printf("step_fifo closed \n");
        printf("---------------------- \n");
        //End fifo(step)
        //Start publishing(step)
        printf("Start publishing to step channel \n");
        pubnub::futres fr_2 = pb_2.publish(channel, stepMsg);
        printf("Await publish... \n");
        res = fr_2.await();
        if (res == PNR_STARTED) {
            std::cout << "await() returned unexpected: PNR_STARTED" << std::endl;
            return -1;
        }
        if (PNR_OK == res) {
            std::cout << "Published: " << stepMsg << " Response from Pubnub: " << pb_2.last_publish_result() << std::endl;
        }
        else if (PNR_PUBLISH_FAILED == res) {
            std::cout << "Published: " << stepMsg << " failed on Pubnub, description: " << pb_2.last_publish_result() << std::endl;
        }
        else {
            std::cout << "Publishing: " << stepMsg << " failed with code: " << (int)res << std::endl;
        }
        //End publishing(step)
    }
}

int main()
{
    try 
    {
        std::thread t1(bpm_publish);
        std::cout << "Thread 1 started" << std::endl;
        std::thread t2(step_publish);
        std::cout << "Thread 2 started" << std::endl;
        t1.join();
        std::cout << "Thread 1 finished" << std::endl;
        t2.join();
        std::cout << "Thread 2 finished" << std::endl;
    }
    catch (std::exception &exc) {
        std::cout << "Caught exception: " << exc.what() << std::endl;
    }
	

    return 0;
}

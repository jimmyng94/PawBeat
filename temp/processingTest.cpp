#include <iostream> 
#include <fstream> 
#include <fcntl.h> 
#include <inttypes.h> 
#include <linux/i2c-dev.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/ioctl.h> 
#include <wiringPi.h> 
#include <wiringPiI2C.h> 
#include <errno.h> 
#include <ADS1015.h> 
#include <vector> 
#include <cmath> 
#include <time.h> 
#include "LSM6DS3.h"
#include "Fir1.h"
#include <string.h> 
#include <thread>
#include <sstream>
#define ADC_PIN 3
//#define ACC_PIN 7
#define Fs 120

using namespace std; 
static volatile int counter = 0; 
//static volatile float bpm = 0;
static volatile float step = 0;
static volatile int upflag = 0;
static volatile int t = 0;
vector <float> _bpm;
static volatile bool threadRunning ;

Adafruit_ADS1015 ads; 
LSM6DS3 imu(I2C_MODE, 0x6A);

Fir1 fir("hr_coeff.dat");

void getSTEP(void){
	float x = imu.readFloatAccelX();
	float y = imu.readFloatAccelY();
	float z = imu.readFloatAccelZ();
	
	float mag = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
	if(mag > 10){
		step++;
	}
}

float getBPM(){ 
  //cout << "Get"; 
  float val = ads.getLastConversionResults();  
  std::cout<< "val = " << val << std::endl; //val is constant at 4095
  //cout << adc0<< endl;
  float newVal = fir.filter(val);
  std::cout<< "newVal = " << newVal << std::endl; //new val under 10 so if does not run
  if(newVal > 10){
	   std::cout<< "upflag = " << upflag << std::endl;
    if(upflag == 0){
	    std::cout<< "t = " << t << std::endl;
	if(t > 0){
		std::cout<< "Fs = " << Fs << std::endl;
		float bpm = Fs/t*60;
		_bpm.push_back(bpm);
		printf("%d \n", bpm);
	    }
	t = 0;
    }
    upflag = 25;
  }
  else{
    if(upflag > 0){
      upflag--;
    }
  }
t++;
counter++;
//returns newVal
}

void writeBPM(){
    int fd; 
    const char* bpmMsg; 
    char * bpm_fifo = "/home/pi/Documents/pawpulse/webinterface/bpm_fifo"; 
    if (mkfifo(bpm_fifo, 0666)<0) {
	perror("bpm_fifo status");
    } 
    else {
	perror("mkfifo error");
    }
    while(_bpm.size() != 0) {
	auto bpm = _bpm.back();
	_bpm.pop_back(); 
	ostringstream bpmMsg_oss;
	bpmMsg_oss << "{\"eon\":{\"bpm\":" << bpm << "}}";
	string bpmMsg_s = bpmMsg_oss.str();
	bpmMsg = bpmMsg_s.c_str();
	fd = open(bpm_fifo, O_WRONLY); 
	if (fd==-1) {
		perror("open error");
	}
	else {
		printf("bpm_fifo opened \n");
	}
	if (write(fd, bpmMsg, sizeof(bpmMsg_s))==-1) {
		perror("write error");
	}
	else {
		printf("Message written: %s \n", bpmMsg);
	}
		close(fd); 
		printf("bpm_fifo closed \n");
    }
}
/*
void writeSTEP(){
    int fd; 
    const char* stepMsg; 
    char * step_fifo = "/home/pi/Documents/pawpulse/webinterface/step_fifo"; 
    if (mkfifo(step_fifo, 0666)<0) {
	perror("step_fifo status");
    } 
    else {
	perror("mkfifo error");
    }
    while(_step.size() != 0) {
	auto step = _step.back();
	_step.pop_back(); 
	ostringstream stepMsg_oss;
	stepMsg_oss << "{\"eon\":{\"steps\":" << step << "}}";
	string stepMsg_s = stepMsg_oss.str();
	stepMsg = stepMsg_s.c_str();
	fd = open(step_fifo, O_WRONLY); 
	if (fd==-1) {
		perror("open error");
	}
	else {
		printf("step_fifo opened \n");
	}
	if (write(fd, stepMsg, sizeof(stepMsg_s))==-1) {
		perror("write error");
	}
	else {
		printf("Message written: %s \n", stepMsg);
	}
		close(fd); 
		printf("step_fifo closed \n");
    }
}*/


 void sendData(){
	threadRunning  = true;
	std::thread sending(writeBPM); 
	sending.join(); 
	threadRunning  = false;
	
 }
 
 void startHeart()
{
	counter++;
	std::thread th0(getBPM);
	th0.join();
}
int main (int,char**)
{
	// inits the filter
	//fir("hr_coeff.txt");
	// resets the delay line to zero
	fir.reset ();
  
	wiringPiSetup(); 
	pinMode(ADC_PIN, INPUT);
  
	//set up adc
	//ads.begin(); 
	//ads.setGain(GAIN_SIXTEEN);

	// setup ADS1015
	ads.begin();
	ads.setGain(GAIN_FOUR); 

	//ads.startComparator_SingleEnded(0,0);
	ads.startComparator_SingleEnded(0, 1000); 
    
	if (imu.begin() != 0) 
	{ 
		std::cout << "Problem starting the sensor at 0x6A." << std::endl; 
		return 1;
	} 

	else 
	{ 
		std::cout << "Sensor at 0x6A started." << std::endl; 
		imu.settings.gyroEnabled =0; 
		imu.settings.accelRange = 2;  //Max G force readable.  Can be: 2, 4, 8, 16
		imu.settings.accelSampleRate = 26; //Hz.  Can be: 13, 26, 52, 104, 208, 416, 833, 1666, 3332, 6664, 13330
        
	}  
	//Interrupt when adc gets new reading
	//if(wiringPiISR(ADC_PIN, INT_EDGE_RISING, &startHeart) > 0){ 
    	//	cout << "INTERRUPT!" << endl; 
  	//}

  	//uint8_t readDataByte = 0;
		//uint16_t stepsTaken = 0;
 while (1){  
	float bpm;
	std::cout<< "main : " << counter << std::endl;
        usleep(1000000);
	std::cout<< "start getBPM" << std::endl;
	bpm = getBPM(); //getBPM() returns newVal
	std::cout<< "end getBPM" << std::endl;
	std::cout<< "bpm = " << bpm << std::endl;
	_bpm.push_back(bpm); //works
	sendData(); //works
	
	//if (_bpm.empty() == false && threadRunning == false){
	//	sendData();
	//}
	//getBPM();
	/*if(counter%3 == 0){ 
    		getSTEP(); 
  	}		*/
 }
}

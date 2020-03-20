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
#define ADC_PIN 3
//#define ACC_PIN 7
#define Fs 50

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

Fir1 fir;

void getSTEP(void){
	float x = imu.readFloatAccelX();
	float y = imu.readFloatAccelY();
	float z = imu.readFloatAccelZ();
	
	float mag = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
	if(mag > 10){
		step++;
	}
//SEND STEP TO WEB :)
}

void getBPM(void){ 
  //cout << "Get"; 
  float val = ads.getLastConversionResults();  
  //cout << adc0<< endl;
  float newVal = fir.filter(val);
  if(newVal > 10){
    if(upflag == 0){
	if(t > 0){
		float bpm = Fs/t*60;
		_bpm.push_back(bpm)
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
  //SEND BPM TO WEB :)
}

void writeFIFO(){
    int fd; 
    char input[1024]; 
    char * myfifo = "/home/pi/Documents/pawpulse/webinterface/bpm_fifo"; 
    mkfifo(myfifo, 0666); 
    if (mkfifo(myfifo, 0666)<0) {
	perror("FIFO status");
    } 
    else {
	perror("mkfifo error");
    }
    while(_bpm.size() != 0) {
	// Take an input from user. 
	// 80 is maximum length 
	// Change this to set input to bpm value JSON format {"eon":{"bpm":intplaceholder}}
	auto bpm = _bpm.back();
	_bpm.pop_back(); 
	input = "{\"eon\":{\"bpm\":" + bpm +"}}" 
	// Open FIFO for write only 
	fd = open(myfifo, O_WRONLY); 
	if (fd==-1) {
		perror("open error");
	}
	else {
		std::cout << "FIFO opened \n";
	}
	// Write the input on FIFO 
	write(fd, input, sizeof(input)); 
	if (write(fd, input, sizeof(input))==-1) {
		perror("write error");
	}
	else {
		printf("Message written: %s \n", input);
	}
	close(fd); 
    }
}
 void sendData(){
	threadRunning  = true;
	std::thread sending(writeFIFO); 
	sending.join(); 
	threadRunning  = false;
	
 }
int main (int,char**)
{
	// inits the filter
	fir("hr_coeff.txt");
	// resets the delay line to zero
	fir.reset ();
  
	wiringPiSetup(); 
	pinMode(ADC_PIN, INPUT);
  
	//set up adc
	ads.begin(); 
	ads.setGain(GAIN_SIXTEEN);

	// setup ADS1015
	ads.begin();
	ads.setGain(GAIN_SIXTEEN); 

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
	if(wiringPiISR(ADC_PIN, INT_EDGE_RISING, &getBPM) > 0){ 
    		//cout << "INTERRUPT!" << endl; 
  	}

  	uint8_t readDataByte = 0;
		uint16_t stepsTaken = 0;
 while (1){  
	if (_bpm.empty() == false && threadRunning == false){
		sendData();
	}
	/*if(counter%3 == 0){ 
    		getSTEP(); 
  	}		*/
 }
}


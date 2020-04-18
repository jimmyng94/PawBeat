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
#define ADC_PIN 3	//input pin for ADC for microphone
#define ACC_PIN 7	//input pin for accelerometer
#define Fs 120

using namespace std; 
bool simulate = true;
static volatile int step = 0;
static volatile int counter = 0; 
static volatile int upflag = 0;
static volatile int stepflag = 0;
static volatile int t = 0;
vector <float> _bpm;
vector <float> _step;
std::vector<int> arr;	//handles simulated adc data
std::vector<float> acc_x;	//handles simulated acc data
std::vector<float> acc_y;
std::vector<float> acc_z;
static volatile bool threadRunning ;

Adafruit_ADS1015 ads; 
LSM6DS3 imu(I2C_MODE, 0x6A);
Fir1 fir("hr_coeff.dat");

void getStep(void){
	float x;
	float y;
	float z;
	if(simulate == false){
		x = imu.readFloatAccelX();
		y = imu.readFloatAccelY();
		z = imu.readFloatAccelZ();
	}
	else{
		if (acc_x.empty() == false){ 
			x = acc_x.back();
			acc_x.pop_back(); 
			
			y = acc_y.back();
			acc_y.pop_back();
			
			z = acc_z.back();
			acc_z.pop_back();
		}
	}
	float mag = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
	if(mag > 1.2){
		if(stepflag == 0){
			step++;
			_step.push_back(step);
			cout << "STEP: " << step << endl;
		}
		stepflag  = 5;
	}
	else{
		if(stepflag > 0){
			stepflag--;
		}
	}
	
}

void getBPM(void){
	float val;
	if (simulate == false){ 
		val = ads.getLastConversionResults();  
	}
	else
	{	
		if (arr.empty() == false){ 
			val = arr.back();
			arr.pop_back(); 
		}
	}
	float newVal = fir.filter(val);
	int bpm = 0;
	newVal = pow(newVal,2);
	if(newVal > 300){
		if(upflag == 0){
			if(t > 0){
				float new_bpm = 120.0/t*60.0;
				if(new_bpm > 30){
					bpm = new_bpm;
					_bpm.push_back(bpm);
				}
				cout << "BPM: " << bpm << endl;
			}
		t = 1;
		}
    upflag = 60;
	}
	else{
		if(upflag > 0){
		upflag--;
		}
	}
	t++;
}

void writeBPM(){
    int fd; 
    const char* bpmMsg; 
    const char* bpm_fifo = "../webClient/sendDataClient/bpm_fifo"; 
    mkfifo(bpm_fifo, 0666);
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
		if (write(fd, bpmMsg, sizeof(bpmMsg_s))==-1) {
			perror("write error");
		}
		else {
			printf("Message written: %s \n", bpmMsg);
		}
		close(fd); 
    }
}

void writeStep(){
    int fd; 
    const char* stepMsg; 
    const char* step_fifo = "../webClient/sendDataClient/step_fifo"; 
    mkfifo(step_fifo, 0666);
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
		
		if (write(fd, stepMsg, sizeof(stepMsg_s))==-1) {
			perror("write error");
		}
		else {
			printf("Message written: %s \n", stepMsg);
		}
			close(fd); 
    }
}


void sendBPM(){
	threadRunning  = true;
	std::thread sendBPM(writeBPM); 
	sendBPM.join(); 
	threadRunning  = false;
 }
 
void sendStep(){
	threadRunning  = true;
	std::thread sendStep(writeStep); 
	sendStep.join(); 
	threadRunning  = false;
 }
 
void startBPM(){
	std::thread th0(getBPM);
	th0.join();
}

void startStep(){
	std::thread th1(getStep);
	th1.join();
}
int main (int,char**)
{
	// inits the filter
	//fir("hr_coeff.txt");
	// resets the delay line to zero
	fir.reset ();
	if (simulate == false){
		wiringPiSetup(); 
		pinMode(ADC_PIN, INPUT);
		//set up adc/ADS
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
		if(wiringPiISR(ADC_PIN, INT_EDGE_RISING, &startBPM) > 0){ 
			cout << "INTERRUPT!" << endl; 
		}
	}
	else{
		//Send simulated data to getBPM function
		std::ifstream arr_handler("ads_120_C.txt");
		// use a std::vector to store your items.  It handles memory allocation automatically.
		float number;
		while (arr_handler>>number) {
			arr.push_back(number);
			// ignore anything else on the line
			arr_handler.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		//Send simulated data to getStep function
		std::ifstream accx_handler("3x.txt");
		while (accx_handler>>number) {
			//cout<< typeid(number).name() << endl;
			acc_x.push_back(number);
			// ignore anything else on the line
			accx_handler.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		std::ifstream accy_handler("3y.txt");
		while (accy_handler>>number) {
			acc_y.push_back(number);
			// ignore anything else on the line
			accy_handler.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		std::ifstream accz_handler("3Z.txt");
		while (accz_handler>>number) {
			acc_z.push_back(number);
			// ignore anything else on the line
			accz_handler.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	int count = 0;		
	while (arr.empty() == false || acc_x.empty() == false){
		count++;
		// calling get bpm at 120sps
		int sleepTime = 1000000/120;
		usleep(sleepTime);
		if(arr.empty() == false){
			startBPM();
			sendBPM();
			
		}
		if(count == 5){ //&& acc_x.empty() == false){
			startStep();
			sendStep();
			count = 0;
		}
	}
	return 0;
 }

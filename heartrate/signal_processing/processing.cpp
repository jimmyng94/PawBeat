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
#include <Fir1.h>

#define ADC_PIN 3
//#define ACC_PIN 7
#define Fs 50

using namespace std; 
static volatile int counter = 0; 
static volatile float bpm = 0;
static volatile float step = 0;
static volatile int upflag = 0;

Adafruit_ADS1015 ads; 

void getBPM(void){ 
  //cout << "Get"; 
  float val = ads.getLastConversionResults();  
  //cout << adc0<< endl;
  float newVal = fir.filter(val);
  if(newVal > 10){
    if(upflag == 0){
       bpm = fs/counter*60;
       counter ++;
    }
    upflag = 25;
  }
  else(){
    if(upflag > 0){
      upflag--;
    }
  }
  //SEND BPM TO WEB :)
  return; 
}

int main (int,char**)
{
	// inits the filter
	Fir1 fir("coefficients.dat");
	// resets the delay line to zero
	fir.reset ();
  
  wiringPiSetup(); 
  pinMode(INT_PIN, INPUT);
  
  //set up adc
  ads.begin(); 
  ads.setGain(GAIN_SIXTEEN); 
  
  //Interrupt when adc gets new reading
  ads.startComparator_SingleEnded(0, 1000); 
  if(wiringPiISR(INT_PIN, INT_EDGE_RISING, &getBPM) > 0){ 
    //cout << "INTERRUPT!" << endl; 
  }



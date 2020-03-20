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
#include <Fir1.h>

#define ADC_PIN 3
//#define ACC_PIN 7
#define Fs 50

using namespace std; 
static volatile int counter = 0; 
static volatile float bpm = 0;
static volatile float step = 0;
static volatile int upflag = 0;
static volatile int t = 0;

Adafruit_ADS1015 ads;
Fir1 fir;

void getSTEP(void){
	float x = readFloatAccelX();
	float y = readFloatAccelY();
	float z = readFloatAccelZ();
	
	float mag = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
	if(mag > 10){
		step++;
	}
//SEND STEP TO WEB :)
return
}

void getBPM(void){ 
  //cout << "Get"; 
  float val = ads.getLastConversionResults();  
  //cout << adc0<< endl;
  float newVal = fir.filter(val);
  if(newVal > 10){
    if(upflag == 0){
	    if(t > 0){
      		bpm = Fs/t*60;
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
  return; 
}

int main (int,char**)
{
	// inits the filter
	fir("hr_coeff.txt");
	// resets the delay line to zero
	fir.reset ();
  
  wiringPiSetup(); 
  pinMode(INT_PIN, INPUT);
  
  //set up adc
  ads.begin(); 
  ads.setGain(GAIN_SIXTEEN);
//set up acc	
LSM6DS3Core imu(I2C_MODE, 0x6B);

	if (imu.beginCore() !=0)
	{
		printf("Error at beginCore().\n");
	}
	else
	{
		printf("\nbeginCore() passed.\n");
	}

	uint8_t errorAccumulator =0;

	uint8_t dataToWrite = 0;
	// setup accelerometer
	dataToWrite = 0;

	dataToWrite |= LSM6DS3_ACC_GYRO_FS_XL_2g;
	dataToWrite |= LSM6DS3_ACC_GYRO_ODR_XL_26Hz;

	//Now, write the patched together data
	errorAccumulator += imu.writeRegister(LSM6DS3_ACC_GYRO_CTRL1_XL, dataToWrite);

	//Set the ODR bit
	errorAccumulator += imu.readRegister(&dataToWrite, LSM6DS3_ACC_GYRO_CTRL4_C);
	dataToWrite &= ~((uint8_t)LSM6DS3_ACC_GYRO_BW_SCAL_ODR_ENABLED);
	
	// Enable embedded functions -- ALSO clears the pdeo step count
	errorAccumulator += imu.writeRegister(LSM6DS3_ACC_GYRO_CTRL10_C, 0x3E);
	// Enable pedometer algorithm
	errorAccumulator += imu.writeRegister(LSM6DS3_ACC_GYRO_TAP_CFG1, 0x40);
	// Step Detector interrupt driven to INT1 pin
	errorAccumulator += imu.writeRegister( LSM6DS3_ACC_GYRO_INT1_CTRL, 0x10 );
	
	if( errorAccumulator )
	{
		printf("Problem configuring the device.\n");
	}
	else
	{
		printf("Device O.K.\n");
	}
  	uint8_t readDataByte = 0;
		uint16_t stepsTaken = 0;
 while (1){  
  	//Interrupt when adc gets new reading
  	ads.startComparator_SingleEnded(0, 1000); 
  	if(wiringPiISR(INT_PIN, INT_EDGE_RISING, &getBPM) > 0){ 
    		//cout << "INTERRUPT!" << endl; 
  	}

	if(counter%3 == 0){ 
    		getSTEP(); 
  	}	
 }
}



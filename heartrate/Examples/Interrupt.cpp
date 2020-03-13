#include <unistd.h>
#include "LSM6DS3.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//#include <thread.h>
//#include <chrono.h>
#include <iostream>
#include <math.h>
#include <wiringPi.h>

#define INT_PIN 0

using namespace std;

LSM6DS3 imu(I2C_MODE, 0x6A ); // constructor
float roll, pitch; 

void setup(void){
  cout <<" Done "<< endl;
  imu.settings.gyroEnabled = 1;  //Can be 0 or 1
  imu.settings.gyroRange = 2000;   //Max deg/s.  Can be: 125, 245, 500, 1000, 2000
  imu.settings.gyroSampleRate = 26;   //Hz.  Can be: 13, 26, 52, 104, 208, 416, 833, 1666
  imu.settings.gyroBandWidth = 200;  //Hz.  Can be: 50, 100, 200, 400;
  imu.settings.gyroFifoEnabled = 1;  //Set to include gyro in FIFO
  imu.settings.gyroFifoDecimation = 1;  //set 1 for on /1

  imu.settings.accelEnabled = 1;
  imu.settings.accelRange = 4;      //Max G force readable.  Can be: 2, 4, 8, 16
  imu.settings.accelSampleRate = 26;  //Hz.  Can be: 13, 26, 52, 104, 208, 416, 833, 1666, 3332, 6664, 13330
  imu.settings.accelBandWidth = 200;  //Hz.  Can be: 50, 100, 200, 400;
  imu.settings.accelFifoEnabled = 1;  //Set to include accelerometer in the FIFO
  imu.settings.accelFifoDecimation = 1;  //set 1 for on /1
  imu.settings.tempEnabled = 1;
  
    //Non-basic mode settings
  imu.settings.commMode = 1;

  //FIFO control settings
  imu.settings.fifoThreshold = 100;  //Can be 0 to 4096 (16 bit bytes)
  imu.settings.fifoSampleRate = 25;  //Hz.  Can be: 10, 25, 50, 100, 200, 400, 800, 1600, 3300, 6600
  imu.settings.fifoModeWord = 6;  //FIFO mode.
  //FIFO mode.  Can be:
  //  0 (Bypass mode, FIFO off)
  //  1 (Stop when full)
  //  3 (Continuous during trigger)
  //  4 (Bypass until trigger)
  //  6 (Continous mode)
  
  imu.writeRegister(LSM6DS3_ACC_GYRO_INT1_CTRL,0X01);
  
  imu.begin();
  
  imu.fifoBegin();
  // error at fifo clear
  //imu.fifoClear();
  cout <<hex <<imu.fifoGetStatus()<< endl;
}

void getAccValue(void){
  /*float temp;
  cout<< "enter" << endl;
  while( ( imu.fifoGetStatus() & 0x1000 ) == 0 ) {

  temp = imu.calcGyro(imu.fifoRead());
  cout<< temp<< " , ";

  temp = imu.calcGyro(imu.fifoRead());
  cout<< temp<< " , ";

  temp = imu.calcGyro(imu.fifoRead());
  cout<< temp<< " , ";

  temp = imu.calcAccel(imu.fifoRead());
  cout<< temp<< " , ";

  temp = imu.calcAccel(imu.fifoRead());
  cout<< temp<< " , ";

  temp = imu.calcAccel(imu.fifoRead());
  cout<< temp<< endl;
}
  uint16_t tempUnsigned = imu.fifoGetStatus();
  cout<<hex<< tempUnsigned << endl;*/
    float x = imu.readFloatAccelX();
    float y = imu.readFloatAccelY();
    float z = imu.readFloatAccelZ();
    roll = atan(y/sqrt((pow(x,2)+pow(z,2))))*180*3.14159;
    pitch = atan(-1*x/sqrt((pow(y,2)+pow(z,2))))*180*3.14159;
    cout << "roll = " << roll << ";  Pitch = " << pitch << endl;
}
int main()
{
  
  //setup();
  uint8_t errorAccumulator =0;
  imu.begin();
  errorAccumulator +=imu.writeRegister(LSM6DS3_ACC_GYRO_INT1_CTRL,0x01); 
  uint8_t WHO;
  imu.readRegister(&WHO,LSM6DS3_ACC_GYRO_WHO_AM_I_REG) ;
  cout<< hex<< WHO<< endl;
  if( errorAccumulator )
	{
		printf("Problem configuring the device.\n");
	}
	else
	{
		printf("Device O.K.\n");
	}
  
  if (wiringPiSetup () < 0) {
      cout<<"Unable to setup wiringPi"<<endl;
      //return 1;
  }
  pinMode(INT_PIN, INPUT);
  
  if(wiringPiISR(INT_PIN, INT_EDGE_RISING, &getAccValue) < 0){
      cout << "INTERRUPT Failed!" << endl;
  }
  cout<<" test Point!!" << endl;
 
  while (1)
  {
    //printf(wiringPiISR(INT_PIN, INT_EDGE_RISING, &getValue));
    //cout<< "roll : "<< roll<< " Pitch : "<< pitch<< endl;
   
    //printf("acc x: %f \n", imu.readFloatAccelX());
    //printf("acc y: %f \n", imu.readFloatAccelY());
    //printf("acc z: %f \n", imu.readFloatAccelZ());
    usleep(100000);
  }
  return 0;
 
}

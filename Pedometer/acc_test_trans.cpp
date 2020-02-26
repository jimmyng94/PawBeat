/*https://github.com/Zeph1990/LSM6DS3-for-Raspberry-Pi/blob/master/LSM6DS3.py
https://github.com/hallgrimur1471/Adafruit_ADS1X15_RPi*/

#include<wiringPi.h>
#include <wiringPiI2C.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(){
  uint8_t address = 0x6B;
  uint8_t dataToWrite[3];
  float adc_ref= 3.3;
  
  float zero_x = 1.569;
  float zero_y = 1.569;
  float zero_z = 1.569;
  
  float sensitivity_x = 0.3;
  float sensitivity_y = 0.3;
  float sensitivity_z = 0.3;
  
 uint8_t dataToWrite = 0;
 dataTowrite[0] =  0x03; 
 dataTowrite[1] =  0x00; 
 dataTowrite[2] =  0x10;
 int fd = wiringPiI2Csetup(address);
 int 
  
}

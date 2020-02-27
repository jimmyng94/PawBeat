/*
using sparkfun library
reference: https://learn.sparkfun.com/tutorials/lsm6ds3-breakout-hookup-guide/all
github: https://github.com/sparkfun/SparkFun_LSM6DS3_Arduino_Library
*/

#include "LSM6DS3.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>


using namespace std;

int main()
{
  
  LSM6DS3 imu(I2C_MODE, 0x6B ); // constructor
  //SensorSettings settingsIWanted;
  /*// if more than 1 device 
  LSM6DS3 SensorOne( I2C_MODE, 0x6A );
  LSM6DS3 SensorTwo( I2C_MODE, 0x6B );
  */
  imu.begin();
 
  while (1)
  {
    //printf(
    printf("acc x: %f \n", imu.readFloatAccelX());
    printf("acc y: %f \n", imu.readFloatAccelY());
    printf("acc z: %f \n", imu.readFloatAccelZ());
  }
  return 0;
 
}

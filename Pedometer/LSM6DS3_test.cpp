/*
using sparkfun library
reference: https://learn.sparkfun.com/tutorials/lsm6ds3-breakout-hookup-guide/all
github: https://github.com/sparkfun/SparkFun_LSM6DS3_Arduino_Library
*/

#include "SparkFunLSM6DS3.h"
#include <wiringPiI2C.h>
#include <iostream>

using namespace std;

int main()
{
  LSM6DS3 my_imu(); // constructor
  SensorSettings settingsIWanted;

  /*// if more than 1 device 
  LSM6DS3 SensorOne( I2C_MODE, 0x6A );
  LSM6DS3 SensorTwo( I2C_MODE, 0x6B );
  */
  if (my_imu.begin() != 0)
  {
    cout<< " IMU fail to connect"<< endl;
    return 0;
  }
  else {
     cout<< " IMU to connected!"<< endl;
  }
  
  while (1)
  {
    //printf(
    cout << "acc x: ";
    cout<< my_imu.readFloatAccelX();
    cout<< endl;
    //cout << "acc y: " <<my_imu.readFloatAccelY()<< endl;
    //cout << "acc z: " <<my_imu.readFloatAccelZ()<< endl;
  }
  return (0);
   
    
 
}

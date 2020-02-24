/*
using sparkfun library
reference: https://learn.sparkfun.com/tutorials/lsm6ds3-breakout-hookup-guide/all
github: https://github.com/sparkfun/SparkFun_LSM6DS3_Arduino_Library
*/

#include <SparkFunLSM6DS3.h>
#include <wiringPiI2C.h>

using namespace std;

int main()
{
  LSM6DS3Core my_imu; // constructor
  /*// if more than 1 device 
  LSM6DS3 SensorOne( I2C_MODE, 0x6A );
  LSM6DS3 SensorTwo( I2C_MODE, 0x6B );
  */
  
  if (my_imu.begin() != 0){
    count<< " IMU fail to connect"<< endl;
    return 0;
  }
  else {
     count<< " IMU to connected!"<< endl;
  }
  
  while (True):
  {
    cout << "acc x: " <<my_imu.readfloatAccelX()<< endl;
    cout << "acc y: " <<my_imu.readfloatAccelY()<< endl;
    cout << "acc z: " <<my_imu.readfloatAccelZ()<< endl;
  }
  return (0);
   
    
 
}

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
  uint16_t myImu= LSM6DS3Core ( I2C_MODE, 0x6B );
  
  cout<< "Init result : " << fd<< endl;
  
  while (True):
  {
    cout << "acc x: " <<myImu.readfloatAccelX()<< endl;
    cout << "acc y: " <<myImu.readfloatAccelY()<< endl;
    cout << "acc z: " <<myImu.readfloatAccelZ()<< endl;
  }
  return (0);
   
    
 
}

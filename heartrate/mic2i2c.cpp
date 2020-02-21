#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <errno.h>
#include <SparkFun_ADS1015_Arduino_Library.h>

int main (void)
{
  //int address = 0x48;
  //wiringPiI2CSetup (address) ;
  
  while(1){
  
  uint16_t channel = adcSensor.getSingleEnded(0);
  std::cout << "Readout: ";
  std::cout << channel;
  std::cout << "\t"
  float multiplier = adcSensor.getMultiplier(); // used to convert readings to actual voltages (in mV units)
  // the private varaible _multiplierToVolts is auto-updated each time setGain is called
  std::cout << channel*multiplier;
  std::cout << "mV";
  delay(50); // avoid bogging up serial monitor
  
  }
  
  return 0 ;
}

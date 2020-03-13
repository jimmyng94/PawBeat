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

#define INT_PIN 3 

using namespace std; 
static volatile int counter = 0; 

uint16_t buffer[12000] = {}; 

Adafruit_ADS1015 ads; 

void addValue(uint16_t value){ 
  if(counter < 12000 && value != 4095 ){ 
    ::buffer[counter] = value; 
    counter++; 
  } 
} 

void getValue(void){ 
  //cout << "Get"; 
  uint16_t adc0 = ads.getLastConversionResults();  
  //cout << adc0<< endl;
  uint16_t val = adc0; 
  addValue(val); 
  return; 
}

int main(int argc, char *argv[]) 
{ 
  wiringPiSetup(); 
  pinMode(INT_PIN, INPUT); 

  uint16_t adc0; 

  //double buffer[12000] = {}; 

  int c = 0; 
  //int t = 0; 

  ads.begin(); 
  ads.setGain(GAIN_SIXTEEN); 

  //ads.startComparator_SingleEnded(0,0);
  ads.startComparator_SingleEnded(0, 1000); 
  if(wiringPiISR(INT_PIN, INT_EDGE_RISING, &getValue) > 0){ 
    cout << "INTERRUPT!" << endl; 
  }
  
  int i = 0; 

  while (counter<12000) { 

    /*adc0 = ads.getLastConversionResults(); // ads.readADC_SingleEnded(0); 
    cout << adc0 << endl;

    double val = adc0; 

    if(c == 12000){ 
        c = 0; 
      } 
    buffer[c] = val; 

    cout << c << endl; 

    c++; 
    cout <<"while "<< i << endl; 
    i++; */
   cout<< "main : " << counter << endl;
    usleep(1000000);

  } 
   

  ofstream myfile; 
  myfile.open("heartbeat_30.txt"); 
  
  for (int i = 0; i < 12000; i++){ 
    myfile << ::buffer[i]<< endl; 
  } 

  myfile.close(); 

} 

 

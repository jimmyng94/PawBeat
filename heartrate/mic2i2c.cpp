
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

using namespace std;
 
int main(int argc, char *argv[])
{
  Adafruit_ADS1015 ads;
  uint16_t adc0;
  
  double buffer[2][12000] = {};
  int c = 0;
  int t = 0;
  
  
  ads.begin();
  ads.setGain(GAIN_TWO);
  
  while (c<12000) {
    adc0 = ads.readADC_SingleEnded(0);
    double val = adc0*2.048/4096*2.0;
    
    if(c == 12000){
        c = 0;
      }
    
    buffer[0][c] = val;
    
    buffer[1][c] = t;
    
    cout << c << endl;

    c++;
    t++;
  }
  
  ofstream myfile;
  myfile.open("heartbeat_30.txt");
  for (int i = 0; i < 12000; i++){
    myfile << buffer[0][i];
    myfile << endl;
  }
  myfile.close();
}

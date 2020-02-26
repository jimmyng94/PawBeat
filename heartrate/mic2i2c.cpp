
#include <iostream>
#include <fcntl.h>
#include <inttypes.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
 
//#include <wiringPi.h>
//#include <wiringPiI2C.h>
//#include <errno.h>
//#include <SparkFun_ADS1015_Arduino_Library.h>

int main (){
  
  int addr = 0x48;
  int I2CFile;
  
  uint8_t writeBuf[3]; 
  uint8_t readBuf[2];
  
  int16_t val;
  
  I2CFile = open("/dev/i2c-1", O_RDWR);
  
  ioctl(I2CFile, I2C_SLAVE, addr);

  writeBuf[0] = 1;
  writeBuf[1] = 0xC3;
  writeBuf[2] = 0x03;
while(1){  
  readBuf[0] = 0;
  readBuf[1] = 0;
  
  write(I2CFile, writeBuf, 3);
  while((readBuf[0] & 0x80) == 0){
    read(I2CFile, readBuf, 2);
  }
  
  writeBuf[0] = 0;
  
  write(I2CFile, writeBuf, 1);
  
  read(I2CFile, readBuf, 2);
  
  val = readBuf[0] << 8|readBuf[1];
  
  printf("voltage reading %f (V) \n", (float)val*4.096/32767.0);
  //readBuf[0] = 0;
  //readBuf[1] = 0;
}
  
  close(I2CFile);
  
  return 0 ;
}

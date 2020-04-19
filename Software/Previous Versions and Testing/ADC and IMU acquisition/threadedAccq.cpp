#include <iostream>  
#include <fstream> 
#include <stdio.h>  
#include <vector>  
//#include <windows.h> 
//#include <chrono> 
#include <thread> 
#include <wiringPi.h>  
#include <unistd.h>
#include "ADS1015.h"  
#include "LSM6DS3.h" 

#define INT_PIN 3  

uint8_t results ; 
int data = 0; 

LSM6DS3 imu(I2C_MODE, 0x6A); 
Adafruit_ADS1015 ads; 

int counter; 
bool endLoop = false; 
std::vector <int> adcRaw;
std::vector <double> accRawX, accRawY, accRawZ;

void readData(uint8_t* outputPointer) 
{     
    if (counter < 1000) { 
        uint16_t adcValue = ads.getLastConversionResults();
        if (adcValue <4095){
            adcRaw.push_back(adcValue); 
            accRawX.push_back(imu.readFloatAccelX());
            //std::cout<<imu.readFloatAccelZ()<< std::endl;
            accRawY.push_back(imu.readFloatAccelY());
            accRawZ.push_back(imu.readFloatAccelZ());
            counter++; 
        }
    } 
    else { 
        endLoop = true; 
    } 
} 

void startThread() { 
    std::thread accq1(readData,&results); 
    accq1.join(); 
} 

int main() { 
    // setup interrupt 
    wiringPiSetup(); 
    pinMode(INT_PIN, INPUT); 
    
    // setup ADS1015 & LSM6DS3 
    ads.begin();
    ads.setGain(GAIN_SIXTEEN); 

    //ads.startComparator_SingleEnded(0,0);
    ads.startComparator_SingleEnded(0, 1000); 
    
    if (imu.begin() != 0) 
    { 
        std::cout << "Problem starting the sensor at 0x6A." << std::endl; 
        return 1;
    } 

    else 
    { 
        std::cout << "Sensor at 0x6A started." << std::endl; 
        imu.settings.gyroEnabled =0; 
        imu.settings.accelRange = 2;  //Max G force readable.  Can be: 2, 4, 8, 16
        imu.settings.accelSampleRate = 26; //Hz.  Can be: 13, 26, 52, 104, 208, 416, 833, 1666, 3332, 6664, 13330
        
    }  

    //SET INTERRUPT  
    if (wiringPiISR(INT_PIN, INT_EDGE_RISING, &startThread) > 0) { 
        std::cout << "INTERRUPT!" << std::endl; 
    } 
    std::cout<< "working..." << std::endl;

    while (endLoop== false) { 
        std::cout<< "main : " << counter << std::endl;
        usleep(1000000);
        /*int pre = ::results + 10; 
        std::cout << "from main "  << pre << std::endl; 
        printf("from f %d \n", ::results);*/ 
    } 
    std::cout<<"acclx : " << accRawX.size()<< std::endl; 
    std::cout<<"accly : " << accRawY.size()<< std::endl; 
    std::cout<<"acclz : " << accRawZ.size()<< std::endl; 
    std::ofstream myfile; 
    myfile.open("heartbeat_30.txt");   
    if (adcRaw.empty() == false){
        while (adcRaw.size() != 0) { 
            auto back = accRawZ.back();
            accRawZ.pop_back(); 
            myfile << back << std::endl; 
        } 
    }
    myfile.close(); 
    return 0;

} 

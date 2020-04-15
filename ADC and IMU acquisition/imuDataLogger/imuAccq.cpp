#include <iostream>  
#include <fstream> 
#include <stdio.h>  
#include <vector>  
#include <thread> 
#include <wiringPi.h>  
#include <unistd.h>
#include "LSM6DS3.h" 

#define LED 7
#define writeLED 2
#define Interrupt 0

using namespace std;

LSM6DS3 imu(I2C_MODE, 0x6B); 

bool pinStat = false;
int iter =0;
std::vector <double> accRawX, accRawY, accRawZ;
float x,y,z,px,py,pz;
void collectData(){
    int sample = 0;
    px =0.0;
    py =0.0;
    pz = 0.0;
    while(sample<1200){
        int sleepTime = 1000000/26;
		usleep(sleepTime);
        sample += 1;
        x = imu.readFloatAccelX() ;
        y = imu.readFloatAccelY() ;
        z = imu.readFloatAccelZ() ;
        if(px!= x){
            accRawX.push_back(x);
            px =x;
        }
        if(py!= y){
            accRawY.push_back(y);
            py =y;
        }
        if(pz!= z){
            accRawZ.push_back(z);
            pz =z;
        }
    }
        
}

void startThread() { 
    cout<< "gt it"<< endl;

    if (pinStat == false){
        wiringPiSetup(); 
        pinMode(LED,OUTPUT);
        pinMode(writeLED,OUTPUT);
        pinStat = true;
        digitalWrite(LED, HIGH);
        std::thread accq1(collectData); 
        accq1.join(); 
        cout<< accRawX.size()<< endl;
        cout<< accRawY.size()<< endl;
        cout<< accRawZ.size()<< endl;
        digitalWrite(LED,LOW);
        digitalWrite(writeLED,HIGH);
        string name ;
        ofstream myfile; 
        name = to_string(iter) +"Z.txt";
        myfile.open(name);   
        if (accRawZ.empty() == false){
            while (accRawZ.size() != 0) { 
                auto back = accRawZ.back();
                accRawZ.pop_back(); 
                myfile << back << std::endl; 
            } 
        }
        myfile.close(); 
        
        name = to_string(iter) +"y.txt";
        myfile.open(name);   
        if (accRawY.empty() == false){
            while (accRawY.size() != 0) { 
                auto back = accRawY.back();
                accRawY.pop_back(); 
                myfile << back << std::endl; 
            } 
        }
        myfile.close(); 
        
          name = to_string(iter) +"x.txt";
        myfile.open(name);   
        if (accRawX.empty() == false){
            while (accRawX.size() != 0) { 
                auto back = accRawX.back();
                accRawX.pop_back(); 
                myfile << back << std::endl; 
            } 
        }
        myfile.close(); 
        iter +=1;
        digitalWrite(writeLED,LOW);
        cout<< "ended" << endl;
        pinStat = false;
    }
    else{
        cout<<"no no " << endl;
    }
} 


int main(){
    wiringPiSetup(); 
    pinMode(Interrupt, INPUT); 
    pinMode(LED,OUTPUT);
    digitalWrite(LED, LOW);
    if (imu.begin() != 0) 
    { 
        std::cout << "Problem starting the sensor at 0x6A." << std::endl; 
        
    } 

    else 
    { 
        std::cout << "Sensor at 0x6A started." << std::endl; 
        imu.settings.gyroEnabled =0; 
        imu.settings.accelRange = 2;  //Max G force readable.  Can be: 2, 4, 8, 16
        imu.settings.accelSampleRate = 26; //Hz.  Can be: 13, 26, 52, 104, 208, 416, 833, 1666, 3332, 6664, 13330
        
    }

     while(1){
         usleep(10000);
        if (digitalRead(Interrupt)== HIGH){
            cout<<"High"<<endl;
            startThread();
            
        }
     }
    
    
    
}

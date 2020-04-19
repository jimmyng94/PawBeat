# Software
The PawPulse software is composed of two main files **pawpulse.cpp** and **pawpulseWebClient.cpp**. These files communicate with each other in order to aquire the heartrate and step count of your pet and upload this information, in real-time, to the PawPulse website.
A full-guide on how to install this software and the architecture of the software files is available at the PawPulse [wiki](https://github.com/jimmyng94/PawPulse/wiki).

#### Disclaimer
Due to COVID-19 test on a real dog using this software could not be obtained hence the software was adapted to make use of pre-recorded data obtained earlier from using the PawPulse hadware on a human. If you require to use the PawPulse software with live data from your hardware the following change to the pawpulse.cpp must be made:
```
line 29: bool simulate = true;
```
set this to:
```
line 29: bool simulate = false;
```

## Folders
#### Libraries
This folder defines the location of the required libraries. The ADS1015 and LSM6DS3 libaries have been already included in this folder. The additional required libraries will need to be cloned into this folder during installation. A guide on how to do this can be found [here](https://github.com/jimmyng94/PawPulse/wiki/Installation-Guide).

#### Previous Versions and Testing
This folder contains old code from previous software versions and code used during testing. This folder is included for development purposes and is not required for running the PawPulse software.

#### Website
This folder contains the files used to build the PawPulse website. Again this folder is included for development purposes and is not required for running the PawPulse software. The PawPulse website is hosted using a seperate github repository so that the files in this folder can be edited without effecting the operartion of the website. The PawPulse website can be found [here](https://tymonherzyk.github.io/PawPulseWeb/index.html).

## Files
#### 3Z.txt
This file contains the data recorded from the accelerometer in the z-axis. This file is used by pawpulse.cpp for demosnstartion purposes.

#### 3x.txt
This file contains the data recorded from the accelerometer in the x-axis. This file is used by pawpulse.cpp for demosnstartion purposes.

#### 3y.txt
This file contains the data recorded from the accelerometer in the y-axis. This file is used by pawpulse.cpp for demosnstartion purposes.

#### CMakeLists.txt
This is a cmake file used to build the makefile for pawpulse.cpp. It can be used, after the required libraries have been installed, by running the following code:
```
cmake .
make
```

#### README.md
Readme file for this folder.

#### ads_120_C.txt
This file contains the data recorded from the mircophone for determining heartrate. This file is used by pawpulse.cpp for demosnstartion purposes.

#### hr_coeff.dat
This file contains coefficent data from the heartrate audio filter. This file is used by pawpulse.cpp for demonstration purposes.

#### pawpulse.cpp
This is the first main pawpulse software file. It handles the aquisition and filtering of audio and position data to determine heartrate and step count. It also passes information to the pawpulseWebClient.cpp for uploading to the PawPulse website. This file is built using CMakeLists.txt

#### pawpulseWebClient.cpp 
This is the second main pawpulse software file. It communicates with pawpulse.cpp and handles data uploading in real-time using the the PubNub API. This file is built using pawpulseWebClient.mk

#### pawpulseWebClient.mk
This is the makefile for pawpulseWebClient.cpp it has been adapted from the PubNub cpp posix makefile. It can be used, after the required libraries have been installed, by running the following code:
```
make -f pawpulseWebClient.mk
```

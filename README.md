# PawPulse
![logo](https://github.com/jimmyng94/PawPulse/blob/master/Other/Media/PawPulseLogo.png?raw=true)

PawPulse is an [open-source](https://github.com/jimmyng94/PawPulse/blob/master/LICENSE) pet health monitoring project developed by Engineering MSc students at the University Of Glasgow using a Raspberry Pi. The main functions that the project provide are:
- Heartbeat Monitoring
- Pedometer
- Live data display through a [website](https://tymonherzyk.github.io/PawPulseWeb/)

Currently, the development of the project is only intended to be used on a dog. Usage on other pets will require further testing.

## Project Architecture
![Basic Design](https://github.com/jimmyng94/PawPulse/blob/master/Other/Media/PawPulseDiagram.png?raw=true)
#### Hardware
All the sensors along with the raspberry will be attached to a dog harness to collect and process the data before posting the data to the web page. Therefore, the PCB is split into 2 individual boards. The 1st board is a PiHat where the [IMU](https://www.st.com/resource/en/datasheet/lsm6ds3.pdf) is located. The 2nd board contains the [ADC](http://www.ti.com/lit/ds/symlink/ads1015.pdf) and is located beside the microphone. Both boards are using I2C to communicate with the Raspberry Pi.

![img2](https://github.com/jimmyng94/PawPulse/blob/master/Other/Media/image2.jpeg?raw=true)

![img8](https://github.com/jimmyng94/PawPulse/blob/master/Other/Media/image8.jpeg?raw=true)

#### Software
The PawPulse software is split into two main files: "pawpulse.cpp" and "pawpulseWebClient.cpp". The pawpulse file is responsible for aquiring data for the dog's heartbeat and step count from the corresponding hardware. Once the data has been aquired through the "getBPM" and "getStep" functions it is then passed to the "writeBPM" and "writeSTEP" functions. These functions sort the data into the correct JSON format and pass it to the pawpulseWebClient file through named pipes "bpm_fifo" and "step_fifo". The pawpulseWebClient file is responsible for uploading the data to the PawPulse website through the PubNub API. Threading has been used throughout the software to allow both processes (bpm and step) to work at the same time.  

![Macro Software Architecture](https://github.com/jimmyng94/PawPulse/blob/master/Other/Media/macroSoftwareArchitecture.PNG?raw=true)

#### Website
A website has been built in order to test the web capabilities of this project. The website has been designed to function as a profesional space in which the data from the PawPulse system can be displayed to users in real-time. The website has been built using HTML, CSS and JavaScript languages. To display data in real-time it utlises libraries such as PubNub API and EON. The website has also been built to be responsive and hence can be viewed safely on phone and monitors. Example screenshots from the "Live Data" page are given below:

![Web Monitor](https://github.com/jimmyng94/PawPulse/blob/master/Other/Media/websiteMonitor.PNG?raw=true)

![Web Phone](https://github.com/jimmyng94/PawPulse/blob/master/Other/Media/websitePhone.PNG?raw=true)

The PawPulse website is hosted at https://tymonherzyk.github.io/PawPulseWeb/

#### Guides
Further information as well as in-depth installation and development guides for this project can be found on our Github [Wiki](https://github.com/jimmyng94/PawPulse/wiki) Page.

## Quick Installation
A full in-depth installation guide is available in our [wiki](https://github.com/jimmyng94/PawPulse/wiki/Installation).

#### 1. Clone PawPulse github repository
On the main repository page, click the green "Clone or Download" button, copy the address that drops down. In your chosen directory clone the PawPulse repository by running the folowing code:
```
git clone *copied address*
```
#### 2. Install required libraries
Install the required libraries in the "Libraries" folder:
* ADS1015 Library
* Fir1 Library
* PubNub c-core
* SparkFun blah Library
* WiringPi

#### 3. Make the pawpulse.cpp executable
To make the pawpulse executable file navigate into the "Software" folder and use the "CMakeLists.txt" file. This is done by running the following code:
```
cmake .
make
```
A new executable with the name "pawpulse" should now be available in the "Software" folder.

#### 4. Make the pawpulseWebClient.cpp executable
To make the pawpulseWebClient executable file navigate into the "Software" folder and use the "pawpulseWebClient.mk" makefile. This is done by running the following code:
```
make -f pawpulseWebClient.mk
```
A new executable with the name "pawpulseWebClient" should now be available in the "Software" folder.

#### 5. Run software

## Additional Functionality
Recommendations of possible functions that could be added in the future: 
- Automated execution of the PawPulse software.
- Live heartbeat playback allowing the owner to hear their pet's heartbeat and make it more convenient for a veterinarian to monitor pets
- GPS tracking
- Health diagnoses and recommendations
- Personalised website login
- Phone application development for convenience

## Demonstration
A demonstartion of the real-time application and operation of the PawPulse software is available on the PawPulse youtube [channel](https://www.youtube.com/channel/UC-eADsYPdyjXFOSjoH-YVWg). The demonstartion shows the software being executed and the data being uploaded to the PawPulse website in real-time.

Video Link - https://www.youtube.com/watch?v=mI9MpOQwHOM

## Social Media
- [Instagram](https://www.instagram.com/paw_pulse/)
- [Youtube](https://www.youtube.com/channel/UC-eADsYPdyjXFOSjoH-YVWg)
- [Twitter](https://twitter.com/paw_pulse)

## Authors 
- [Maggie Wood](https://github.com/maggwood)n-
- [Ng Jing Ming](https://github.com/jimmyng94) -
- [Tymon Herzyk](https://github.com/tymonherzyk) - WebClient and Website author

## Disclaimer
Disruption due to COVID-19 has prohibited us from running any actual tests on our test dog. Thus, this project is not guaranteed to work on a dog. Testing was only done using a human heartbeat that was collected before the disruption. In the future we hope to be able to test it on a real pet and collect more data to improve our algorithm. Thank you for your understanding.


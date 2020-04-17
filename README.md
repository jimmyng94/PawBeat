# PawPulse
![logo](https://github.com/jimmyng94/PawPulse/blob/master/PPLogo.png?raw=true)

PawPulse is an [open-source](https://github.com/jimmyng94/PawPulse/blob/master/LICENSE) pet health monitoring project developed by Engineering MSc students at the University Of Glasgow using a Raspberry Pi. The main functions that the project provide are:
- Heartbeat Monitoring
- Pedometer
- Live data display through a [website](https://tymonherzyk.github.io/PawPulseWeb/)

Currently, the development of the project is only intended to be used on a dog. Usage on other pets will require further testing.

## Project Architecture
![Basic Design](https://github.com/jimmyng94/PawPulse/blob/master/media/PawPulseDiagram.png?raw=true)
#### Hardware
All the sensors along with the raspberry will be attached to a dog harness to collect and process the data before posting the data to the web page. Therefore, the PCB is split into 2 individual boards. The 1st board is a PiHat where the [IMU](https://www.st.com/resource/en/datasheet/lsm6ds3.pdf) is located. The 2nd board contains the [ADC](http://www.ti.com/lit/ds/symlink/ads1015.pdf) and is located beside the microphone. Both boards are using I2C to communicate with the Raspberry Pi.

![img2](https://github.com/jimmyng94/PawPulse/blob/master/media/image2.jpeg?raw=true)

![img8](https://github.com/jimmyng94/PawPulse/blob/master/media/image8.jpeg?raw=true)

#### Software
The PawPulse software is split into two main files: `processing` and `sendDataClient`. The `processing` file is responsible for aquiring data for the dog's heartbeat and steps from the corresponding hardware. Once the data has been aquired through the `getBPM` and `getStep` functions it is then passed to the `writeBPM` and `writeSTEP` functions. These functions sort the data into the correct JSON format and pass it to the `sendDataClient` file through named pipes `bpm_fifo` and `step_fifo`. The `sendDataClient` file is responsible for uploading the data to the PawPulse website through the PubNub API. Threading has been used throughout the software to allow both processes (bpm and step) to work at the same time.  

![Macro Software Architecture](https://github.com/jimmyng94/PawPulse/blob/master/media/macroSoftwareArchitecture.PNG?raw=true)

#### Website
A website has been built in order to test the web capabilities of this project. The website has been designed to function as a profesional space in which the data from the PawPulse system can be displayed to users in real-time. The website has been built using HTML, CSS and JavaScript languages. To display data in real-time it utlises libraries such as PubNub API and EON. The website has also been built to be responsive and hence can be viewed safely on phone and monitors. Example screenshots from the "Live Data" page are given below:

![Web Monitor](https://github.com/jimmyng94/PawPulse/blob/master/media/websiteMonitor.PNG?raw=true)

![Web Phone](https://github.com/jimmyng94/PawPulse/blob/master/media/websitePhone.PNG?raw=true)

The PawPulse website is hosted at https://tymonherzyk.github.io/PawPulseWeb/

#### Guides
Further information as well as in-depth installation and development guides for this project can be found on our Github [Wiki](https://github.com/jimmyng94/PawPulse/wiki) Page.

## Quick Installation
A full in-depth installation guide is available in our [wiki](https://github.com/jimmyng94/PawPulse/wiki/Installation).

#### 1. Clone PawPulse github repository
On the main repository page, click the green "Clone or Download" button, copy the address that drops down and in your chosen directory on the Raspberry Pi terminal, type the following:
```
git clone *copied address*
```
#### 2. Install required libraries
Install the required libraries in the correct destinations:
* ADS1015 Library
* Fir1 Library
* PubNub c-core
* SparkFun blah Library
* WiringPi

#### 3. Make the processing.cpp executable
To make the `processing` executable file navigate into the ? folder. Once in this folder run the following code:
```
cmake .
make
```
A new executable with the name "processing" should now be available in this folder.

_If you want to make the processing demonstration executable file, simply navigate to the demo folder and run the same code. This will make processingDemo executable file._

#### 4. Make the sendDataClient.cpp executable
To make the `sendDataClient` executable file navigate into the folder containing `sendDataClient`. Once in this directory run the following code:
```
make -f sendDataClient.mk
```
A new executable with the name "sendDataClient" should now be available in this folder.

#### 5. Run software

## Additional Functionality
Recommendations of possible functions that could be added in the future: 
- Live heartbeat playback allowing the owner to hear their pet's heartbeat and make it more convenient for a veterinarian to monitor pets
- GPS tracking
- Health diagnoses and recommendations
- Personalised website login so each user can view data separately
- Phone application development for convenience

## Social Media
- [Instagram](https://www.instagram.com/paw_pulse/)
- [Twitter](https://twitter.com/paw_pulse)

## Authors 
- [Maggie Wood](https://github.com/maggwood)n-
- [Ng Jing Ming](https://github.com/jimmyng94) -
- [Tymon Herzyk](https://github.com/tymonherzyk) - WebClient and Website author

## Disclaimer
Disruption due to COVID-19 has prohibited us from running any actual tests on our test dog. Thus, this project is not guaranteed to work on a dog. Testing was only done using a human heartbeat that was collected before the disruption. In the future we hope to be able to test it on a real pet and collect more data to improve our algorithm. Thank you for your understanding.


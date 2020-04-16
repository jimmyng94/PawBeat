# PawPulse
![logo](https://github.com/jimmyng94/PawPulse/blob/master/PPLogo.png?raw=true)

PawPulse is an [open-source](https://github.com/jimmyng94/PawPulse/blob/master/LICENSE) pet health monitoring project developed in University Of Glasgow using a Raspberry Pi. The main functions that the project provide are:
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
The PawPulse software is split into two main files "processing" and "sendDataClient". The "processing" software is responsible for aquiring data for heartbeat and steps from the corresponding hardware. Once the data has been aquired through the "getBPM" and "getSTEP" functions it is then passed to the "writeBPM" and "writeSTEP" functions. These function sort the data into the correct JSON format and passes this data to the "sendDataClient" through named pipes "bpm_fifo" and "step_fifo". The "sendDataClient" is responsible for uploading the data to the PawPulse website through the PubNub API. Threading has been used throughout the software to allow both processes (bpm and step) to work at the same time.  

![Macro Software Architecture](https://github.com/jimmyng94/PawPulse/blob/master/media/macroSoftwareArchitecture.PNG?raw=true)

For further information about our software and a full installation guide please refer to our [wiki](https://github.com/jimmyng94/PawPulse/wiki) pages.

#### Website
![Web Image]( )

[Website link](https://tymonherzyk.github.io/PawPulseWeb/)
#### Guide
The details and complete guide of the project could be found on our [Github Wiki](https://github.com/jimmyng94/PawPulse/wiki) Page.

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
- [Maggie Wood](https://github.com/maggwood)
- [Ng Jing Ming](https://github.com/jimmyng94)
- [Tymon Herzyk](https://github.com/tymonherzyk)

## Disclaimer
Disruption due to COVID-19 has prohibited us from running any actual tests on our test dog. Thus, this project is not guaranteed to work on a dog. Testing was only done using a human heartbeat that was collected before the disruption. In the future we hope to be able to test it on a real pet and collect more data to improve our algorithm. Thank you for your understanding.


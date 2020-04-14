# PawPulse
![logo](https://github.com/jimmyng94/PawPulse/blob/master/PPLogo.png?raw=true)

PawPulse is an [open-source](https://github.com/jimmyng94/PawPulse/blob/master/LICENSE) pet health monitoring project developed in University Of Glasgow using a Raspberry Pi. The main functions that the project provide are:
- Heartbeat Monitoring
- Pedometer
- Live data display through a [website](https://tymonherzyk.github.io/PawPulseWeb/)

Currently, the development of the project is only intended to be used on a dog. Usage on other pets will require further testing.

## Project Architecture
![Basic Design]()
#### Hardware
The PCB is split into 2 individual boards. The 1st board is a PiHat where the [IMU](https://www.st.com/resource/en/datasheet/lsm6ds3.pdf) is located. The 2nd board contains the [ADC](http://www.ti.com/lit/ds/symlink/ads1015.pdf) and is located beside the microphone. Both boards are using I2C to communicate with the Raspberry Pi.

![PCB Design2](https://github.com/jimmyng94/PawPulse/blob/master/Hardware/V1/piHatV1/pihat.PNG?raw=true)
#### Web Interface
![Web Image]( )

[Website](https://tymonherzyk.github.io/PawPulseWeb/)
#### Guide
The details and complete guide of the project could be found on our [Github Wiki](https://github.com/jimmyng94/PawPulse/wiki) Page.

## Additional Functionality
Recommendations of possible functions that could be added in the future: 
- Live heartbeat playback allowing the owner to hear their pet's heartbeat and make it more convenient for a veterinarian to monitor pets
- GPS tracking
- Health diagnoses and recommendations
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


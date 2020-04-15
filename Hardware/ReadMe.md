# Hardware
Hardware development of this project went through a few development and testing to determine the best circuit used for this project. 
This project requires an analog to digital converter to convert the analog microphone signal and an inertial measurement unit for pedometer function. 
The selected component used for version 1 of this project is listed below.
The schematic, board design and PCB mask are included in the newest version.  

## Version 0 (Concept)
- Mic signal is passed through a 4th order Low pass filter that filters noise above 1kHz. Used a [LM324N](http://www.ti.com/lit/ds/symlink/lm324-n.pdf). All the components are located in MicBOB_V0. 
- The IMU selected is attached on a PiHat. Fairly straight forward
###### Problems
- The Low pass filter seems to be attenuating the signal and no signal reaches the ADC.
- Missing power line to the VCC of the IMU.

## Version 1 (Prototype A)
- Removed the Low Pass Filter and used the ADS1014 Programmable Gain Amplifier(PGA) to amplify the signal from the microphone.
- Added a diode for reverse voltage protection.
- Added a trace to supply power to the IMU.

| Part | Quantity|
|-----| :-----: |
|Raspberry Pi | 1|
|[ADC ADS1014](http://www.ti.com/lit/ds/symlink/ads1015.pdf)|1|
|[IMU LSM6DS3](https://www.st.com/resource/en/datasheet/lsm6ds3.pdf)|1|
|6mm Microphone|1|
|1206 0.1uf Capacitor |2|
|5K Resistor|4|
|1N4148 Diode|1|
|20-pin Female Header|1|
|6-way header Molex connector|2|
|6-way shell Molex connector|2|
|M2.5 Standoffs	|4|
|M2.5 Screws	|4|

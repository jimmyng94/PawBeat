#include "LSM6DS3"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <thread.h>
#include <chrono.h>

int main()
{

	LSM6DS3Core imu(I2C_MODE, 0x6B);

	if (imu.beginCore() !=0)
	{
		printf("Error at beginCore().\n");
	}
	else
	{
		printf(\nbeginCore() passed.\n");
	}

	uint8_t errorAccumulator =0;

	uint8_t dataToWrite = 0;
	// setup accelerometer
	dataToWrite = 0;

	dataToWrite |= LSM6DS3_ACC_GYRO_FS_XL_2g;
	dataToWrite |= LSM6DS3_ACC_GYRO_ODR_XL_26Hz;

	//Now, write the patched together data
	errorAccumulator += imu.writeRegister(LSM6DS3_ACC_GYRO_CTRL1_XL, dataToWrite);

	//Set the ODR bit
	errorAccumulator += imu.readRegister(&dataToWrite, LSM6DS3_ACC_GYRO_CTRL4_C);
	dataToWrite &= ~((uint8_t)LSM6DS3_ACC_GYRO_BW_SCAL_ODR_ENABLED);
	
	// Enable embedded functions -- ALSO clears the pdeo step count
	errorAccumulator += imu.writeRegister(LSM6DS3_ACC_GYRO_CTRL10_C, 0x3E);
	// Enable pedometer algorithm
	errorAccumulator += imu.writeRegister(LSM6DS3_ACC_GYRO_TAP_CFG1, 0x40);
	// Step Detector interrupt driven to INT1 pin
	errorAccumulator += imu.writeRegister( LSM6DS3_ACC_GYRO_INT1_CTRL, 0x10 );
	
	if( errorAccumulator )
	{
		printf("Problem configuring the device.\n");
	}
	else
	{
		printf("Device O.K.\n");
	}
	
	while(1)
	{
		uint8_t readDataByte = 0;
		uint16_t stepsTaken = 0;
    
		//Read the 16bit value by two 8bit operations
		imu.readRegister(&readDataByte, LSM6DS3_ACC_GYRO_STEP_COUNTER_H);
		stepsTaken = ((uint16_t)readDataByte) << 8;
	
		imu.readRegister(&readDataByte, LSM6DS3_ACC_GYRO_STEP_COUNTER_L);
		stepsTaken |= readDataByte;
	
	
		//Display steps taken
		Serial.print("Steps taken: %f \n", stepsTaken);
		std::this_thread::sleep_for (std::chrono::seconds(1));
 
	}
}

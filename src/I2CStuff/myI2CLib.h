/*
 * myI2CLib.h
 *
 * Created: 20/04/2018 15:53:31
 *  Author: practiques
 */ 


#ifndef MYI2CLIB_H_
#define MYI2CLIB_H_

#include <stdlib.h>
#include <string.h>

#include "gpio.h"
#include "pm.h"
#include "twi.h"
#include "dip204.h"

#include "FreeRTOS.h"
#include "semphr.h"

/***************** I2C Part ***************/
#define TWI_SPEED             50000       // Speed of TWI


#define LSM9DS1_ACC_ADDRESS 0x6B
#define LSM9DS1_MAG_ADDRESS 0x1E
#define CTRL_REG6_XL 0x20	// Accelerometer register
#define ACCEL_SENSOR_X_h 0x29
#define ACCEL_SENSOR_Z_h 0x2D
#define ACCEL_SENSOR_Y_h 0x2B
#define ACCEL_SENSOR_X_l 0x28
#define ACCEL_SENSOR_Z_l 0x2C
#define ACCEL_SENSOR_Y_l 0x2A


/* Unused defines */
#define CCS811_ADDRESS 0x5B
#define RGB_SENSOR 0x44
#define BME280_ADDR 0x77
#define MAX30105_ADDR 0x57
#define GESTURE_ADDR 0x39

bool I2C_writeRegister(uint8_t dev_addr, uint8_t reg_addr, uint8_t data);
bool I2C_readRegister(uint8_t dev_addr, uint8_t reg_addr, uint8_t* data);
void I2C_Init(void);



#endif /* MYI2CLIB_H_ */
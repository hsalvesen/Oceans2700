/*
 * gyro.c
 *
 *  Created on: May 24, 2023
 *      Author: swric
 */
#include "gyro.h"

int16_t read_gyro(uint32_t axis) {

	uint8_t xMSB = 0x00;
	uint8_t xLSB = 0x00;

	HAL_I2C_Mem_Read(&hi2c1,gyro_rd, axis+1, 1, &xMSB, 1, 10);
	HAL_I2C_Mem_Read(&hi2c1,gyro_rd, axis, 1, &xLSB, 1, 10);
	return (xMSB << 8) | xLSB;
}

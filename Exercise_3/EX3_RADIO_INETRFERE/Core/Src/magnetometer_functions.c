#include "main.h"

#define MAG_READ 0x3C
#define MAG_WRITE 0x3D
#define LSM303AGR_BlockUpdate_Continuous ((uint8_t)0x00) /*!< Continuous Update */
#define LSM303AGR_CFG_REG_A_M 0x60  /* Configuration register A magnetic field */
#define LSM303AGR_ODR_220_HZ ((uint8_t) 0x1C)  /*!< Output Data Rate = 220 Hz */


float string[64];

void mag_config(){
	uint8_t configValue = LSM303AGR_ODR_220_HZ;
	HAL_I2C_Mem_Write(&hi2c1, MAG_WRITE, LSM303AGR_CFG_REG_A_M, 1, &configValue, 1, 10);

	uint8_t mode = LSM303AGR_BlockUpdate_Continuous;
	HAL_I2C_Mem_Write(&hi2c1, MAG_WRITE, 0x22, 1, &mode, 1, 10);

	uint8_t magregValue = 0x57;
	HAL_I2C_Mem_Write(&hi2c1, MAG_WRITE, 0x20, 1, &magregValue, 1, 10);
}

float read_x_data(){

	float x_data;
	uint8_t magXm;
	HAL_I2C_Mem_Read(&hi2c1, MAG_READ, 0x69, 1, &magXm, 1, 1000);
	uint8_t magXl;
	HAL_I2C_Mem_Read(&hi2c1,MAG_READ, 0x68, 1, &magXl, 1, 1000);
	int16_t magX = (((magXm << 8) | magXl));
	x_data = magX;

	return x_data;
}

float read_y_data(){
	float y_data;
	uint8_t magYm;
	HAL_I2C_Mem_Read(&hi2c1,MAG_READ, 0x6B, 1, &magYm, 1, 1000);
	uint8_t magYl;
	HAL_I2C_Mem_Read(&hi2c1,MAG_READ, 0x6A, 1, &magYl, 1, 1000);
	int16_t magY = (((magYm << 8) | magYl));
	return y_data = magY;
}

float read_z_data(){
	float z_data;
	uint8_t magZm;
	HAL_I2C_Mem_Read(&hi2c1,MAG_READ, 0x6D, 1, &magZm, 1, 1000);
	uint8_t magZl;
	HAL_I2C_Mem_Read(&hi2c1,MAG_READ, 0x6C, 1, &magZl, 1, 1000);
	int16_t magZ = (((magZm << 8) | magZl));
	return z_data = magZ;
}


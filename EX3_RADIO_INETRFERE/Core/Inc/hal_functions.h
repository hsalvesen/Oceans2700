/*
 * hal_functions.h
 *
 *  Created on: 24 May 2023
 *      Author: Matylda
 */

#ifndef INC_HAL_FUNCTIONS_H_
#define INC_HAL_FUNCTIONS_H_

#include "main.h"

extern ADC_HandleTypeDef hadc1;

extern I2C_HandleTypeDef hi2c1;

extern UART_HandleTypeDef huart1;

extern PCD_HandleTypeDef hpcd_USB_FS;

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_I2C1_Init(void);
void MX_USB_PCD_Init(void);
void MX_ADC1_Init(void);
void MX_USART1_UART_Init(void);


#endif /* INC_HAL_FUNCTIONS_H_ */

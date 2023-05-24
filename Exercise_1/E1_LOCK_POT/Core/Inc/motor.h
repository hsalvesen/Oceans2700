/*
 * motor.h
 *
 *  Created on: May 24, 2023
 *      Author: haz
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "main.h"

volatile uint16_t move_motor(volatile uint16_t vertical_PWM, uint32_t angle);

#endif /* INC_MOTOR_H_ */

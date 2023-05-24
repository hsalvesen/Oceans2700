/*
 * motor.c
 *
 *  Created on: May 24, 2023
 *      Author: haz
 */
#include "motor.h"

volatile uint16_t move_motor(volatile uint16_t vertical_PWM, uint32_t angle) {
	while (vertical_PWM != angle) {
		if (vertical_PWM < angle) {
			vertical_PWM += 5;
		} else {
			vertical_PWM -= 5;
		}
		TIM2->CCR1 = vertical_PWM;
	}
	return vertical_PWM;
}

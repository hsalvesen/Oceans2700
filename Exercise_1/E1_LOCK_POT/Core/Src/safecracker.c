#include "safecracker.h"

void generate_target_angles(uint32_t angles_degrees[5]) {
	for (uint32_t i = 0; i < 5; i++) {
		angles_degrees[i] = (SysTick->VAL % 181); // generate a random number within the loop
	}
}

void run_safecracker() {
	volatile uint16_t vertical_PWM = 1000;
	uint8_t current_state = 0;
	uint8_t led_on = 0;
	uint32_t led_timestamp = 0;
	uint32_t state_timestamp = 0;
	uint32_t angles_degrees[NUM_ENTRIES];
	uint32_t DEGREES_TO_SERVO = 1900 / 180;
	uint32_t target_angle, robot_angle;
	generate_target_angles(angles_degrees);
	// delay for initialisation of the lidar
	while (current_state < NUM_ENTRIES) {
		robot_angle = angles_degrees[current_state]
				* DEGREES_TO_SERVO+ ROBOT_ZERO_ANGLE;
		HAL_Delay(1000);
		vertical_PWM = move_motor(vertical_PWM, robot_angle);
		HAL_Delay(1000);
		vertical_PWM = move_motor(vertical_PWM, RESET_ANGLE);
		uint32_t adcValue = getADCValue();
		target_angle = angles_degrees[current_state]
				* (UPPER_CALIBRATION - LOWER_CALIBRATION)
				/ 180.0+ LOWER_CALIBRATION;
		if (abs(adcValue - target_angle) <= TOLERANCE) {
			if (state_timestamp == 0) {
				state_timestamp = HAL_GetTick();
			} else if (HAL_GetTick() - state_timestamp > 1000) {
				current_state++;
				state_timestamp = 0;
				led_timestamp = HAL_GetTick();
				if (current_state == 5) {
					HAL_GPIO_WritePin(FINISHED_LOCK_GPIO_PORT,
							FINISHED_LOCK_PIN, GPIO_PIN_SET);
					HAL_UART_Transmit(&huart1, (uint8_t*) "]", strlen("]"),
							HAL_MAX_DELAY);
					led_on = 2;
					break;
				} else {
					led_on = 1;
				}
			}
		} else {
			state_timestamp = 0;
		}
		if (led_on) {
			HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_SET); // Turn on the LED
			if (led_on == 1 && HAL_GetTick() - led_timestamp >= 3000) // Check if 3 seconds have passed and led_on is not 2
					{
				led_on = 0;
				HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_RESET); // Turn off the LED
			}
		} else {
			HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_RESET); // Turn off the LED
		}
	}
}

#ifndef ROBOT_MOVEMENT_H
#define ROBOT_MOVEMENT_H

#include <stdint.h>	

uint16_t reset_angle;
uint8_t correct_entry;
uint8_t current_state;
uint8_t led_on;
uint32_t led_timestamp;
uint32_t state_timestamp[5];
uint32_t predefined_angles_degrees[5];
uint32_t predefined_angles_adc[5];
uint32_t angles_robot[5];
uint32_t robot_zero_angle;
uint32_t upper_calibration;
uint32_t lower_calibration;
uint32_t tolerance;
uint32_t degrees_to_servo;

void start_robot();
  
#endif

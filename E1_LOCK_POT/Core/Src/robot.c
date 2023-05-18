#include <stdint.h>

#include "robot.h"

void start_robot()
{
  reset_angle = 1600;
  correct_entry = 0;
  current_state = 0;
  led_on = 0;
  led_timestamp = 0;
  state_timestamp = {0, 0, 0, 0, 0};
  predefined_angles_adc = {0, 0, 0, 0, 0};
  angles_robot = {0, 0, 0, 0, 0};
  robot_zero_angle = 650;
  upper_calibration = 3800;
  lower_calibration = 1200;
  tolerance = 400;
  degrees_to_servo = 1900/180;
  
	for (uint32_t i = 0; i < 5; i++)
	{
	    predefined_angles_degrees[i] = (SysTick->VAL % 181); // generate a random number within the loop

	    angles_robot[i] = predefined_angles_degrees[i]*degrees_to_servo + robot_zero_angle;
	    predefined_angles_adc[i] = predefined_angles_degrees[i]*(upper_calibration - lower_calibration) / 180.0 + lower_calibration;
	}

	uint8_t num_entries = (sizeof(angles_robot)/sizeof(angles_robot[0]));

	// delay for initialisation of the lidar
	for (uint8_t i = 0; i < num_entries; i++)
	{
		correct_entry = 0;
		HAL_Delay(1000);
	while (vertical_PWM != angles_robot[i])
	{
		if (vertical_PWM < angles_robot[i]) {
			vertical_PWM += 5;
		}
		else {
			vertical_PWM -= 5;
		}
		TIM2->CCR1 = vertical_PWM;
	}
	HAL_Delay(1000);
	while (vertical_PWM != reset_angle)
	{
		if (vertical_PWM < reset_angle) {
			vertical_PWM += 5;
		}
		else {
			vertical_PWM -= 5;
		}
		TIM2->CCR1 = vertical_PWM;
	}
    /* USER CODE BEGIN 3 */
		{
		    uint32_t adcValue = 0;
		    HAL_ADC_Start(&hadc1); // Start ADC1 (or the appropriate ADCx for your specific microcontroller)
		    if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
		    {
		        adcValue = HAL_ADC_GetValue(&hadc1); // Read the ADC value
		    }
		    HAL_ADC_Stop(&hadc1);

		    switch (current_state)
		    {
		    // 135 degrees
		    case 0:
		        if (adcValue >= (predefined_angles_adc[0] - tolerance) && adcValue <= (predefined_angles_adc[0] + tolerance))
		        {
		            if (state_timestamp[current_state] == 0)
		            {
		                state_timestamp[current_state] = HAL_GetTick();
		            }
		            else if (HAL_GetTick() - state_timestamp[current_state] > 1000)
		            {
		                current_state = 1;
		                led_on = 1;
		                correct_entry = 1;
		                led_timestamp = HAL_GetTick();
		            }
		        }
		        else
		        {
		            state_timestamp[current_state] = 0;
		        }
		        break;
		    // 45 degrees
		    case 1:
		    	if (adcValue >= (predefined_angles_adc[1] - tolerance) && adcValue <= (predefined_angles_adc[1] + tolerance))
		        {
		            if (state_timestamp[current_state] == 0)
		            {
		                state_timestamp[current_state] = HAL_GetTick();
		            }
		            else if (HAL_GetTick() - state_timestamp[current_state] > 1000)
		            {
		                current_state = 2;
		                led_on = 1;
		                correct_entry = 1;
		                led_timestamp = HAL_GetTick();
		            }
		        }
		        else
		        {
		            state_timestamp[current_state] = 0;
		        }
		        break;
		    // 	180 degrees
		    case 2:
		    	if (adcValue >= (predefined_angles_adc[2] - tolerance) && adcValue <= (predefined_angles_adc[2] + tolerance))
		        {
		            if (state_timestamp[current_state] == 0)
		            {
		                state_timestamp[current_state] = HAL_GetTick();
		            }
		            else if (HAL_GetTick() - state_timestamp[current_state] > 1000)
		            {
		                current_state = 3;
		                led_on = 1;
		                correct_entry = 1;
		                led_timestamp = HAL_GetTick();
		            }
		        }
		        else
		        {
		            state_timestamp[current_state] = 0;
		        }
		        break;
		    // 0 degrees
		    case 3:
		    	if (adcValue >= (predefined_angles_adc[3] - tolerance) && adcValue <= (predefined_angles_adc[3] + tolerance))
		        {
		            if (state_timestamp[current_state] == 0)
		            {
		                state_timestamp[current_state] = HAL_GetTick();
		            }
		            else if (HAL_GetTick() - state_timestamp[current_state] > 1000)
		            {
		                current_state = 4;
		                led_on = 1;
		                correct_entry = 1;
		                led_timestamp = HAL_GetTick();
		            }
		        }
		        else
		        {
		            state_timestamp[current_state] = 0;
		        }
		        break;
		    // 90 degrees
		    case 4:
		    	if (adcValue >= (predefined_angles_adc[4] - tolerance) && adcValue <= (predefined_angles_adc[4] + tolerance))
		        {
		            if (state_timestamp[current_state] == 0)
		            {
		                state_timestamp[current_state] = HAL_GetTick();
		            }
		            else if (HAL_GetTick() - state_timestamp[current_state] > 1000)
		            {
		                current_state = 5;
		                led_on = 2;
		                correct_entry = 1;
		                // Unlock
		                HAL_GPIO_WritePin(FINISHED_LOCK_GPIO_PORT, FINISHED_LOCK_PIN, GPIO_PIN_SET);

		            }
		        }
		        else
		              {
		                  state_timestamp[current_state] = 0;
		              }
		              break;
		          default:
		              break;
		          }

			  if (led_on)
			  {
				  HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_SET); // Turn on the LED
				  if (led_on == 1 && HAL_GetTick() - led_timestamp >= 3000) // Check if 3 seconds have passed and led_on is not 2
				  {
					  led_on = 0;
					  HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_RESET); // Turn off the LED
				  }
			  }
			  else
			  {
				  HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_RESET); // Turn off the LED
			  }
	if (correct_entry != 1)
	{
		i = i-1;
	}
	}
  /* USER CODE END 3 */
	}
}

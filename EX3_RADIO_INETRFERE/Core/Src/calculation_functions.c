#include "main.h"
#include <math.h>
#include <stdbool.h>

#define ARRAY_SIZE 10

char string1[64];

void shuffle_array(float array[], float degrees){
	for(int i = 1; i < ARRAY_SIZE; i ++){
		array[i - 1] = array[i];
	}
	array[ARRAY_SIZE - 1] = degrees;
	return array;
}

float calculate_degrees(float x_data, float y_data){
	double degrees, y_on_x;
	double pi = 3.14159;
	if(x_data != 0 && y_data != 0){
			//determining which quadrant the mag is facing
			if(x_data > 0 && y_data > 0){
				y_on_x = (y_data/x_data);
				degrees = atan(y_on_x)*(180/pi);
				while(degrees >= 360){
					degrees = degrees - 360;
				}
			}
			else if (x_data < 0 && y_data > 0){
				y_on_x = (y_data/x_data);
				degrees = atan(y_on_x)*(180/pi) + 180;
				while(degrees >= 360){
					degrees = degrees - 360;
				}
			}
			else if (x_data < 0 && y_data < 0){
				y_on_x = (y_data/x_data);
				degrees = atan(y_on_x)*(180/pi) + 180;
				while(degrees >= 360){
					degrees = degrees - 360;
				}
			}
			else if (x_data > 0 && y_data < 0){
				y_on_x = (y_data/x_data);
				degrees = atan(y_on_x)*(180/pi) + 360;
				while(degrees >= 360){
					degrees = degrees - 360;
				}
			}
			else{

			}

		}
		else if(x_data == 0 && y_data > 0){
			degrees = 90;
		}
		else if(x_data == 0 && y_data < 0){
			degrees = 270;
		}
		else if(y_data == 0 && x_data > 0){
			degrees = 0;
		}
		else if (y_data == 0 && x_data < 0){
			degrees = 180;
		}

	return degrees;
}

float calculate_average(float array[], float degrees, int count){
	float average;

	sprintf(string1, "INSIDE FUNCTION\r\n");
	HAL_UART_Transmit(&huart1, string1, strlen(string1), HAL_MAX_DELAY);

	if (array[ARRAY_SIZE - 1] == 0){
		array[count] = degrees;
		return (-1);
	}
	else{
		//shuffle the array
		shuffle_array(array, degrees);
		float sum = 0;
		for(int i = 0; i < ARRAY_SIZE; i ++){
			sum += array[i];
		}
		average = (sum/ARRAY_SIZE);
		return average;
	}
}

int check_solution(float average, int solution, float degrees){
	sprintf(string1, "solution: %d\r\n", solution);
	HAL_UART_Transmit(&huart1, string1, strlen(string1), HAL_MAX_DELAY);
	if(average > 67.5 && average < 112.5 && solution == 1){
		turnOnLED(2);
		return 1;
	}
	else if (average > 22.5 && average < 67.5 && solution == 2){
		turnOnLED(3);
		return 1;
	}
	else if (((degrees < 360 && degrees > 337.5) || (degrees > 0 && degrees < 22.5)) && solution == 3){ //something weird for 0 - 360
		turnOnLED(4);
		return 1;
	}
	else if (average > 292.5 && average < 337.5 && solution == 4){
		turnOnLED(5);
		return 1;
	}
	else if (average > 247.5 && average < 292.5 && solution == 5){
		turnOnLED(6);
		return 1;
	}
	else if (average > 202.5 && average < 247.5 && solution == 6){
		turnOnLED(7);
		return 1;
	}
	else if (average > 157.5 && average < 202.5 && solution == 7){
		turnOnLED(0);
		return 1;
	}
	else if (average > 112.5 && average < 157.5 && solution == 0){
		turnOnLED(1);
		return 1;
	}
	else{
		//turn on four LED's
		turnOnFour();
		sprintf(string1, "CORRECT SOLUTION NOT FOUND\r\n");
		HAL_UART_Transmit(&huart1, string1, strlen(string1), HAL_MAX_DELAY);
		return 0;
	}

}

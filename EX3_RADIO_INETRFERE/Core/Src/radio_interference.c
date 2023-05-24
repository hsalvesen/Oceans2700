#include "main.h"

void radio_interfere(){
	void (*LDRChannels[8])() = {
		  &ADC_select_CH2,
		  &ADC_select_CH3,
		  &ADC_select_CH4,
		  &ADC_select_CH5,
		  &ADC_select_CH6,
		  &ADC_select_CH7,
		  &ADC_select_CH8,
		  &ADC_select_CH9
	};

	//MAGNETOMETER VARIABLES
	int solution;
	float x_data, y_data, z_data;
	uint8_t test[64];
	HAL_StatusTypeDef returnValue, stat, check, odr;
	float array[ARRAY_SIZE] = {0};

	//AVERAGING VARIABLES
	float degrees, average;
	int count = 0;
	float sum = 0;
	int completed_magnetometer = 0;

	//ADC VARIABLES
	int LDRs[] = {0, 0, 0, 0, 0, 0, 0, 0};
	int ADC_Solutions[8] = {0,0,0,0,0,0,0,0};
	int completed_ADC = 0;

	for(int cycle = 0; cycle < 5; cycle++){
			solution =(SysTick->VAL % 8);
			//MAGNETOMETER MODULE
		mag_config();
	   while (1){

		   x_data = read_x_data();
		   y_data = read_y_data();
		   z_data = read_z_data();

		   degrees = calculate_degrees(x_data, y_data);

		   average = calculate_average(array, degrees, count);
		   count++;

		   completed_magnetometer = check_solution(average, solution, degrees);

		   if (completed_magnetometer == 1){
			   break;
		   }

				HAL_Delay(100);
	   	   }
		   //ADC MODULE
			   HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
			   ADC_Solutions[solution] = 1;

			   while (1){

				   poll_ADC(LDRChannels, LDRs);
				   completed_ADC = check_match(ADC_Solutions, LDRs);
				   char test[64];

				   if(completed_ADC == 1){
					   ADC_Solutions[solution] = 0;
					   break;
				   }
			   }
		  }
}

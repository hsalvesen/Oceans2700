/*
 * calculation_functions.h
 *
 *  Created on: May 24, 2023
 *      Author: Matylda
 */

#ifndef INC_CALCULATION_FUNCTIONS_H_
#define INC_CALCULATION_FUNCTIONS_H_

void shuffle_array(float array[], float degrees);
float calculate_degrees(float x_data, float y_data);
float calculate_average(float array[], float degrees, int count);
bool check_solution(float average, int solution, float degrees);

#endif /* INC_CALCULATION_FUNCTIONS_H_ */

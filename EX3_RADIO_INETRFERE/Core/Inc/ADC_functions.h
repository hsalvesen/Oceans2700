/*
 * ADC_functions.h
 *
 *  Created on: May 24, 2023
 *      Author: Matylda
 */

#ifndef INC_ADC_FUNCTIONS_H_
#define INC_ADC_FUNCTIONS_H_

#include "main.h"

void poll_ADC(void (**array)(), int LDRs[]);
void ADC_select_CH2 (void);
void ADC_select_CH3 (void);
void ADC_select_CH4 (void);
void ADC_select_CH5 (void);
void ADC_select_CH6 (void);
void ADC_select_CH7 (void);
void ADC_select_CH8 (void);
void ADC_select_CH9 (void);
int check_match(int ADC_Solutions[], int LDRs[]);

#endif /* INC_ADC_FUNCTIONS_H_ */

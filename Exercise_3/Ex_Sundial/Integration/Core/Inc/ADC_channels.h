#include "main.h"

int ADC_check(void (*LDRChannels[8])(), int* LDRs, int* ADC_Solutions, ADC_HandleTypeDef *hadc1, ADC_ChannelConfTypeDef *sConfig);

void ADC_select_CH2 (ADC_HandleTypeDef *hadc1, ADC_ChannelConfTypeDef *sConfig);

void ADC_select_CH3 (ADC_HandleTypeDef *hadc1, ADC_ChannelConfTypeDef *sConfig);

void ADC_select_CH4 (ADC_HandleTypeDef *hadc1, ADC_ChannelConfTypeDef *sConfig);

void ADC_select_CH5 (ADC_HandleTypeDef *hadc1, ADC_ChannelConfTypeDef *sConfig);

void ADC_select_CH6 (ADC_HandleTypeDef *hadc1, ADC_ChannelConfTypeDef *sConfig);

void ADC_select_CH7 (ADC_HandleTypeDef *hadc1, ADC_ChannelConfTypeDef *sConfig);

void ADC_select_CH8 (ADC_HandleTypeDef *hadc1, ADC_ChannelConfTypeDef *sConfig);

void ADC_select_CH9 (ADC_HandleTypeDef *hadc1, ADC_ChannelConfTypeDef *sConfig);

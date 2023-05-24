
#ifndef ADC_CHANNEL_SELECT_H
#define ADC_CHANNEL_SELECT_H

#include "main.h"


int ADC_check(void (*LDRChannels[8])(), int* LDRs, int* ADC_Solutions, ADC_HandleTypeDef *hadc1, ADC_ChannelConfTypeDef *sConfig){
	// Poll each LED in sequence
	for (int i = 0; i < 8; i++){
		LDRChannels[i](hadc1, sConfig);
		HAL_ADC_Start(hadc1);
		HAL_ADC_PollForConversion(hadc1, 1000);
		int ADC_val = HAL_ADC_GetValue(hadc1);
		HAL_ADC_Stop(hadc1);

		// read the value from ADC, full range is 12 bits
		uint8_t scale = ADC_val / (0xfff / 8);  // divide the scale into 8 even partitions (for 8 leds)

		// Mark LED to be triggered
		if (scale > 3) {
			LDRs[i] = 1;
		} else {
			LDRs[i] = 0;
		}
	}

	// Check if solution is a match+
	for (int i = 0; i <= 8; i++){
		if (i == 8){
			return 1;
		} else if (LDRs[i] == ADC_Solutions[i]){
			continue;
		} else{
			return 0;
		}
	}
}

void ADC_select_CH2 (ADC_HandleTypeDef *hadc1, ADC_ChannelConfTypeDef *sConfig){
sConfig->Channel = ADC_CHANNEL_2;
sConfig->Rank = ADC_REGULAR_RANK_1;
sConfig->SingleDiff = ADC_SINGLE_ENDED;
sConfig->SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
sConfig->OffsetNumber = ADC_OFFSET_NONE;
sConfig->Offset = 0;
if (HAL_ADC_ConfigChannel(hadc1, sConfig) != HAL_OK)
{
  Error_Handler();
}
}

void ADC_select_CH3 (ADC_HandleTypeDef *hadc1, ADC_ChannelConfTypeDef *sConfig){
sConfig->Channel = ADC_CHANNEL_3;
sConfig->Rank = ADC_REGULAR_RANK_1;
sConfig->SingleDiff = ADC_SINGLE_ENDED;
sConfig->SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
sConfig->OffsetNumber = ADC_OFFSET_NONE;
sConfig->Offset = 0;
if (HAL_ADC_ConfigChannel(hadc1, sConfig) != HAL_OK)
{
  Error_Handler();
}
}

void ADC_select_CH4 (ADC_HandleTypeDef *hadc1, ADC_ChannelConfTypeDef *sConfig){
sConfig->Channel = ADC_CHANNEL_4;
sConfig->Rank = ADC_REGULAR_RANK_1;
sConfig->SingleDiff = ADC_SINGLE_ENDED;
sConfig->SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
sConfig->OffsetNumber = ADC_OFFSET_NONE;
sConfig->Offset = 0;
if (HAL_ADC_ConfigChannel(hadc1, sConfig) != HAL_OK)
{
  Error_Handler();
}
}

void ADC_select_CH5 (ADC_HandleTypeDef *hadc1, ADC_ChannelConfTypeDef *sConfig){
sConfig->Channel = ADC_CHANNEL_5;
sConfig->Rank = ADC_REGULAR_RANK_1;
sConfig->SingleDiff = ADC_SINGLE_ENDED;
sConfig->SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
sConfig->OffsetNumber = ADC_OFFSET_NONE;
sConfig->Offset = 0;
if (HAL_ADC_ConfigChannel(hadc1, sConfig) != HAL_OK)
{
  Error_Handler();
}
}

void ADC_select_CH6 (ADC_HandleTypeDef *hadc1, ADC_ChannelConfTypeDef *sConfig){
sConfig->Channel = ADC_CHANNEL_6;
sConfig->Rank = ADC_REGULAR_RANK_1;
sConfig->SingleDiff = ADC_SINGLE_ENDED;
sConfig->SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
sConfig->OffsetNumber = ADC_OFFSET_NONE;
sConfig->Offset = 0;
if (HAL_ADC_ConfigChannel(hadc1, sConfig) != HAL_OK)
{
  Error_Handler();
}
}

void ADC_select_CH7 (ADC_HandleTypeDef *hadc1, ADC_ChannelConfTypeDef *sConfig){
sConfig->Channel = ADC_CHANNEL_7;
sConfig->Rank = ADC_REGULAR_RANK_1;
sConfig->SingleDiff = ADC_SINGLE_ENDED;
sConfig->SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
sConfig->OffsetNumber = ADC_OFFSET_NONE;
sConfig->Offset = 0;
if (HAL_ADC_ConfigChannel(hadc1, sConfig) != HAL_OK)
{
  Error_Handler();
}
}

void ADC_select_CH8 (ADC_HandleTypeDef *hadc1, ADC_ChannelConfTypeDef *sConfig){
sConfig->Channel = ADC_CHANNEL_8;
sConfig->Rank = ADC_REGULAR_RANK_1;
sConfig->SingleDiff = ADC_SINGLE_ENDED;
sConfig->SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
sConfig->OffsetNumber = ADC_OFFSET_NONE;
sConfig->Offset = 0;
if (HAL_ADC_ConfigChannel(hadc1, sConfig) != HAL_OK)
{
  Error_Handler();
}
}

void ADC_select_CH9 (ADC_HandleTypeDef *hadc1, ADC_ChannelConfTypeDef *sConfig){
sConfig->Channel = ADC_CHANNEL_9;
sConfig->Rank = ADC_REGULAR_RANK_1;
sConfig->SingleDiff = ADC_SINGLE_ENDED;
sConfig->SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
sConfig->OffsetNumber = ADC_OFFSET_NONE;
sConfig->Offset = 0;
if (HAL_ADC_ConfigChannel(hadc1, sConfig) != HAL_OK)
{
  Error_Handler();
}
}

#endif


#ifndef ADC_CHANNEL_SELECT_H
#define ADC_CHANNEL_SELECT_H

#include "main.h"




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

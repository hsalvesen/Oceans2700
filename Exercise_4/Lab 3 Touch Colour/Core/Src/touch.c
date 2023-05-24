#include "touch.h"

#define BLUE 0
#define RED 1
#define ORANGE 2
#define GREEN 3

void readTSC() {
	HAL_TSC_IODischarge(&htsc, ENABLE);
	HAL_Delay(2);

	if (HAL_TSC_Start(&htsc) != HAL_OK) {
		Error_Handler();
	}

	while (HAL_TSC_GetState(&htsc) == HAL_TSC_STATE_BUSY) {}
}

uint32_t get_TSC_colours() {
	uint32_t result = 0;
	result |= ((uint16_t)HAL_TSC_GroupGetValue(&htsc, BLUE_TSC_GROUP) < BLUE_THRESHOLD) << BLUE;
	result |= ((uint16_t)HAL_TSC_GroupGetValue(&htsc, RED_TSC_GROUP) < RED_THRESHOLD) << RED;
	result |= ((uint16_t)HAL_TSC_GroupGetValue(&htsc, ORANGE_TSC_GROUP) < ORANGE_THRESHOLD) << ORANGE;
	result |= ((uint16_t)HAL_TSC_GroupGetValue(&htsc, GREEN_TSC_GROUP) < GREEN_THRESHOLD) << GREEN;
	return result;

}

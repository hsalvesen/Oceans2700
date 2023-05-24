#include "main.h"

int main(void)
{
	init_peripherals();

	radio_interfere();

	HAL_UART_Transmit(&huart1, (uint8_t*) "]", strlen("]"), HAL_MAX_DELAY);

	turnOnAll();

	while (1){}
}



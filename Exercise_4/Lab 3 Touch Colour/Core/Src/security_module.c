#include "security_module.h"

void run_security_module() {
	uint32_t n_done = 0;
	while (n_done < N_LOOPS) {
		uint32_t current_colour = (SysTick->VAL % 16);
		set_leds(current_colour);
		while (1) {
			readTSC();
			if (current_colour == get_TSC_colours()) {
				n_done++;
				break;
			}
		}
	}
	HAL_UART_Transmit(&huart1, (uint8_t*) DONE, strlen(DONE), HAL_MAX_DELAY);
	set_leds(0x0);
}

#include "peripherals.h"

void init_peripherals() {
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();
	/* Configure the system clock */
	SystemClock_Config();
	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_USB_PCD_Init();
	MX_TSC_Init();
	MX_USART1_UART_Init();
}

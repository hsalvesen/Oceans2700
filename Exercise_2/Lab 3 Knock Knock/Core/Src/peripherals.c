#include "peripherals.h"

void init_peripherals() {
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();
	/* Configure the system clock */
	SystemClock_Config();
	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_I2C1_Init();
	MX_USB_PCD_Init();
	MX_USART1_UART_Init();
	MX_TIM2_Init();
	initialise_ptu_i2c(&hi2c1);
	TIM2->CNT = 0xFFFFFFFF;
	TIM2->EGR |= (1 << 0);
	TIM2->CR1 |= (1 << 0);
}

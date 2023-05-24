#include "peripherals.h"

void Init_Peripherals() {
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();
	/* Configure the system clock */
	SystemClock_Config();
	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_I2C1_Init();
	MX_SPI1_Init();
	MX_USB_PCD_Init();
	MX_TIM2_Init();
	MX_TIM1_Init();
	MX_ADC1_Init();
	MX_USART1_UART_Init();
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
	// TIM 2 is setup with a prescaler that makes 1 count = 1 microsecond
	// Even with HAL, you can still set the values yourself
	TIM2->ARR = 20000; // 20000 = 20ms, which is the desired clock period for servos
	TIM2->CR1 |= TIM_CR1_ARPE;
	// note: for PWM if you continually change the clock period
	// you can get unexpected results. To remove this, set ARPE so that the
	// ARR settings are not activated until the next cycle.
	initialise_ptu_i2c(&hi2c1);
}

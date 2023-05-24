#include "peripherals.h"

void init_peripherals(){
	enable_clocks();
	  HAL_Init();
	  SystemClock_Config();
	  MX_GPIO_Init();
	  MX_I2C1_Init();
	  MX_USB_PCD_Init();
	  MX_ADC1_Init();
	  MX_USART1_UART_Init();
}

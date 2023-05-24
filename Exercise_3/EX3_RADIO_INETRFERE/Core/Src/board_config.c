#include "main.h"

#define LED_ALL 0xffff
#define LED_FOUR 0x5555

volatile int LED_POS = 0;
volatile uint8_t* led_output_display = ((uint8_t*)&(GPIOE->ODR)) + 1;
volatile uint32_t systickValue = 0;

void enable_clocks() {

RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIOEEN;
}

void enableLED()
{
	//only take important bits (first 16) of LED output register
	uint16_t* portReg = ((uint16_t*)&(GPIOE->MODER))+1;

	//set LED pins to output
	*portReg = LED_FOUR;
}

void turnOnLED(int pos){
	LED_POS = pos;
	*led_output_display = 1UL << LED_POS;

}

void turnOnAll(){
	*led_output_display = LED_ALL;
}

void turnOnFour(){
	*led_output_display = LED_FOUR;
}

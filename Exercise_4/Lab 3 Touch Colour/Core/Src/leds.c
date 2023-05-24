#include "leds.h"

void turn_on_colour(uint8_t colour) {
	volatile uint8_t* led_output_display = ((uint8_t*)&(GPIOE->ODR)) + 1;
	*led_output_display |= 0x11<<colour;
}

void turn_off_colour(uint8_t colour) {
	volatile uint8_t* led_output_display = ((uint8_t*)&(GPIOE->ODR)) + 1;
	*led_output_display &= ~(0x11<<colour);
}

void set_leds(uint8_t colour) {
	for (int i = 0; i < 4; i++) {
		  if (colour & (1UL << i)) {
			  turn_on_colour(i);
		  } else {
			  turn_off_colour(i);
		  }
	  }
}

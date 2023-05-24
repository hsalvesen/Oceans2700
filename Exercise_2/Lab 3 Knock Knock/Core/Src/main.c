#include "main.h"

int main(void)
{
	init_peripherals();

	uint32_t knock_pattern_ms[] = {DOT, DOT, DOT, DOT, SPACE, DOT, SPACE, DOT, DOT, SPACE, DOT, DOT, DOT, SPACE, DASH};
	uint32_t pattern_len = 15;

	detect_knock_pattern(knock_pattern_ms, pattern_len);
	while (1) {}
}

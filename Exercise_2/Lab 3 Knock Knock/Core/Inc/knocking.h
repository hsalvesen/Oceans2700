#ifndef Knocking
#define Knocking

#include "main.h"

#define DOT_SPACE_THRESHOLD 1000
#define DOT 1
#define SPACE 2
#define DASH 3
#define DONE "]"
#define WRONG "["

uint32_t process_knock(
		uint32_t* knock_times_i,
		uint32_t* previous_time_ms,
		uint32_t* current_time_ms,
		uint32_t* knock_pattern_ms,
		uint32_t pattern_len
		);

void detect_knock_pattern(uint32_t knock_pattern_ms[], uint32_t pattern_len);

#endif

#include "knocking.h"
#include "usart.h"

uint32_t process_knock(
		uint32_t* knock_times_i,
		uint32_t* previous_time_ms,
		uint32_t* current_time_ms,
		uint32_t* knock_pattern_ms,
		uint32_t pattern_len
		) {
	if (*knock_times_i == 0) {
		*previous_time_ms = *current_time_ms;
		(*knock_times_i)++;
		HAL_UART_Transmit(&huart1, (uint8_t* ) ".", strlen("."), HAL_MAX_DELAY);
	} else {
		if (*current_time_ms - *previous_time_ms > DOT_SPACE_THRESHOLD) {
			if (knock_pattern_ms[*knock_times_i] == SPACE && knock_pattern_ms[*knock_times_i+1] == DOT) {
				*knock_times_i += 2;
				*previous_time_ms = *current_time_ms;
				HAL_UART_Transmit(&huart1, (uint8_t* ) " .", strlen(" ."), HAL_MAX_DELAY);
			} else if (knock_pattern_ms[*knock_times_i] == SPACE && knock_pattern_ms[*knock_times_i+1] == DASH) {
				*knock_times_i += 2;
				*previous_time_ms = *current_time_ms;
				HAL_UART_Transmit(&huart1, (uint8_t* ) " -", strlen(" -"), HAL_MAX_DELAY);
			} else {
				*knock_times_i = 0;
				*previous_time_ms = *current_time_ms;
				HAL_UART_Transmit(&huart1, (uint8_t* ) WRONG, strlen(WRONG), HAL_MAX_DELAY);
			}
		} else {
			if (knock_pattern_ms[*knock_times_i] == DOT) {
				*knock_times_i += 1;
				*previous_time_ms = *current_time_ms;
				HAL_UART_Transmit(&huart1, (uint8_t* ) ".", strlen("."), HAL_MAX_DELAY);
			} else if (knock_pattern_ms[*knock_times_i] == DASH) {
				*knock_times_i += 1;
				*previous_time_ms = *current_time_ms;
				HAL_UART_Transmit(&huart1, (uint8_t* ) "-", strlen("-"), HAL_MAX_DELAY);
			} else {
				*knock_times_i = 0;
				*previous_time_ms = *current_time_ms;
				HAL_UART_Transmit(&huart1, (uint8_t* ) WRONG, strlen(WRONG), HAL_MAX_DELAY);
			}
		}
	}
	if (*knock_times_i == pattern_len) {
		return 1;
	}
	return 0;
}

void detect_knock_pattern(uint32_t knock_pattern_ms[], uint32_t pattern_len) {
	uint32_t current_time_ms = 0;
	uint32_t previous_time_ms = 0;
	uint32_t knock_times_i = 0;
	while (1) {
		current_time_ms = TIM2->CNT;
		if (current_time_ms - previous_time_ms > KNOCK_DEBOUNCE_MS) {
			int16_t yaw_rate = read_gyro(YAW);
			if (abs(yaw_rate) > GYRO_THRESHOLD) {
				if (process_knock(&knock_times_i, &previous_time_ms,
						&current_time_ms, knock_pattern_ms, pattern_len)) {
					HAL_UART_Transmit(&huart1, (uint8_t*) DONE, strlen(DONE),
							HAL_MAX_DELAY);
					break;
				}
			}
		}
	}
}

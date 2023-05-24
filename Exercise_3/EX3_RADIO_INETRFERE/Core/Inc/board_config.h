/*
 * board_config.h
 *
 *  Created on: May 24, 2023
 *      Author: Matylda
 */

#ifndef INC_BOARD_CONFIG_H_
#define INC_BOARD_CONFIG_H_

#include "main.h"

void enable_clocks();
void enableLED();
void turnOnLED(int pos);
void turnOnAll();
void turnOnFour();

#endif /* INC_BOARD_CONFIG_H_ */

#ifndef Touch
#define Touch

#include "main.h"
#include "tsc.h"

#define BLUE_THRESHOLD 4500
#define BLUE_TSC_GROUP TSC_GROUP1_IDX

#define RED_THRESHOLD 4500
#define RED_TSC_GROUP TSC_GROUP3_IDX

#define ORANGE_THRESHOLD 4500
#define ORANGE_TSC_GROUP TSC_GROUP6_IDX

#define GREEN_THRESHOLD 4500
#define GREEN_TSC_GROUP TSC_GROUP8_IDX

#define TOUCH_HOLD_MS 200

void readTSC();

uint32_t get_TSC_colours();

#endif

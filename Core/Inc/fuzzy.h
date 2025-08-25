#ifndef FUZZY_H
#define FUZZY_H

#include "stm32f1xx_hal.h"
#include <math.h>


void find_temp(float temp);
void find_hum(float hum);
void motion_detection(int presence);
void rule_evaluation(void);
void maximum(void);
void centre(void);
int crisp_output(void);
int fuzzy_init(float temp_rcv, float hum_rcv, int presence_rcv);

#endif /* FUZZY_H */

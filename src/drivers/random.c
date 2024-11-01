/*
 * @file random.c
 * @brief Implements random number generation functions
 * 
 * @author Ameed Othman
 * @date 2024-11-01
 */

#include "random.h"
#include "adc.h"
#include <stdlib.h>

void Random_Init(void) {
    ADC_Init();
    int seed = ADC_Read(0);
    srand(seed);
}

int Random_GetNumber(int min, int max) {
    return min + (rand() % (max - min + 1));
}

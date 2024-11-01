/*
 * @file shift_register.c
 * @rief Implements shift register control functions
 * 
 * @author Ameed Othman
 * @date 2024-10-31
 */

#include "shift_register.h"
#include "gpio.h"

#define LATCH_PIN 8
#define CLOCK_PIN 12
#define DATA_PIN 11

void ShiftRegister_Init(void) {
    GPIO_SetPinDirection(LATCH_PIN, GPIO_OUTPUT);
    GPIO_SetPinDirection(CLOCK_PIN, GPIO_OUTPUT);
    GPIO_SetPinDirection(DATA_PIN, GPIO_OUTPUT);
}

void ShiftRegister_ShiftOut(unsigned char data) {
    GPIO_WritePin(LATCH_PIN, GPIO_LOW);

    for (int i = 0; i < 8; i++) {
        unsigned char bit = (data & (1 << (7 - i))) ? GPIO_HIGH : GPIO_LOW;
        GPIO_WritePin(DATA_PIN, bit);
        GPIO_WritePin(CLOCK_PIN, GPIO_HIGH);
        GPIO_WritePin(CLOCK_PIN, GPIO_LOW);
    }

    GPIO_WritePin(LATCH_PIN, GPIO_HIGH);
}


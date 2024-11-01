/*
 * @file button.c
 * @brief Implements button input functions
 * 
 * @author Ameed Othman
 * @date 2024-10-31
 */

#include "button.h"
#include "gpio.h"

#define BUTTON_PIN 2

void Button_Init(void) {
    GPIO_SetPinDirection(BUTTON_PIN, GPIO_INPUT);
}

int Button_IsPressed(void) {
    return GPIO_ReadPin(BUTTON_PIN) == GPIO_LOW;
}

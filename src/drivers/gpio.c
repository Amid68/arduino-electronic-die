/*
 * @file gpio.c
 * @brief Implements GPIO control functions
 * 
 * @author Ameed Othman
 * @date 2024-11-01
 */

#include "gpio.h"
#include <avr/io.h> 

/**
 * @brief Sets the direction of a specified GPIO pin.
 * 
 * @param pin The pin number to configure.
 * @param direction The direction to set (GPIO_INPUT or GPIO_OUTPUT).
 */
void GPIO_SetPinDirection(int pin, int direction) {
    if (direction == GPIO_OUTPUT) {
        DDRB |= (1 << pin);
    } else {
        DDRB &= ~(1 << pin);
    }
}

/**
 * @brief Writes a value to a specified GPIO pin.
 * 
 * @param pin The pin number to write to.
 * @param value The value to write (GPIO_HIGH or GPIO_LOW).
 */
void GPIO_WritePin(int pin, int value) {
    if (value == GPIO_HIGH) {
        PORTB |= (1 << pin);
    } else {
        PORTB &= ~(1 << pin);
    }
}

/**
 * @brief Reads the current value of a specified GPIO pin.
 * 
 * @param pin The pin number to read from.
 * @return int The current value read from the pin (GPIO_HIGH or GPIO_LOW).
 */
int GPIO_ReadPin(int pin) {
    return (PINB & (1 << pin)) ? GPIO_HIGH : GPIO_LOW;
}

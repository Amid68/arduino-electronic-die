/*
 * @file gpio.c
 * @brief Implements GPIO control functions for multiple ports
 * 
 * @author Ameed Othman
 * @date 2024-11-01
 */

#include "gpio.h"
#include <avr/io.h>

#define NUM_PINS 20

typedef struct {
    volatile uint8_t *ddr;
    volatile uint8_t *port;
    volatile uint8_t *pin;
    uint8_t bit;
} PinMap;

static const PinMap pin_map[NUM_PINS] = {
    // D0 - D7 (PORTD)
    {&DDRD, &PORTD, &PIND, PD0},  // D0
    {&DDRD, &PORTD, &PIND, PD1},  // D1
    {&DDRD, &PORTD, &PIND, PD2},  // D2 (Button Pin)
    {&DDRD, &PORTD, &PIND, PD3},  // D3
    {&DDRD, &PORTD, &PIND, PD4},  // D4
    {&DDRD, &PORTD, &PIND, PD5},  // D5
    {&DDRD, &PORTD, &PIND, PD6},  // D6
    {&DDRD, &PORTD, &PIND, PD7},  // D7
    // D8 - D13 (PORTB)
    {&DDRB, &PORTB, &PINB, PB0},  // D8 (LATCH_PIN)
    {&DDRB, &PORTB, &PINB, PB1},  // D9
    {&DDRB, &PORTB, &PINB, PB2},  // D10
    {&DDRB, &PORTB, &PINB, PB3},  // D11 (DATA_PIN)
    {&DDRB, &PORTB, &PINB, PB4},  // D12 (CLOCK_PIN)
    {&DDRB, &PORTB, &PINB, PB5},  // D13
    // A0 - A5 (PORTC)
    {&DDRC, &PORTC, &PINC, PC0},  // A0
    {&DDRC, &PORTC, &PINC, PC1},  // A1
    {&DDRC, &PORTC, &PINC, PC2},  // A2
    {&DDRC, &PORTC, &PINC, PC3},  // A3
    {&DDRC, &PORTC, &PINC, PC4},  // A4
    {&DDRC, &PORTC, &PINC, PC5},  // A5
};

void GPIO_SetPinDirection(int pin, int direction) {
    if (pin < 0 || pin >= NUM_PINS)
        return;
    if (direction == GPIO_OUTPUT) {
        *(pin_map[pin].ddr) |= (1 << pin_map[pin].bit);
    } else {
        *(pin_map[pin].ddr) &= ~(1 << pin_map[pin].bit);
    }
}

void GPIO_WritePin(int pin, int value) {
    if (pin < 0 || pin >= NUM_PINS)
        return;
    if (value == GPIO_HIGH) {
        *(pin_map[pin].port) |= (1 << pin_map[pin].bit);
    } else {
        *(pin_map[pin].port) &= ~(1 << pin_map[pin].bit);
    }
}

int GPIO_ReadPin(int pin) {
    if (pin < 0 || pin >= NUM_PINS)
        return GPIO_LOW;
    return (*(pin_map[pin].pin) & (1 << pin_map[pin].bit)) ? GPIO_HIGH : GPIO_LOW;
}

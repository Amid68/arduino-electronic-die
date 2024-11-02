/*
 * @file delay.c
 * @brief Implements delay functions using AVR timers
 * 
 * @author Ameed Othman
 * @date 2024-11-02
 */

#include "delay.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned long timer_millis = 0;

void Delay_Init(void) {
    // Configure Timer0 for 1ms overflow interrupts
    TCCR0A = (1 << WGM01);               // Set CTC mode
    TCCR0B = (1 << CS01) | (1 << CS00);  // Prescaler 64
    OCR0A = 249;                         // Compare match value for 1ms at 16MHz
    TIMSK0 = (1 << OCIE0A);              // Enable Timer0 compare interrupt
    sei();                               // Enable global interrupts
}

ISR(TIMER0_COMPA_vect) {
    timer_millis++;
}

void Delay_ms(int milliseconds) {
    unsigned long start_time = timer_millis;
    while ((timer_millis - start_time) < milliseconds);
}

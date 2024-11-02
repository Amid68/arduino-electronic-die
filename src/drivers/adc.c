/*
 * @file adc.c
 * @brief Implements ADC reading functions for AVR microcontrollers
 * 
 * @author Ameed Othman
 * @date 2024-11-02
 */

#include "adc.h"
#include <avr/io.h>

void ADC_Init(void) {
    // Set the ADC reference to AVcc (5V)
    ADMUX = (1 << REFS0);

    // Set the ADC prescaler to 128 (16MHz / 128 = 125kHz)
    ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    // Enable the ADC
    ADCSRA |= (1 << ADEN);
}

int ADC_Read(int channel) {
    // Select the ADC channel (0-7)
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

    // Start the ADC conversion
    ADCSRA |= (1 << ADSC);

    // Wait for the conversion to complete
    while (ADCSRA & (1 << ADSC));

    return ADCW;
}

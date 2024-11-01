/*
 * @file gpio.h
 * @brief Header file for GPIO functions
 * 
 * @author Ameed Othman
 * @date 2024-11-01
 */

#ifndef __GPIO_H__
#define __GPIO_H__

#define GPIO_INPUT  0
#define GPIO_OUTPUT 1

#define GPIO_LOW  0
#define GPIO_HIGH 1

void GPIO_SetPinDirection(int pin, int direction);
void GPIO_WritePin(int pin, int value);
int GPIO_ReadPin(int pin);

#endif

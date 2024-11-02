/*
 * @file display.h
 * @brief Header file for display functions
 * 
 * @author Ameed Othman
 * @date 2024-10-31
 */

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

void Display_Init(void);
void Display_ShowDecimalPoint(void);
void Display_ShowNumber(unsigned char num);
void Display_AnimateShake(int frame);
void Display_AnimateRoll(int frame);

#endif

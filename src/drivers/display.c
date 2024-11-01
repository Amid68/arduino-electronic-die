/*
 * @file display.c
 * @brief Implements display functions for the 7-segment display
 * 
 * @author Ameed Othman
 * @date 2024-10-31
 */

#include "display.h"
#include "shift_register.h"

static const unsigned char lookup_7seg[] = {0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x80};
static const unsigned char shake_dice[] = {0x63, 0x5C};
static const unsigned char roll_dice[] = {0x1C, 0x58, 0x54, 0x4C};

void Display_Init(void) {
    ShiftRegister_Init();
}

void Display_ShowDecimalPoint(void) {
    ShiftRegister_ShiftOut(lookup_7seg[6]);
}

void Display_ShowNumber(unsigned char num) {
    if (num < 6) {
        ShiftRegister_ShiftOut(lookup_7seg[num]);
    }
}

void Display_AnimateShake(int frame) {
    if (frame == 0 || frame == 1) {
        ShiftRegister_ShiftOut(shake_dice[frame]);
    }
}

void Display_AnimateRoll(int frame) {
    if (frame >= 0 && frame < 4) {
        ShiftRegister_ShiftOut(roll_dice[frame]);
    }
}


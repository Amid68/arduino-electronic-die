/**
 * @file main.c
 * @brief Main program for the electronic die application
 *
 * @author Ameed Othman
 * @date 2024-10-31
 */

#include "dice.h"
#include "display.h"
#include "button.h"

int main(void) {
    Dice_Init();
    Display_Init();
    Button_Init();

    Display_ShowDecimalPoint();

    while (1) {
        Dice_Run();
    }

    return 0;
}


/**
 * @file dice.c
 * @brief Implements the dice rolling logic
 *
 * @author Ameed Othman
 * @date 2024-10-31
 */

#include "dice.h"
#include "display.h"
#include "button.h"
#include "delay.h"
#include "random.h"

static int rand_seed = 0;
static unsigned char shake_toggle = 0;
static int roll_index = 0;
static int shake_speed = 0;

void Dice_Init(void) {
    Random_Init();
}

void Dice_Run(void) {
    if (Button_IsPressed()) {
        shake_speed = 150;
        Delay_ms(30);

        rand_seed = 0;
        roll_index = 0;
        shake_toggle = 0;

        while (Button_IsPressed()) {
            rand_seed++;

            if (shake_toggle) {
                Display_AnimateShake(0);
                shake_toggle = 0;
            } else {
                Display_AnimateShake(1);
                shake_toggle = 1;
            }

            Delay_ms(80 + shake_speed);

            if (shake_speed > 0) {
                shake_speed -= 10;
            }
        }

        int rolls = rand_seed % 10 + 14;
        for (int i = 0; i < rolls; i++) {
            Display_AnimateRoll(roll_index);
            Delay_ms((1+i) * 20);
            roll_index = (roll_index + 1) % 4;
        }

        int rand_num = Random_GetNumber(0, 5);
        Display_ShowNumber(rand_num);
    }
}



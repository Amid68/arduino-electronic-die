/**
 * @file DiceRoller.ino
 * @brief A program to simulate a dice roll using a 7-segment display, driven by a shift register and controlled via a button press.
 * 
 * The program features an animated dice-shaking effect, followed by a rolling animation and displays the final result on a 7-segment display.
 * The animation and display logic are driven by a shift register, interfacing with a 7-segment display.
 * 
 * @author Ameed Othman
 * @date 2024-10-31
 */

const int latchPin = 8;  
const int clockPin = 12; 
const int dataPin = 11;  
const int buttonPin = 2; 

unsigned char lookup_7seg[] = {0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x80};

unsigned char shake_dice[] = {0x63, 0x5C};
unsigned char roll_dice[] = {0x1C, 0x58, 0x54, 0x4C};

int rand_seed;
int rand_num = 0;
unsigned char shake_toggle = 0;
int index = 0;
int shake_speed;

/**
 * @brief Initializes the input and output pins, sets up the 7-segment display, and seeds the random generator.
 */
void setup() {
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);

    // Initial display state showing DP on the 7-segment display
    shiftOut(dataPin, clockPin, MSBFIRST, lookup_7seg[6]);
    digitalWrite(latchPin, HIGH);

    // Seed the random generator using an analog pin
    randomSeed(analogRead(0));
}

/**
 * @brief Main loop to handle dice rolling logic and animations upon button press.
 */
void loop() {
    if (digitalRead(buttonPin) == LOW) {
        shake_speed = 150; 
        delay(30);

        rand_seed = 0;
        index = 0;
        shake_toggle = 0;

        // Shaking animation loop while the button is pressed
        while (digitalRead(buttonPin) == LOW) {
            rand_seed++;

            AnimateDice(shake_toggle ? 0 : 1, shake_dice);
            shake_toggle = !shake_toggle;

            delay(80 + shake_speed);
            if (shake_speed > 0) {
                shake_speed -= 10;
            }
        }

        // Rolling animation sequence
        for (int rolls = 0; rolls < (rand_seed % 10 + 14); rolls++) {
            AnimateDice(index, roll_dice);
            delay((1 + rolls) * 20);
            index = (index + 1) % 4;
        }

        // Display the final dice number
        rand_num = random(0, 6);
        DiceNumber(rand_num);
    }
}

/**
 * @brief Displays a number on the 7-segment display.
 * 
 * @param num The number to display (0-5 for representing numbers 1-6).
 */
void DiceNumber(unsigned char num) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, lookup_7seg[num]);
    digitalWrite(latchPin, HIGH);
}

/**
 * @brief Displays a frame of animation for shaking or rolling the dice.
 * 
 * @param seg The index of the frame to display.
 * @param table The array containing the animation frames.
 */
void AnimateDice(int seg, unsigned char *table) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, table[seg]);
    digitalWrite(latchPin, HIGH);
}
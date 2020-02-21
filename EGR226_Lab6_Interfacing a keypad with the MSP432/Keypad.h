#ifndef __KEYPAD_H__    // ifndef stands for if not defined
#define __KEYPAD_H__

#include <stdint.h>

/*
 * If we want to implement our keypad in a different project
 * and can't use the same pins, we only need to change these define
 * statements rather than going through the entire code
 */

// Pin 2 on the keypad
    #define ROW0_PORT P5
    #define ROW0_PIN BIT5//BIT4

// Pin 7 on the keypad
    #define ROW1_PORT P5//P4
    #define ROW1_PIN BIT4//BIT0

// Pin 6 on the keypad
    #define ROW2_PORT P4
    #define ROW2_PIN BIT7//BIT2

// Pin 4 on the keypad
    #define ROW3_PORT P4
    #define ROW3_PIN BIT5

// Pin 3 on the keypad
    #define COLUMN0_PORT P4
    #define COLUMN0_PIN BIT0//BIT7

// Pin 1 on the keypad
    #define COLUMN1_PORT P4//P5
    #define COLUMN1_PIN BIT2//BIT5

// Pin 5 on the keypad
    #define COLUMN2_PORT P4
    #define COLUMN2_PIN BIT4//BIT4

/*
 * We are setting the columns high when cycling
 * through and checking for buttons pressed. Here we are defining
 * so in the main.c file, it is readable
 */

// Column 0 is set HIGH
    #define  C0_ON COLUMN0_PORT->DIR |= COLUMN0_PIN; COLUMN0_PORT->OUT |= COLUMN0_PIN
// Column 0 is set LOW
    #define  C0_OFF COLUMN0_PORT->DIR &= ~COLUMN0_PIN; COLUMN0_PORT->OUT &= ~COLUMN0_PIN
//----------------------
// Column 1 is set HIGH
    #define  C1_ON COLUMN1_PORT->DIR |= COLUMN1_PIN; COLUMN0_PORT->OUT |= COLUMN0_PIN
// Column 1 is set LOW
    #define  C1_OFF COLUMN1_PORT->DIR &= ~COLUMN1_PIN; COLUMN0_PORT->OUT &= ~COLUMN0_PIN
//----------------------
// Column 2 is set HIGH
    #define  C2_ON COLUMN2_PORT->DIR |= COLUMN2_PIN; COLUMN2_PORT->OUT |= COLUMN2_PIN
// Column 2 is set LOW
    #define  C2_OFF COLUMN2_PORT->DIR &= ~COLUMN2_PIN; COLUMN2_PORT->OUT &= ~COLUMN2_PIN


/*
 * Function Prototypes
 */

void Init_Keypad();             // Initializes the ports and pins associated to the keypad
uint8_t Pressed_Row ();         // The Pressed_Row function identifies which row was pressed
uint16_t Button_Pressed ();     // The Button_Pressed function identifies which button was pressed
void Systick_Delay(uint16_t time);           // The function sets up the SysTick Timer and creates a specified delay
                                // depending on the argument entered in milliseconds
#endif

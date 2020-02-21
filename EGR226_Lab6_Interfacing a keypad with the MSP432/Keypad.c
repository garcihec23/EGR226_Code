#include "msp.h"
#include "keypad.h"
#include <stdint.h>
#include <stdio.h>

/*
 * The Init_Keypad function initializes the pins that the
 * keypad is connected to as inputs
 */

void Init_Keypad() {
    /*
     * See Keypad.h to see which port this applies to
     * as this is built to be able to use any port not
     * just specific ones
     */

    ROW0_PORT->DIR &= ~ROW0_PIN;       // Sets the pin to be an input
    ROW0_PORT->REN |= ROW0_PIN;        // Enables the internal resistor
    ROW0_PORT->OUT &= ~ROW0_PIN;       // Sets the internal resistance to be a pull-down resistor

    ROW1_PORT->DIR &= ~ROW1_PIN;       // Sets the pin to be an input
    ROW1_PORT->REN |= ROW1_PIN;        // Enables the internal resistor
    ROW1_PORT->OUT &= ~ROW1_PIN;       // Sets the internal resistance to be a pull-down resistor

    ROW2_PORT->DIR &= ~ROW2_PIN;       // Sets the pin to be an input
    ROW2_PORT->REN |= ROW2_PIN;        // Enables the internal resistor
    ROW2_PORT->OUT &= ~ROW2_PIN;       // Sets the internal resistance to be a pull-down resistor

    ROW3_PORT->DIR &= ~ROW3_PIN;       // Sets the pin to be an input
    ROW3_PORT->REN |= ROW3_PIN;        // Enables the internal resistor
    ROW3_PORT->OUT &= ~ROW3_PIN;       // Sets the internal resistance to be a pull-down resistor

    COLUMN0_PORT->DIR &= ~COLUMN0_PIN;       // Sets the pin to be an input
    COLUMN0_PORT->REN |= COLUMN0_PIN;        // Enables the internal resistor
    COLUMN0_PORT->OUT &= ~COLUMN0_PIN;       // Sets the internal resistance to be a pull-down resistor

    COLUMN1_PORT->DIR &= ~COLUMN1_PIN;       // Sets the pin to be an input
    COLUMN1_PORT->REN |= COLUMN1_PIN;        // Enables the internal resistor
    COLUMN1_PORT->OUT &= ~COLUMN1_PIN;       // Sets the internal resistance to be a pull-down resistor

    COLUMN2_PORT->DIR &= ~COLUMN2_PIN;       // Sets the pin to be an input
    COLUMN2_PORT->REN |= COLUMN2_PIN;        // Enables the internal resistor
    COLUMN2_PORT->OUT &= ~COLUMN2_PIN;       // Sets the internal resistance to be a pull-down resistor
}

/*
 * The Pressed_Row function identifies which row was pressed
 * then passes the unsigned 8-bit number to the next function
 */
uint8_t Pressed_Row () {

    /*
     * Local variable that is assigned the 8-bit number that represents the row pressed.
     * We only care about the 4 least significant bits as there are only 4 rows
     */
    uint8_t row = 0x00;         // initialized to 0's
    Systick_Delay(10);          // Generates a 10ms delay

    row |= (ROW0_PORT->IN & ROW0_PIN) ? 1 << 0 : 0;       // This ternary condition assigns a 1 to the least significant bit if Row 0 is pressed else it assigns it a 0 (0000 000X)
    Systick_Delay(10);          // Generates a 10ms delay
    row |= (ROW1_PORT->IN & ROW1_PIN) ? 1 << 1 : 0;       // This ternary condition assigns a 1 to the first bit if Row 1 is pressed else it assigns it a 0 (0000 00X0)
    Systick_Delay(10);          // Generates a 10ms delay
    row |= (ROW2_PORT->IN & ROW2_PIN) ? 1 << 2 : 0;       // This ternary condition assigns a 1 to the second bit if Row 2 is pressed else it assigns it a 0 (0000 0X00)
    Systick_Delay(10);          // Generates a 10ms delay
    row |= (ROW3_PORT->IN & ROW3_PIN) ? 1 << 3 : 0;       // This ternary condition assigns a 1 to the third bit if Row 3 is pressed else it assigns it a 0 (0000 X000)

    return row;
}

/*
 * The Pressed_Column function identifies which button was pressed
 * then passes the unsigned 16-bit number to the next function
 */

uint16_t Button_Pressed () {
/*
 * Local variable that is assigned the 16-bit number that represents the the button that was pressed.
 */
    uint16_t button = 0x0000;        // Initialized to 0's


    C0_ON;      // Sets Column 3 HIGH
    button |= (Pressed_Row() & 0x000F) << 0;        // Pressed_Row () Function returns an 8-bits, and we only care
                                                    // about the 4 least significant bits, we mask it with 0x000F.
                                                    // Since this is the first column, we will not shift it to the left
                                                    // Ends up being the MSBs of the variable 'button'
    Systick_Delay(10);          // Generates a 10ms delay
    C0_OFF;     // Sets Column 3 LOW

    C1_ON;      // Sets Column 1 HIGH
    button |= (Pressed_Row() & 0x000F) << 4;        // Pressed_Row () Function returns an 8-bits, and we only care
                                                    // about the 4 least significant bits, we mask it with 0x000F.
                                                    // Since this is the second column, we will shift it to the left by 4-bits
    Systick_Delay(10);          // Generates a 10ms delay
    C1_OFF;     // Sets Column 1 LOW


    C2_ON;      // Sets Column 0 HIGH
    button |= (Pressed_Row() & 0x000F) << 8;        // Pressed_Row () Function returns an 8-bits, and we only care
                                                    // about the 4 least significant bits, we mask it with 0x000F.
                                                    // Since this is the second column, we will shift it to the left by 8-bits
                                                    // Ends up being the LSBs of the variable 'button'
    Systick_Delay(10);          // Generates a 10ms delay
    C2_OFF;     // Sets Column 0 LOW



    return button;      // returns a 16-bit number that can be translated to the correct "button" pressed
}

/*
 * This function initializes the SysTick Timer
 * and creates a delay depending on the argument in ms
 */
void Systick_Delay(uint16_t time) {
    SysTick -> LOAD = (3000 * time) - 1;        //  Delay is (3000 * specified time in milliseconds) / (1 / 3MHz))
    SysTick -> VAL = 0;                         // Clear Current Value Register
    SysTick -> CTRL = 5;                        // Enable the SysTick Timer

    while ((SysTick -> CTRL & BIT(16)) == 0) {
        /*
         * Wait until the COUNTFLAG is set
         */
    }

    SysTick -> CTRL = 0;        // Stop the Timer (Enable = 0)

}

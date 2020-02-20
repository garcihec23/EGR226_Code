#include "Keypad.h"

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

    R0_PORT -> DIR &= ~R0_PIN;       // Sets the pin to be an input
    R0_PORT -> REN |= R0_PIN;        // Enables the internal resistor
    R0_PORT -> OUT &= ~R0_PIN;       // Sets the internal resistance to be a pull-down resistor

    R1_PORT -> DIR &= ~R1_PIN;       // Sets the pin to be an input
    R1_PORT -> REN |= R1_PIN;        // Enables the internal resistor
    R1_PORT -> OUT &= ~R1_PIN;       // Sets the internal resistance to be a pull-down resistor

    R2_PORT -> DIR &= ~R2_PIN;       // Sets the pin to be an input
    R2_PORT -> REN |= R2_PIN;        // Enables the internal resistor
    R2_PORT -> OUT &= ~R2_PIN;       // Sets the internal resistance to be a pull-down resistor

    R3_PORT -> DIR &= ~R3_PIN;       // Sets the pin to be an input
    R3_PORT -> REN |= R3_PIN;        // Enables the internal resistor
    R3_PORT -> OUT &= ~R3_PIN;       // Sets the internal resistance to be a pull-down resistor

    C0_PORT -> DIR &= ~C0_PIN;       // Sets the pin to be an input
    C0_PORT -> REN |= C0_PIN;        // Enables the internal resistor
    C0_PORT -> OUT &= ~C0_PIN;       // Sets the internal resistance to be a pull-down resistor

    C1_PORT -> DIR &= ~C1_PIN;       // Sets the pin to be an input
    C1_PORT -> REN |= C1_PIN;        // Enables the internal resistor
    C1_PORT -> OUT &= ~C1_PIN;       // Sets the internal resistance to be a pull-down resistor

    C2_PORT -> DIR &= ~C2_PIN;       // Sets the pin to be an input
    C2_PORT -> REN |= C2_PIN;        // Enables the internal resistor
    C2_PORT -> OUT &= ~C2_PIN;       // Sets the internal resistance to be a pull-down resistor
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

    row |= (R0_PORT -> IN & R0_PIN) ? 1 << 0 : 0;       // This ternary condition assigns a 1 to the least significant bit if Row 0 is pressed else it assigns it a 0 (0000 000X)
    row |= (R1_PORT -> IN & R1_PIN) ? 1 << 1 : 0;       // This ternary condition assigns a 1 to the first bit if Row 1 is pressed else it assigns it a 0 (0000 00X0)
    row |= (R2_PORT -> IN & R2_PIN) ? 1 << 2 : 0;       // This ternary condition assigns a 1 to the second bit if Row is pressed else it assigns it a 0 (0000 0X00)
    row |= (R3_PORT -> IN & R3_PIN) ? 1 << 3 : 0;       // This ternary condition assigns a 1 to the third bit if Row 0 Pin 0 is pressed else it assigns it a 0 (0000 X000)

    return row;
}

/*
 * The Pressed_Column function identifies which button was pressed
 * then passes the unsigned 16-bit number to the next function
 */

uint16_t Pressed_Column () {
    /*
     * Local variable that is assigned the 16-bit number that represents the the button that was pressed.
     */
    uint16_t button =0x0000;        // Initialized to 0's

    button = ()


}



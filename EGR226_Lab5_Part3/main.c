#include "msp.h"

/*
 * Author: Hector Garcia
 * Course: EGR 226
 * Section: 905
 * Professor Ekin
 * Date: February 14, 2020
 *
 * Description: This program (Part 3) will initialize with the RGB LED off
 * and will cycle through Red -> Green -> Blue -> Red, etc. as the
 * external button 1 is held pressed. However, when button 2 is pressed,
 * the order of the LED cycle is reversed.
 */

// Function Prototypes
    int SwitchBounce();     // Switch Bounce Function
    void init_ports();      // Port Initialization Function
    void state_machine();   // State Machine Function
    void delay1s();         // Delay of 1 second Function

// Global Variables
    int but_flag = 0;       // Directional Flag (Tells us which button was pressed)

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watch dog timer

    init_ports();               // Calls the Port Initialization Function

    while(1) {
        state_machine();        // Calls the State Machine Function
        }
    }

/*
 * This function avoids reading the pushbutton switch during a switch bounce
 * interval
 */
int SwitchBounce() {

    uint8_t flag = 0;   // Variable is changed when switch button is pressed

    // These nested if statements check to see if the button is pressed
    // button pressed is active low, so we are checking for 0's twice.
    // we are delaying one second to verify the button was actually pressed
    // if it is pressed, the flag is set HIGH (1), incorporates a second button,
    // which reverses the order of the LED sequence

    while (1) {
        if (((P2->IN & BIT4) == 0) || ((P2 -> IN & BIT6) == 0)) {
            delay1s();      // When cycles equals 3,000,000,the delay will be 1 second

            if ((P2->IN & BIT4) == 0) {
                flag = 1;       // flag is set to 1 meaning button 1 is pressed
                but_flag = 0;   // directional flag remains at 0
                }
            if ((P2->IN & BIT6) == 0) {
                flag = 1;       // flag is set to 1 meaning button 2 is pressed
                but_flag = 1;   // directional flag is set to 1
                }
            }

        return flag;
    }
}

/*
 * This function will initialize port 2 pin 4 and pin 6 into an input
 * and port 2 pins 0, 1, and 2 as outputs. Further, it sets
 * the proper directions for the port pins, enables port 2
 * pin 4 and 6's internal resistor and sets it as a pull-up resistor,
 * and initializes the LED to be off
 */
void init_ports() {

    // Forward Button
    P2->SEL0 &= ~BIT4;        // Setting SEL0 and SEL1 in Port 2 to be Simple I/O
    P2->SEL1 &= ~BIT4;

    P2->DIR &= ~BIT4;         // Setting the direction of Port 2 Pin 4 to be an input
    P2->REN |= BIT4;          // Internal Resistor is enabled
    P2->OUT |= BIT4;          // Resistor is configured as a Pull-Up Resistor
                              // We want a pull-up resistor because we are reading for
                              // 0's to verify the button was pressed
    // Reverse Button
    P2->SEL0 &= ~BIT6;        // Setting SEL0 and SEL1 in Port 2 to be Simple I/O
    P2->SEL1 &= ~BIT6;

    P2->DIR &= ~BIT6;         // Setting the direction of Port 2 Pin 6 to be an input
    P2->REN |= BIT6;          // Internal Resistor is enabled
    P2->OUT |= BIT6;          // Resistor is configured as a Pull-Up Resistor
                              // We want a pull-up resistor because we are reading for
                              // 0's to verify the button was pressed

    P2->SEL0 &= ~0x07;        // Setting SEL0 and SEL1 in Port 2 to be Simple I/O
    P2->SEL1 &= ~0x07;

    P2->DIR |= 0x07;          // Sets pins 0, 1, 2, 3 in Port 2 as outputs (RGB LED)
    P2OUT &= ~7;              // Initialized with the LED off
}

/*
 * This function creates a Finite State Machine and cycles through
 * the states if the switch button has been pressed. I used the enum
 * data type to create the states.
 */
void state_machine() {

    /*
     * The enum names are identifiers that behave as constants in the language.
     * OFF = 0, RED = 1, GREEN = 2, BLUE = 3.
     */
    enum states {
        OFF, RED, GREEN, BLUE,
    } state;


    while (1) {
        switch (state) {

        case OFF:
            P2->OUT &= ~7;          // Initialized with the LED off
            if (SwitchBounce()) {
                if(!but_flag)
                {
                    state = RED;    // if the button 1 IS pressed, move to the RED state

                }
                if(but_flag)
                {
                    state = BLUE;   // if the button 2 IS pressed, move to the BLUE state

                }
            }
            else {
                state = OFF;        // if the buttons were was NOT pressed, stay in the OFF state
            }
            break;

        case RED:
            P2->OUT &= ~7;               // Initialized with the LED off
            P2->OUT |= 1;                // Turns on BIT0 (Red LED on)
            if (SwitchBounce()) {
                if(!but_flag)
                {
                    state = GREEN;       // if the button 1 IS pressed, move to the GREEN state

                }
                if(but_flag)
                {
                    state = BLUE;        // if the button 2 IS pressed, move to the BLUE state

                }                }
            else {
                state = RED;        // if the buttons were was NOT pressed, stay in the RED state
            }
            break;

        case GREEN:
            P2->OUT &= ~7;              // Initialized with the LED off
            P2->OUT |= 2;               // Turns off BIT0 and turns on BIT1 (Green LED on)
            if (SwitchBounce()) {
                if(!but_flag)
                {
                    state = BLUE;       // if the button 2 IS pressed, move to the BLUE state

                }
                if(but_flag)
                {
                    state = RED;        // if the switch button 2 IS pressed, move to the RED state

                }
            }
            else {
                state = GREEN;       // if the buttons were NOT pressed, stay in the GREEN state
            }
            break;

        case BLUE:
            P2->OUT &= ~7;           // Initialized with the LED off
            P2->OUT |=4;             // Turns off BIT1 and turns on BIT2 (Green LED on)

            if (SwitchBounce()) {
                if(!but_flag)
                {
                    state = RED;     // if the button 1 IS pressed, move to the RED state

                }
                if(but_flag)
                {
                    state = GREEN;   // if the button 2 IS pressed, move to the GREEN state

                }
            }
            else {
                state = BLUE;        // if the switch button was NOT pressed, stay in the BLUE state
            }
            break;
        default:
            P2->OUT &= ~7;           // We want the LED to be off in the default state
            break;
        }
    }
}



/*
 * This functions initializes the SysTick Timer
 */
void delay1s() {
    SysTick -> LOAD = 3000000 - 1;        // 1s Delay is 1s / (1 / 3MHz))
    SysTick -> VAL = 0;         // Clear Current Value Register
    SysTick -> CTRL = 5;        // Enable the SysTick Timer

    while ((SysTick -> CTRL & BIT(16)) == 0) {
        /*
         * Wait until the COUNTFLAG is set
         */
    }

    SysTick -> CTRL = 0;        // Stop the Timer (Enable = 0)
}

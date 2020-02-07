#include "msp.h"

/*
 * Author: Hector Garcia
 * Course: EGR 226
 * Section: 905
 * Professor Ekin
 * Date: February 7, 2020
 *
 * Description: This program will initialize with the RGD LED off
 * and will cycle through Red -> Green -> Blue -> Red, etc. as the
 * switch button 1 is pressed.
 */

// Function Prototypes
    int SwitchBounce();         // Switch Bounce Function
    void init_ports();          // Port Initialization Function
    void state_machine();       // State Machine Function

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watch dog timer


	while(1) {
	    init_ports();           // Calls the Port Initialization Function
	    state_machine();        // Calls the State Machine Function
        }
    }

/*
 * This function avoids reading the pushbutton switch during a switch bounce
 * interval
 */
int SwitchBounce() {

    uint8_t flag = 0;       // Variable is changed when switch button is pressed

    // These nested if statements check to see if the button is pressed
    // button pressed is active low, so we are checking for 0's twice.
    // we are delaying 5ms to verify the button was actually pressed
    // if it is pressed, the flag is set HIGH (1)

    while (1) {
        if ((P1->IN & 0x02) == 0) {
            __delay_cycles(15000);      // When cycles equals 15,000, the delay will be 5ms

            if ((P1->IN & 0x02) == 0) {
                flag = 1;       // flag is set to 1 meaning button is pressed
                // If the button is held down, it will not do anything
                while (1) {
                    if (!((P1->IN & 0x02) == 0)) {
                        break;
                    }
                }
            }
        }
        return flag;
    }
}
/*
 * This function will initialize port 1 pin 1 into an input
 * and port 2 pins 0, 1, and 2 as outputs. Further, it sets
 * the proper directions for the port pins, enables port 1
 * pin 1's internal resistor and sets it as a pull-up resistor,
 * and initializes the LED to be off
 */
void init_ports() {
    P1->SEL0 &= ~0x02;        // Setting SEL0 and SEL1 in Port 1 to be Simple I/O
    P1->SEL1 &= ~0x02;

    P1->DIR &= ~0x02;         // Setting the direction of Port 1 Pin 1 to be an input
    P1->REN |= 0x02;          // Internal Resistor is enabled
    P1->OUT |= 0x02;          // Resistor is configured as a Pull-Up Resistor
                              // We want a pull-up resistor because we are reading for
                              // 0's to verify the button was pressed

    P2->SEL0 &= ~0x07;        // Setting SEL0 and SEL1 in Port 2 to be Simple I/O
    P2->SEL1 &= ~0x07;

    P2->DIR |= 0x07;          // Sets pins 0, 1, 23 in Port 2 as outputs (RGB LED)
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
            P2OUT &= ~7;                // Initialized with the LED off
                if (SwitchBounce()) {
                    state = RED;        // if the switch button IS pressed, move to the RED state
                }
                else {
                    state = OFF;        // if the switch button was NOT pressed, stay in the OFF state
                }
                break;

        case RED:
            P2OUT &= ~7;                // Initialized with the LED off
            P2OUT |= 1;                 // Turns on BIT0 (Red LED on)
                if (SwitchBounce()) {
                    state = GREEN;      // if the switch buttons IS pressed, move to the GREEN state
                }
                else {
                    state = RED;        // if the switch button was NOT pressed, stay in the RED state
                }
                break;

        case GREEN:
            P2OUT &= ~7;                 // Initialized with the LED off
            P2OUT |= 2;                  // Turns off BIT0 and turns on BIT1 (Green LED on)
                if (SwitchBounce()) {
                    state = BLUE;        // if the switch button was IS pressed, move to the BLUE state
                }
                else {
                    state = GREEN;       // if the switch button was NOT pressed, stay in the GREEN state
                }
                break;

        case BLUE:
            P2OUT &= ~7;                // Initialized with the LED off
            P2OUT |=4;                  // Turns off BIT1 and turns on BIT2 (Green LED on)

                if (SwitchBounce()) {
                    state = RED;         // if the switch button was IS pressed, move to the RED state
                }
                else {
                    state = BLUE;        // if the switch button was NOT pressed, stay in the BLUE state
                }
                break;
        default:
            P2OUT &= ~7;                 // We want the LED to be off in the default state
            break;
        }
    }
}

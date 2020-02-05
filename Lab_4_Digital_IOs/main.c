#include "msp.h"

/*
 * Author: Hector Garcia
 * Course: EGR 226
 * Section: 905
 * Professor Ekin
 * Date: February 7, 2020
 *
 * Description:
 */

    // Function Prototypes
    int SwitchBounce();   // Switch Bounce function

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watch dog timer

	P1SEL0 &= ~0x02;        // Setting SEL0 and SEL1 in Port 1 to be Simple I/O
	P1SEL1 &= ~0x02;

    P1DIR &= ~0x02;         // Setting the direction of Port 1 Pin 1 to be an input
    P1REN |= 0x02;          // Internal Resistor is enabled
    P1OUT |= 0x02;          // Resistor is configured as a Pull-Up Resistor
                            // We want a pull-up resistor because we are reading for
                            // 0's to verify the button was pressed

	P2SEL0 &= ~0x07;        // Setting SEL0 and SEL1 in Port 2 to be Simple I/O
	P2SEL1 &= ~0x07;

	P2DIR |= 0x07;          // Sets pins 1, 2, 3 in Port 2 as outputs (RGB LED)

	if (SwitchBounce()) {
	    P2OUT |= 0x07;      // Turns on RGB LED
	}
	else {
	    P2OUT &= 0x07;      // Turns off RGB LED
	}

}

int SwitchBounce() {

    uint8_t flag = 0;       // Variable is changed when switch button is pressed

                                 // Cycles sets the delay; 15,000 translates to 5ms of delay
    // uint16_t cycles = 15000;     // Set as a variable to accommodate future changes, uint16_t range is 0 to 65,535

    // These nested if statements check to see if the button is pressed
    // button pressed is active low, so we are checking for 0's twice.
    // we are delaying 5ms to verify the button was actually pressed
    // if it is pressed, the flag is set HIGH (1)

    if ((P1IN & 0x02)) {
        _delay_cycles(15000);      // When cycles equals 15,000, the delay will be 5ms

        if ((P1IN & 0x02)) {
            flag = 1;       // flag is set to 1 meaning button is pressed
        }
    }

    return flag;
}

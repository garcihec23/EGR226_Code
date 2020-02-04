#include "msp.h"

void delay(int n);

void main(void)
{
    P2SEL0 &= 0;    // SEL 0 and SEL 1 are 0 therefore configured as Simple I/O
    P2SEL1 &= 0;

    P2DIR |= 0x07;      // Setting pins 1, 2, and 3 as outputs


    while (1) {
        P2OUT |= BIT0;      // Sets pin 1 in port 2 HIGH (Turns on the Red LED)
        delay(1000);

        P2OUT &= ~BIT0;      // Sets pin 1 in port 2 HIGH (Turns off the Red LED)
        delay(1000);

        P2OUT |= BIT1;      // Sets pin 1 in port 2 HIGH (Turns on the Green LED)
        delay(1000);

        P2OUT &= ~BIT1;     // Sets pin 1 in port 2 LOW (Turns off the Green LED)
        delay(1000);

        P2OUT |= BIT2;      // Sets pin 1 in port 2 HIGH (Turns on the Blue LED)
        delay(1000);

        P2OUT &= ~BIT2;      // Sets pin 1 in port 2 HIGH (Turns off the Blue LED)
        delay(1000);

        P2OUT |= 0x07;      // Sets pin 1 in port 2 HIGH (Turns on the RGB LED)
        delay(1000);

        P2OUT &= ~0x07;      // Sets pin 1 in port 2 HIGH (Turns off the RGB LED)
        delay(1000);

    }
}


void delay(int n) {
    int i, j;

    for (j = 0; j < n ; j++) {
        for (i = 250; i > 0; i--);
    }
}

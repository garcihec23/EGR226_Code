#include "msp.h"
#include "keypad.h"
#include <stdint.h>
#include <stdio.h>


void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	Init_Keypad();              // Calls the Keypad Initialization Function
	uint16_t button = 0x0000;
	button = Button_Pressed;

    while(1) {
        Print_Button (button);        // Calls the State Machine Function
  }
}

/*
 * Print_Button () prints the value of the button pressed
 */

void Print_Button (uint16_t button) {

    while (1) {
            switch (button) {

            case '1':
                    printf("The button pressed is 3\n\n");
                    break;
            case '2':
                    printf("The button pressed is 6\n\n");
                    break;
            case '4':
                    printf("The button pressed is 9\n\n");
                    break;
            case '8':
                    printf("The button pressed is #\n\n");
                    break;
            case '16':
                    printf("The button pressed is 2\n\n");
                    break;
            case '32':
                    printf("The button pressed is 5\n\n");
                    break;
            case '64':
                    printf("The button pressed is 8\n\n");
                    break;
            case '128':
                    printf("The button pressed is 0\n\n");
                    break;
            case '256':
                    printf("The button pressed is 1\n\n");
                    break;
            case '512':
                    printf("The button pressed is 4\n\n");
                    break;
            case '1024':
                    printf("The button pressed is 7\n\n");
                    break;
            case '2048':
                    printf("The button pressed is *\n\n");
                    break;

            default:
                printf("We are in the default case, you shouldn't be here\n\n");
                break;
            }
        }
}

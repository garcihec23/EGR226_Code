#include "msp.h"
#include "keypad.h"
#include <stdint.h>
#include <stdio.h>

void Print_Button(uint16_t button);        // Print_Button function prototype

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	Init_Keypad();              // Calls the Keypad Initialization Function
    uint16_t button = 0x0000;
    while(1) {
        button = Button_Pressed(button);    // The 'button' variable is assigned the 16-bit number returned by Button_Pressed()

        Systick_Delay(100); // Creates a 10 ms delay
            if (!button) {
            }
            else {
                Print_Button(button);        // Calls the State Machine Function
            }
    }
  }

/*
 * Print_Button () prints the value of the button pressed
 */

void Print_Button (uint16_t button) {

        switch (button) {

            case 1:
                    printf("The button pressed is 3\n\n");
                    Systick_Delay(100);
                    break;
            case 2:
                    printf("The button pressed is 6\n\n");
                    Systick_Delay(100);
                    break;
            case 4:
                    printf("The button pressed is 9\n\n");
                    Systick_Delay(100);
                    break;
            case 8:
                    printf("The button pressed is #\n\n");
                    Systick_Delay(100);
                    break;
            case 16:
                    printf("The button pressed is 2\n\n");
                    Systick_Delay(100);
                    break;
            case 32:
                    printf("The button pressed is 5\n\n");
                    Systick_Delay(100);
                    break;
            case 64:
                    printf("The button pressed is 8\n\n");
                    Systick_Delay(100);
                    break;
            case 128:
                    printf("The button pressed is 0\n\n");
                    Systick_Delay(100);
                    break;
            case 256:
                    printf("The button pressed is 1\n\n");
                    Systick_Delay(100);
                    break;
            case 512:
                    printf("The button pressed is 4\n\n");
                    Systick_Delay(100);
                    break;
            case 1024:
                    printf("The button pressed is 7\n\n");
                    Systick_Delay(100);
                    break;
            case 2048:
                    printf("The button pressed is *\n\n");
                    Systick_Delay(100);
                    break;

            default:
                printf("We are in the default case, you shouldn't be here\n\n");
                Systick_Delay(100);
                break;
        }
}

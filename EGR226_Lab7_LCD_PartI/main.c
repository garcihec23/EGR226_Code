#include "msp.h"
#include "lcd.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	init_systick_delay();
	init_LCD_pins();
	init_LCD();


	char    myName[6] = {'H','e', 'c', 't', 'o', 'r',},
	        p_name[7] = {'T', '.', ' ', 'E', 'k', 'i', 'n',},
	        course[3] = {'E', 'G', 'R',},
	        num[3] = {'2', '2', '6',};

	command_write(0x01);    // Clear the Display
	micro_delay(500);       // Delay 500 us

    command_write(0x02);    // Return Home
    micro_delay(500);       // Delay 500 us

    command_write(0x85);    // address 05 1st line
    micro_delay(500);       // Delay 500 us

	int i = 0;              // Local Variable

	/*
	 * Prints my name!
	 */
	for(i = 0; i < 6; i++) {
	    data_write(myName[i]);

	    milli_delay(100);
	}

	command_write(0xC4);    // Address 45 2nd line
	micro_delay(500);

//    /*
//     * Prints partner's name
//     */
//    for(i = 0;i < 7; i++) {
//        data_write(p_name[i]);
//        milli_delay(100);
//    }
//
//    command_write(0x96);    // Address 16 3rd line
//    micro_delay(500);
//
//    /*
//     * Prints course name
//     */
//    for(i = 0; i < 3; i++)
//    {
//        data_write(course[i]);
//        milli_delay(100);
//    }
//
//    command_write(0xD6);// address 56 4th line
//    micro_delay(500);
//
//    /*
//     * Prints course number
//     */
//    for(i = 0; i < 3; i++)
//    {
//        data_write(num[i]);
//        milli_delay(100);
    }

	while (1);  // Keeps main() alive

}

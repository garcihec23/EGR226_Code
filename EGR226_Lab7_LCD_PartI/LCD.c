#include "msp.h"
#include "lcd.h"
#include <stdint.h>
#include <stdio.h>

void Init_LCD () {

}



/*
 * This function initializes the SysTick Timer
 * and creates a delay depending on the argument in ms
 */
void Systick_Delay(uint16_t delay) {
    SysTick -> LOAD = (3000 * delay) - 1;        // Delay is (3000 * specified time in milliseconds) / (1 / 3MHz))
    SysTick -> VAL = 0;                          // Clear Current Value Register
    SysTick -> CTRL = 5;                         // Enable the SysTick Timer

    while ((SysTick -> CTRL & BIT(16)) == 0) {
        /*
         * Wait until the COUNTFLAG is set
         */
    }

    SysTick -> CTRL = 0;        // Stop the Timer (Enable = 0)

}

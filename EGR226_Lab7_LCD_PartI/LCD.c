#include "msp.h"
#include "lcd.h"
#include <stdint.h>
#include <stdio.h>

/*
 * The init_LCD_pins() function initializes the the pins for the LCD as outputs
 * NOTE: The RW pin is not initialized b/c it is never pulsed high (we don't read instructions in), it remains low
 * always in the case of the LCD, therefore it is connected to ground physically on the MSP432 Launch Pad
 */
void init_LCD_pins() {

    RS_PORT -> SEL0 &= ~RS_PIN;     // SEL0 and SEL1 are set to 0 and turns RS_PIN as a Simple I/O
    RS_PORT -> SEL1 &= ~RS_PIN;
    RS_PORT -> DIR |= RS_PIN;       // Sets the RS pins to be an output
    RS_PORT -> OUT |= RS_PIN;

    EN_PORT -> SEL0 &= ~EN_PIN;
    EN_PORT -> SEL1 &= ~EN_PIN;
    EN_PORT -> DIR |= EN_PIN;       // Sets the Enable pin to be an output
    EN_PORT -> OUT |= EN_PIN;

    DATA_PORT -> SEL0 &= ~DATA_PIN;
    DATA_PORT -> SEL1 &= ~DATA_PIN;
    DATA_PORT -> DIR |= DATA_PIN;   // Sets the MSBs of the Data pins to be an output
    DATA_PORT -> OUT |= DATA_PIN;

}

/*
 * The init_LCD() function goes through the initialization sequence
 * that is required by the LCD to function properly
 */
void init_LCD () {

        milli_delay(100);

// Reset
        command_write(0x30);
        milli_delay(110);

        command_write(0x30);
        micro_delay(110);

        command_write(0x30);
        micro_delay(110);

        command_write(0x20);
        micro_delay(110);

// -------------- Initialization Sequence ---------------

        command_write(0x28); // Function set
        micro_delay(60);

        command_write(0x0C); // Display On (default should be 0x0F, cursor on and  blinking)
        micro_delay(60);

        command_write(0x01); // Clear
        milli_delay(10);

        command_write(0x06); // Entry mode
        micro_delay(60);

}

/*
 * The push_nibble() function takes in an 8-bit number, nibble which gets masked, then shifted 4-bits to the left.
 * This is done because we are only using the MSBs of any port (to reduce the number of pins physically used). Then
 * the pulse_enable() function is called which pulses enable HIGH to LOW
 */
void push_nibble(uint8_t nibble) {
    DATA_PORT -> OUT &= ~0xF0;                  // This clears the MSBs of DATA_PORT to make sure nothing extra is being shifted in causing errors
    DATA_PORT -> OUT |= (nibble & 0x0F) << 4;   // Nibble is masked with 0x0F, then shift 4-bits and assigned to DATA_PORT
    pulse_enable();                             // By calling the pulse_enable() function, the 4-bits are moved to the DATA_PORT
}

/*
 * The push_byte() function accepts an 8-bit number, "byte" first takes the 8-bit number
 * masks it with 0xF0, and shifts the MSBs of the 8-bit number to the right 4 bits,
 * then assigns the new 8-bit number to the local 8-bit variable, nibble. This happens
 * again, however now the LSBs of the 8-bit number, "byte" are assigned to nibble.
 */
void push_byte(uint8_t byte) {

    uint8_t nibble;     // Local 8-bit variable

    nibble = (byte & 0xF0) >> 4;    // Masks byte with 0xF0 and shift the byte's MSBs to the LSBs and assign to nibble
    push_nibble(nibble);            // Calls the push_nibble() function

    nibble = byte & 0x0F;    // Mask byte with 0x0F and assign LSBs of 'byte' to nibble
    push_nibble(nibble);     // Calls the push_nibble() function
    micro_delay(100);
}

/*
 * The command_write() function keeps RS as 0
 */
void command_write(uint8_t data) {
    RS_PORT -> OUT &= ~RS_PIN;
    push_byte(data);
}

/*
 * The write_data() function keeps RS as 1 so data can be written
 */
void data_write(uint8_t data) {
    RS_PORT -> OUT |= RS_PIN;
    push_byte(data);
}

/*
 * The pulse_enable() function pulses the enable from high to low
 * which causes instructions/commands to move and be executed
 * NOTE: a delay is required to make sure Enable does in fact goes
 * HIGH
 */
void pulse_enable() {

    EN_PORT -> OUT &= ~EN_PIN;      // Enable is brought down to 0
    micro_delay(10);                // Delay of 10 us

    EN_PORT -> OUT |= EN_PIN;       // Enable is brought high to 1
    micro_delay(10);                // Delay of 10 us

    EN_PORT -> OUT &= ~EN_PIN;      // Enable is pulsed down to 0
    micro_delay(10);                // Delay of 10 us

}


/*
 * The init_systick_delay() function initializes the SysTick Timer
 */
void init_systick_delay(void) {
    SysTick -> CTRL = 0;
    SysTick -> LOAD = 0x00FFFFFF;
    SysTick -> VAL = 0;                          // Clear Current Value Register
    SysTick -> CTRL = 0x00000005;                // Enable the SysTick Timer
}

/*
 * The micro_delay() function utilizes the SysTick Timer
 * to create a micro delay (in microseconds)
 */
void micro_delay(unsigned us) {

    SysTick -> LOAD = (3 * us) - 1;
    SysTick -> VAL = 0;

    while ((SysTick -> CTRL & BIT(16)) == 0);

}

/*
 * The milli_delay() function utilizes the SysTick Timer
 * to create a milli delay (in milliseconds)
 */
void milli_delay(unsigned ms) {

    SysTick -> LOAD = (3000 * ms) - 1;
    SysTick -> VAL = 0;

    while ((SysTick -> CTRL & BIT(16)) == 0);

}

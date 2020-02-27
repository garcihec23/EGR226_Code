#ifndef __LCD_H__    // ifndef stands for if not defined
#define __LCD_H__

//#include <stdint.h>

/*
 * If we want to implement our LCD in a different project
 * and can't use the same pins, we only need to change these define
 * statements rather than going through the entire code
 */

// The LCD's Register Select (RS), Read/Write (R/W), and Enable (E) pins

    #define RS_PORT P4
    #define RS_PIN BIT0

//    #define RW_PIN is tied to GND

    #define EN_PORT P4
    #define EN_PIN BIT1

// The LCD's data pins are connected to Port 4 of the MCU, though this can be changed

    #define DATA_PORT P4
    #define DATA_PIN 0xF0

/*
 * Function Prototypes
 */

void init_LCD_pins();
void init_LCD();
void pulse_enable();
void push_nibble(uint8_t nibble);
void push_byte(uint8_t byte);
void command_write(uint8_t data);
void data_write(uint8_t data);

void init_systick_delay(void);
void micro_delay(unsigned us);
void milli_delay(unsigned ms);

#endif

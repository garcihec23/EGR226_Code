#ifndef __LCD_H__    // ifndef stands for if not defined
#define __LCD_H__

#include <stdint.h>

/*
 * If we want to implement our LCD in a different project
 * and can't use the same pins, we only need to change these define
 * statements rather than going through the entire code
 */

// The LCD's data pins are connected to Port 4 of the MCU, though this can be changed
    #define D0_PORT P4
    #define D0_PIN BIT0

    #define D1_PORT P4
    #define D1_PIN BIT1

    #define D2_PORT P4
    #define D2_PIN BIT2

    #define D3_PORT P4
    #define D3_PIN BIT3

    #define D4_PORT P4
    #define D4_PIN BIT4

    #define D5_PORT P4
    #define D5_PIN BIT5

    #define D6_PORT P4
    #define D6_PIN BIT6

    #define D7_PORT P4
    #define D7_PIN BIT7

// The LCD's Register Select (RS), Read/Write (R/W), and Enable (E) pins
    #define RS_PORT P3
    #define RS_PIN BIT2

    #define RW_PORT P6
    #define RW_PIN BIT1

    #define EN_PORT P3
    #define EN_PIN BIT3


/*
 * Function Prototypes
 */

#endif

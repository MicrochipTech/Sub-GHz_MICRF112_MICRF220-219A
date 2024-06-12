/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */


#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

#include <stdint.h>

#define IO_EXPD_ADDR 0x40   // SPI address of the IO Expander
#define GPIO_A 0x12          // Address of the GPIOA register
#define GPIO_B 0x13          // Address of the GPIOB register
#define IO_DIR_A 0x00         // Address of the IODIRA register
#define IO_DIR_B 0x01         // Address of the IODIRB register


/* Function to write to the IO expander which in turn talks with the LCD */
void WriteIOExpd (uint8_t reg, uint8_t data);

/* Function to  write a command to the LCD display*/
void WriteLcdCommand(uint8_t cmd);

/* Function to Initialize the LCD display*/
void LcdInitialization (void);

/* Function to write a byte of data to the LCD display*/
void WriteLcdByte(uint8_t data);

/* Function to write a string to the LCD display*/
void WriteLcdString(char *data);

/* Function to move the cursor to a desired location*/
void LcdGoto(uint8_t row, uint8_t column);

/* Function to clear the LCD display*/
void LcdClear(void);

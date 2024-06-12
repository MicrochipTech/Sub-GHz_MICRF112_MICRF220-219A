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


#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "lcd.h"
#include "mcc_generated_files/mcc.h"


/* 
Function: 
void WriteIOExpd (uint8_t reg, uint8_t data)

Description: 
 * Function used to write a byte to the IO expander
  */
void WriteIOExpd (uint8_t reg, uint8_t data)
{
          LCD_CHIP_SELECT_SetLow();
          spi1_exchangeByte(IO_EXPD_ADDR);
          spi1_exchangeByte(reg);           // Select the required register
          spi1_exchangeByte(data);          // Write the data
          LCD_CHIP_SELECT_SetHigh(); 
}



/* 
Function: 
void WriteLcdCommand(uint8_t cmd)

Description: 
 * Function used to write a command to the LCD screen
  */
void WriteLcdCommand(uint8_t cmd)
{
          WriteIOExpd(GPIO_A,0x60);    //RS LOW -- E HIGH -- LCD Enabled 

          WriteIOExpd(GPIO_B,cmd);     // Write the command on PORT B

          WriteIOExpd(GPIO_A,0x20);    //RS LOW -- E LOW -- LCD Enabled
}



/* 
Function: 
void WriteLcdByte(uint8_t data)

Description: 
 * Function used to write a byte on the LCD screen
  */
void WriteLcdByte(uint8_t data)
{
          WriteIOExpd(GPIO_A,0xE0);    //RS HIGH -- E HIGH -- LCD Enabled --> This is to choose the data register on the LCD

          WriteIOExpd(GPIO_B,data);    //Write the byte on PORT B

          WriteIOExpd(GPIO_A,0xA0);    //RS HIGH -- E LOW -- LCD enabled --> This is to latch the data on the LCD
}



/* 
Function: 
void WriteLcdString(char *data)

Description: 
 * Function used to write a string on the LCD screen
  */
void WriteLcdString(char *data)
{
    uint8_t i=0;
    while(data[i])
    {
        WriteLcdByte(data[i++]);
    }
}



/* 
Function: 
void LcdClear (void)

Description: 
 * Function used to clear the LCD screen
  */
void LcdClear(void)
{
    WriteLcdCommand(0x01);            // 0x01 is the command to clear the LCD Display
    LcdGoto(0,0);
}



/* 
Function: 
void LcdGoto (uint8_t row, uint8_t column)

Description: 
 * Function used to move the LCD cursor
  */
void LcdGoto(uint8_t row, uint8_t column)
{
    if (row<2)
        {
        uint8_t pos = (row == 0) ? (0x80 | column) : (0xC0 | column);       // 0x80 is the start address of Line 1 and 0xC0 for Line 2
        WriteLcdCommand(pos);
        }

}



/* 
Function: 
void LCDInitialization (void)

Description: 
 * Function used to initialize the LCD
  */
void LcdInitialization (void)
{
          WriteIOExpd(IO_DIR_A,0x00);   // Make PORT A as output
          WriteIOExpd(IO_DIR_B,0x00);   // Make PORT B as output

          WriteIOExpd(GPIO_A,0x20);     // Enable VDD for the LCD panel

          __delay_ms(10);      // delay required to correctly initialize the LCD

          WriteLcdCommand(0x3C);

          __delay_ms(10);

          WriteLcdCommand(0x0C);

          __delay_ms(10);

           WriteLcdCommand(0x01); // Clear the display

          __delay_ms(10);

          WriteLcdCommand(0x0C);

//          __delay_ms(130);    // Delay required to let the LCD initialize correctly
          __delay_ms(20);
          __delay_ms(20);
          __delay_ms(20);
          __delay_ms(20);
          __delay_ms(20);
          __delay_ms(20);
          __delay_ms(20);

          WriteLcdCommand(0x80);

          __delay_ms(1);

}
/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC18F47K40
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB 	          :  MPLAB X 4.15	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set LCD_CHIP_SELECT aliases
#define LCD_CHIP_SELECT_TRIS                 TRISAbits.TRISA2
#define LCD_CHIP_SELECT_LAT                  LATAbits.LATA2
#define LCD_CHIP_SELECT_PORT                 PORTAbits.RA2
#define LCD_CHIP_SELECT_WPU                  WPUAbits.WPUA2
#define LCD_CHIP_SELECT_OD                   ODCONAbits.ODCA2
#define LCD_CHIP_SELECT_ANS                  ANSELAbits.ANSELA2
#define LCD_CHIP_SELECT_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define LCD_CHIP_SELECT_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define LCD_CHIP_SELECT_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define LCD_CHIP_SELECT_GetValue()           PORTAbits.RA2
#define LCD_CHIP_SELECT_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define LCD_CHIP_SELECT_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define LCD_CHIP_SELECT_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define LCD_CHIP_SELECT_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define LCD_CHIP_SELECT_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define LCD_CHIP_SELECT_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define LCD_CHIP_SELECT_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define LCD_CHIP_SELECT_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set S1 aliases
#define S1_TRIS                 TRISBbits.TRISB0
#define S1_LAT                  LATBbits.LATB0
#define S1_PORT                 PORTBbits.RB0
#define S1_WPU                  WPUBbits.WPUB0
#define S1_OD                   ODCONBbits.ODCB0
#define S1_ANS                  ANSELBbits.ANSELB0
#define S1_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define S1_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define S1_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define S1_GetValue()           PORTBbits.RB0
#define S1_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define S1_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define S1_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define S1_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define S1_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define S1_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define S1_SetAnalogMode()      do { ANSELBbits.ANSELB0 = 1; } while(0)
#define S1_SetDigitalMode()     do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set IO_RB5 aliases
#define IO_RB5_TRIS                 TRISBbits.TRISB5
#define IO_RB5_LAT                  LATBbits.LATB5
#define IO_RB5_PORT                 PORTBbits.RB5
#define IO_RB5_WPU                  WPUBbits.WPUB5
#define IO_RB5_OD                   ODCONBbits.ODCB5
#define IO_RB5_ANS                  ANSELBbits.ANSELB5
#define IO_RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define IO_RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define IO_RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define IO_RB5_GetValue()           PORTBbits.RB5
#define IO_RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define IO_RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define IO_RB5_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define IO_RB5_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define IO_RB5_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define IO_RB5_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define IO_RB5_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define IO_RB5_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set AN_CH_RSSI aliases
#define AN_CH_RSSI_TRIS                 TRISCbits.TRISC0
#define AN_CH_RSSI_LAT                  LATCbits.LATC0
#define AN_CH_RSSI_PORT                 PORTCbits.RC0
#define AN_CH_RSSI_WPU                  WPUCbits.WPUC0
#define AN_CH_RSSI_OD                   ODCONCbits.ODCC0
#define AN_CH_RSSI_ANS                  ANSELCbits.ANSELC0
#define AN_CH_RSSI_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define AN_CH_RSSI_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define AN_CH_RSSI_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define AN_CH_RSSI_GetValue()           PORTCbits.RC0
#define AN_CH_RSSI_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define AN_CH_RSSI_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define AN_CH_RSSI_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define AN_CH_RSSI_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define AN_CH_RSSI_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define AN_CH_RSSI_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define AN_CH_RSSI_SetAnalogMode()      do { ANSELCbits.ANSELC0 = 1; } while(0)
#define AN_CH_RSSI_SetDigitalMode()     do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set SCK1 aliases
#define SCK1_TRIS                 TRISCbits.TRISC3
#define SCK1_LAT                  LATCbits.LATC3
#define SCK1_PORT                 PORTCbits.RC3
#define SCK1_WPU                  WPUCbits.WPUC3
#define SCK1_OD                   ODCONCbits.ODCC3
#define SCK1_ANS                  ANSELCbits.ANSELC3
#define SCK1_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define SCK1_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define SCK1_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define SCK1_GetValue()           PORTCbits.RC3
#define SCK1_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define SCK1_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define SCK1_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define SCK1_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define SCK1_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define SCK1_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define SCK1_SetAnalogMode()      do { ANSELCbits.ANSELC3 = 1; } while(0)
#define SCK1_SetDigitalMode()     do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set SDI1 aliases
#define SDI1_TRIS                 TRISCbits.TRISC4
#define SDI1_LAT                  LATCbits.LATC4
#define SDI1_PORT                 PORTCbits.RC4
#define SDI1_WPU                  WPUCbits.WPUC4
#define SDI1_OD                   ODCONCbits.ODCC4
#define SDI1_ANS                  ANSELCbits.ANSELC4
#define SDI1_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define SDI1_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define SDI1_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define SDI1_GetValue()           PORTCbits.RC4
#define SDI1_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define SDI1_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define SDI1_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define SDI1_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define SDI1_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define SDI1_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define SDI1_SetAnalogMode()      do { ANSELCbits.ANSELC4 = 1; } while(0)
#define SDI1_SetDigitalMode()     do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set SDO1 aliases
#define SDO1_TRIS                 TRISCbits.TRISC5
#define SDO1_LAT                  LATCbits.LATC5
#define SDO1_PORT                 PORTCbits.RC5
#define SDO1_WPU                  WPUCbits.WPUC5
#define SDO1_OD                   ODCONCbits.ODCC5
#define SDO1_ANS                  ANSELCbits.ANSELC5
#define SDO1_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define SDO1_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define SDO1_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define SDO1_GetValue()           PORTCbits.RC5
#define SDO1_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define SDO1_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define SDO1_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define SDO1_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define SDO1_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define SDO1_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define SDO1_SetAnalogMode()      do { ANSELCbits.ANSELC5 = 1; } while(0)
#define SDO1_SetDigitalMode()     do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set RF_DATA_IN aliases
#define RF_DATA_IN_TRIS                 TRISCbits.TRISC6
#define RF_DATA_IN_LAT                  LATCbits.LATC6
#define RF_DATA_IN_PORT                 PORTCbits.RC6
#define RF_DATA_IN_WPU                  WPUCbits.WPUC6
#define RF_DATA_IN_OD                   ODCONCbits.ODCC6
#define RF_DATA_IN_ANS                  ANSELCbits.ANSELC6
#define RF_DATA_IN_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RF_DATA_IN_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RF_DATA_IN_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RF_DATA_IN_GetValue()           PORTCbits.RC6
#define RF_DATA_IN_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RF_DATA_IN_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RF_DATA_IN_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define RF_DATA_IN_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define RF_DATA_IN_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define RF_DATA_IN_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define RF_DATA_IN_SetAnalogMode()      do { ANSELCbits.ANSELC6 = 1; } while(0)
#define RF_DATA_IN_SetDigitalMode()     do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set SLICE aliases
#define SLICE_TRIS                 TRISDbits.TRISD0
#define SLICE_LAT                  LATDbits.LATD0
#define SLICE_PORT                 PORTDbits.RD0
#define SLICE_WPU                  WPUDbits.WPUD0
#define SLICE_OD                   ODCONDbits.ODCD0
#define SLICE_ANS                  ANSELDbits.ANSELD0
#define SLICE_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define SLICE_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define SLICE_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define SLICE_GetValue()           PORTDbits.RD0
#define SLICE_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define SLICE_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define SLICE_SetPullup()          do { WPUDbits.WPUD0 = 1; } while(0)
#define SLICE_ResetPullup()        do { WPUDbits.WPUD0 = 0; } while(0)
#define SLICE_SetPushPull()        do { ODCONDbits.ODCD0 = 0; } while(0)
#define SLICE_SetOpenDrain()       do { ODCONDbits.ODCD0 = 1; } while(0)
#define SLICE_SetAnalogMode()      do { ANSELDbits.ANSELD0 = 1; } while(0)
#define SLICE_SetDigitalMode()     do { ANSELDbits.ANSELD0 = 0; } while(0)

// get/set IO_RD1 aliases
#define IO_RD1_TRIS                 TRISDbits.TRISD1
#define IO_RD1_LAT                  LATDbits.LATD1
#define IO_RD1_PORT                 PORTDbits.RD1
#define IO_RD1_WPU                  WPUDbits.WPUD1
#define IO_RD1_OD                   ODCONDbits.ODCD1
#define IO_RD1_ANS                  ANSELDbits.ANSELD1
#define IO_RD1_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define IO_RD1_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define IO_RD1_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define IO_RD1_GetValue()           PORTDbits.RD1
#define IO_RD1_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define IO_RD1_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define IO_RD1_SetPullup()          do { WPUDbits.WPUD1 = 1; } while(0)
#define IO_RD1_ResetPullup()        do { WPUDbits.WPUD1 = 0; } while(0)
#define IO_RD1_SetPushPull()        do { ODCONDbits.ODCD1 = 0; } while(0)
#define IO_RD1_SetOpenDrain()       do { ODCONDbits.ODCD1 = 1; } while(0)
#define IO_RD1_SetAnalogMode()      do { ANSELDbits.ANSELD1 = 1; } while(0)
#define IO_RD1_SetDigitalMode()     do { ANSELDbits.ANSELD1 = 0; } while(0)

// get/set IO_RD2 aliases
#define IO_RD2_TRIS                 TRISDbits.TRISD2
#define IO_RD2_LAT                  LATDbits.LATD2
#define IO_RD2_PORT                 PORTDbits.RD2
#define IO_RD2_WPU                  WPUDbits.WPUD2
#define IO_RD2_OD                   ODCONDbits.ODCD2
#define IO_RD2_ANS                  ANSELDbits.ANSELD2
#define IO_RD2_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define IO_RD2_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define IO_RD2_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define IO_RD2_GetValue()           PORTDbits.RD2
#define IO_RD2_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define IO_RD2_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define IO_RD2_SetPullup()          do { WPUDbits.WPUD2 = 1; } while(0)
#define IO_RD2_ResetPullup()        do { WPUDbits.WPUD2 = 0; } while(0)
#define IO_RD2_SetPushPull()        do { ODCONDbits.ODCD2 = 0; } while(0)
#define IO_RD2_SetOpenDrain()       do { ODCONDbits.ODCD2 = 1; } while(0)
#define IO_RD2_SetAnalogMode()      do { ANSELDbits.ANSELD2 = 1; } while(0)
#define IO_RD2_SetDigitalMode()     do { ANSELDbits.ANSELD2 = 0; } while(0)

// get/set IO_RD3 aliases
#define IO_RD3_TRIS                 TRISDbits.TRISD3
#define IO_RD3_LAT                  LATDbits.LATD3
#define IO_RD3_PORT                 PORTDbits.RD3
#define IO_RD3_WPU                  WPUDbits.WPUD3
#define IO_RD3_OD                   ODCONDbits.ODCD3
#define IO_RD3_ANS                  ANSELDbits.ANSELD3
#define IO_RD3_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define IO_RD3_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define IO_RD3_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define IO_RD3_GetValue()           PORTDbits.RD3
#define IO_RD3_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define IO_RD3_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define IO_RD3_SetPullup()          do { WPUDbits.WPUD3 = 1; } while(0)
#define IO_RD3_ResetPullup()        do { WPUDbits.WPUD3 = 0; } while(0)
#define IO_RD3_SetPushPull()        do { ODCONDbits.ODCD3 = 0; } while(0)
#define IO_RD3_SetOpenDrain()       do { ODCONDbits.ODCD3 = 1; } while(0)
#define IO_RD3_SetAnalogMode()      do { ANSELDbits.ANSELD3 = 1; } while(0)
#define IO_RD3_SetDigitalMode()     do { ANSELDbits.ANSELD3 = 0; } while(0)

// get/set IO_RD4 aliases
#define IO_RD4_TRIS                 TRISDbits.TRISD4
#define IO_RD4_LAT                  LATDbits.LATD4
#define IO_RD4_PORT                 PORTDbits.RD4
#define IO_RD4_WPU                  WPUDbits.WPUD4
#define IO_RD4_OD                   ODCONDbits.ODCD4
#define IO_RD4_ANS                  ANSELDbits.ANSELD4
#define IO_RD4_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define IO_RD4_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define IO_RD4_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define IO_RD4_GetValue()           PORTDbits.RD4
#define IO_RD4_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define IO_RD4_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define IO_RD4_SetPullup()          do { WPUDbits.WPUD4 = 1; } while(0)
#define IO_RD4_ResetPullup()        do { WPUDbits.WPUD4 = 0; } while(0)
#define IO_RD4_SetPushPull()        do { ODCONDbits.ODCD4 = 0; } while(0)
#define IO_RD4_SetOpenDrain()       do { ODCONDbits.ODCD4 = 1; } while(0)
#define IO_RD4_SetAnalogMode()      do { ANSELDbits.ANSELD4 = 1; } while(0)
#define IO_RD4_SetDigitalMode()     do { ANSELDbits.ANSELD4 = 0; } while(0)

// get/set IO_RD5 aliases
#define IO_RD5_TRIS                 TRISDbits.TRISD5
#define IO_RD5_LAT                  LATDbits.LATD5
#define IO_RD5_PORT                 PORTDbits.RD5
#define IO_RD5_WPU                  WPUDbits.WPUD5
#define IO_RD5_OD                   ODCONDbits.ODCD5
#define IO_RD5_ANS                  ANSELDbits.ANSELD5
#define IO_RD5_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define IO_RD5_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define IO_RD5_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define IO_RD5_GetValue()           PORTDbits.RD5
#define IO_RD5_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define IO_RD5_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define IO_RD5_SetPullup()          do { WPUDbits.WPUD5 = 1; } while(0)
#define IO_RD5_ResetPullup()        do { WPUDbits.WPUD5 = 0; } while(0)
#define IO_RD5_SetPushPull()        do { ODCONDbits.ODCD5 = 0; } while(0)
#define IO_RD5_SetOpenDrain()       do { ODCONDbits.ODCD5 = 1; } while(0)
#define IO_RD5_SetAnalogMode()      do { ANSELDbits.ANSELD5 = 1; } while(0)
#define IO_RD5_SetDigitalMode()     do { ANSELDbits.ANSELD5 = 0; } while(0)

// get/set IO_RD6 aliases
#define IO_RD6_TRIS                 TRISDbits.TRISD6
#define IO_RD6_LAT                  LATDbits.LATD6
#define IO_RD6_PORT                 PORTDbits.RD6
#define IO_RD6_WPU                  WPUDbits.WPUD6
#define IO_RD6_OD                   ODCONDbits.ODCD6
#define IO_RD6_ANS                  ANSELDbits.ANSELD6
#define IO_RD6_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define IO_RD6_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define IO_RD6_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define IO_RD6_GetValue()           PORTDbits.RD6
#define IO_RD6_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define IO_RD6_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define IO_RD6_SetPullup()          do { WPUDbits.WPUD6 = 1; } while(0)
#define IO_RD6_ResetPullup()        do { WPUDbits.WPUD6 = 0; } while(0)
#define IO_RD6_SetPushPull()        do { ODCONDbits.ODCD6 = 0; } while(0)
#define IO_RD6_SetOpenDrain()       do { ODCONDbits.ODCD6 = 1; } while(0)
#define IO_RD6_SetAnalogMode()      do { ANSELDbits.ANSELD6 = 1; } while(0)
#define IO_RD6_SetDigitalMode()     do { ANSELDbits.ANSELD6 = 0; } while(0)

// get/set IO_RD7 aliases
#define IO_RD7_TRIS                 TRISDbits.TRISD7
#define IO_RD7_LAT                  LATDbits.LATD7
#define IO_RD7_PORT                 PORTDbits.RD7
#define IO_RD7_WPU                  WPUDbits.WPUD7
#define IO_RD7_OD                   ODCONDbits.ODCD7
#define IO_RD7_ANS                  ANSELDbits.ANSELD7
#define IO_RD7_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define IO_RD7_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define IO_RD7_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define IO_RD7_GetValue()           PORTDbits.RD7
#define IO_RD7_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define IO_RD7_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define IO_RD7_SetPullup()          do { WPUDbits.WPUD7 = 1; } while(0)
#define IO_RD7_ResetPullup()        do { WPUDbits.WPUD7 = 0; } while(0)
#define IO_RD7_SetPushPull()        do { ODCONDbits.ODCD7 = 0; } while(0)
#define IO_RD7_SetOpenDrain()       do { ODCONDbits.ODCD7 = 1; } while(0)
#define IO_RD7_SetAnalogMode()      do { ANSELDbits.ANSELD7 = 1; } while(0)
#define IO_RD7_SetDigitalMode()     do { ANSELDbits.ANSELD7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/
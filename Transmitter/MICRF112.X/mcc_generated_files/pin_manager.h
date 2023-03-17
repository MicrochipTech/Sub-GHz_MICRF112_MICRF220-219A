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
        Device            :  PIC16F1619
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

// get/set CPU_ACTIVE aliases
#define CPU_ACTIVE_TRIS                 TRISBbits.TRISB7
#define CPU_ACTIVE_LAT                  LATBbits.LATB7
#define CPU_ACTIVE_PORT                 PORTBbits.RB7
#define CPU_ACTIVE_WPU                  WPUBbits.WPUB7
#define CPU_ACTIVE_OD                   ODCONBbits.ODB7
#define CPU_ACTIVE_ANS                  ANSELBbits.ANSB7
#define CPU_ACTIVE_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define CPU_ACTIVE_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define CPU_ACTIVE_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define CPU_ACTIVE_GetValue()           PORTBbits.RB7
#define CPU_ACTIVE_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define CPU_ACTIVE_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define CPU_ACTIVE_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define CPU_ACTIVE_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define CPU_ACTIVE_SetPushPull()        do { ODCONBbits.ODB7 = 0; } while(0)
#define CPU_ACTIVE_SetOpenDrain()       do { ODCONBbits.ODB7 = 1; } while(0)
#define CPU_ACTIVE_SetAnalogMode()      do { ANSELBbits.ANSB7 = 1; } while(0)
#define CPU_ACTIVE_SetDigitalMode()     do { ANSELBbits.ANSB7 = 0; } while(0)

// get/set MICRF_TX aliases
#define MICRF_TX_TRIS                 TRISCbits.TRISC2
#define MICRF_TX_LAT                  LATCbits.LATC2
#define MICRF_TX_PORT                 PORTCbits.RC2
#define MICRF_TX_WPU                  WPUCbits.WPUC2
#define MICRF_TX_OD                   ODCONCbits.ODC2
#define MICRF_TX_ANS                  ANSELCbits.ANSC2
#define MICRF_TX_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define MICRF_TX_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define MICRF_TX_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define MICRF_TX_GetValue()           PORTCbits.RC2
#define MICRF_TX_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define MICRF_TX_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define MICRF_TX_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define MICRF_TX_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define MICRF_TX_SetPushPull()        do { ODCONCbits.ODC2 = 0; } while(0)
#define MICRF_TX_SetOpenDrain()       do { ODCONCbits.ODC2 = 1; } while(0)
#define MICRF_TX_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define MICRF_TX_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set MICRF_ENABLE aliases
#define MICRF_ENABLE_TRIS                 TRISCbits.TRISC5
#define MICRF_ENABLE_LAT                  LATCbits.LATC5
#define MICRF_ENABLE_PORT                 PORTCbits.RC5
#define MICRF_ENABLE_WPU                  WPUCbits.WPUC5
#define MICRF_ENABLE_OD                   ODCONCbits.ODC5
#define MICRF_ENABLE_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define MICRF_ENABLE_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define MICRF_ENABLE_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define MICRF_ENABLE_GetValue()           PORTCbits.RC5
#define MICRF_ENABLE_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define MICRF_ENABLE_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define MICRF_ENABLE_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define MICRF_ENABLE_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define MICRF_ENABLE_SetPushPull()        do { ODCONCbits.ODC5 = 0; } while(0)
#define MICRF_ENABLE_SetOpenDrain()       do { ODCONCbits.ODC5 = 1; } while(0)

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
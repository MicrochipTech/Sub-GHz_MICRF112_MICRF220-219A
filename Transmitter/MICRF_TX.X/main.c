/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision    :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.75
        Device              :  PIC16F1619
        MCC Driver Version  :  v3.66
*/

/*
    (c) 2019 Microchip Technology Inc. and its subsidiaries. 
    
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

#include "mcc_generated_files/mcc.h"
#include "transmitter.h"

static uint32_t cnt_ = 0;

/*
                         Main application
 */
void main(void)
{
    SYSTEM_Initialize();                            // Initialize the device
    TX_init();                                      // Initialize the transmitter module
    TX_setSerialNumber((serialNum_t)0x1234);        // Set the system serial number
    INTERRUPT_GlobalInterruptEnable();              // Enable the Global Interrupts
    INTERRUPT_PeripheralInterruptEnable();          // Enable the Peripheral Interrupts
    CPU_ACTIVE_SetDigitalOutput();                  // Used to toggle an output pin that indicates CPU being active
    while (1)                                       // Main Loop
    {
        cnt_++;                                     // Increment the transmit counter - Data displayed on receiver
        (void)TX_sendData(&cnt_, sizeof(cnt_));     // Transmit the data (non-blocking call)
        while(!TX_isIdle())                         // While not idle, wait.
        { 
            SLEEP();                                // Sleep between transmitting bits to save power
            CPU_ACTIVE_Toggle();                    // Diags, to see when the processor is awake.
        }
        CPU_ACTIVE_Toggle();                        // Used just for diags
        SLEEP();                                    // WDT is set for 2 seconds.  So, sleep for 2 seconds.
        CPU_ACTIVE_Toggle();                        // Used just for diags
    }
}

/**
 End of File
*/
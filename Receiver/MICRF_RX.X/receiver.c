// <editor-fold defaultstate="collapsed" desc="File Header">
/***********************************************************************************************************************
 *
 * Filename:   receiver.c
 *
 * Global Designator: RX_
 *
 * Contents: Receives data from the MICRF220_219A driver module.
 * 
 ***********************************************************************************************************************
 * © 2019 Microchip Technology Inc. and its subsidiaries.  You may use this software and any derivatives exclusively
 * with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS
 * SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR
 * PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE,
 * COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF
 * THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON
 * ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID
 * DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 * 
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE TERMS. 
 ***********************************************************************************************************************
 *
 * $Log$ Karl Davlin <karl.davlin@microchip.com> Created March 13, 2017, 3:46 PM
 *
 * Last Update: 
 *  2/1/2019 - Updated to use XC8 v2.05, MPLAB X v5.10
 *
 * 
 **********************************************************************************************************************/
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Include Files">
/* ****************************************************************************************************************** */
/* INCLUDE FILES */

#include "receiver.h"
#include "dvr_micrf220_219a.h"
#include <string.h>
#include "dvr_crc.h"

#include "mcc_generated_files/mcc.h"

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Macro Definitions">
/* ****************************************************************************************************************** */
/* MACRO DEFINITIONS */

#define PROTOCOL            ((uint8_t)1)

/* This is used due to the way the PIC10/12/16/18 creates call-graphs for RAM memory.  The 8-Bit PICs do not fair well
 * with reentrant code.  So, care must be taken to ensure libraries are not called at interrupt level and non-interrupt
 * level functions. */
#define PIC_8_BIT           1 /* Set to 1 if using an 8-bit PIC, Set to 0 if using something else (PIC24, PIC32, SAM */

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Type Definitions">
/* ****************************************************************************************************************** */
/* TYPE DEFINITIONS */

typedef struct
{
    unsigned    protocolVer: 4;    // Version of the protocol being sent
    unsigned    cnt:         4;    // Number of data bytes being sent
    serialNum_t serialNum;         // Serial number of the transmitter
    uint8_t     data[15];          // Data to be sent
    uint16_t    crc;               // CRC
}rxPacket_t;                       // Received packet format

typedef struct
{
    rxPacket_t packet;
    int8_t     msgRssi;
    int8_t     noiseRssi;
}rxData_t;

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Local Function Prototypes">
/* ****************************************************************************************************************** */
/* FUNCTION PROTOTYPES */

void RX_messageReceived( uint8_t *pData, uint8_t cnt );

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Constant Definitions">
/* ****************************************************************************************************************** */
/* CONSTANTS */

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="File Variables - Static">
/* ****************************************************************************************************************** */
/* FILE VARIABLE DEFINITIONS */

static          rxData_t   rxData_;
static volatile rxPacket_t rxPacketBuffer_;
static volatile bool       bDataReady_;     // Set true when data is ready

#if RX_ENG_DATA_ON == 1
static volatile engData_t  engData_;
#endif

// </editor-fold>

/* ****************************************************************************************************************** */
/* FUNCTION DEFINITIONS */

// <editor-fold defaultstate="collapsed" desc="void RX_init( void )">
/***********************************************************************************************************************
 *
 * Function Name: RX_init
 *
 * Purpose: initializes this module and the driver module (dvr_micrf220_219A).
 *
 * Arguments: None
 *
 * Returns: N/A
 *
 * Side Effects: The receive driver will start running consuming CPU time (interrupt driven)
 *
 * Reentrant Code: No
 *
 **********************************************************************************************************************/
void RX_init( void )
{
    MICRF_init();                                   // Initialize the driver
    MICRF_rxEnable(true);                           // Enable the driver
    MICRF_setMessageCallback(RX_messageReceived);   // Set the call back function when a possible message is captured.
    
#if RX_ENG_DATA_ON == 1    
    (void)memset((void *)&engData_, 0, sizeof(engData_));   // Clear the receiver buffer
#endif
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="bool RX_process( rxDataPacket_t *pRxDataPacket )">
/***********************************************************************************************************************
 *
 * Function Name: RX_process
 *
 * Purpose: Validates the incoming message and if it is value, returns true.
 *
 * Arguments: rxDataPacket_t *pRxDataPacket
 *
 * Returns: bool - true a message has been received, false - no message has been received.
 *
 * Side Effects: N/A
 *
 * Reentrant Code: No
 *
 **********************************************************************************************************************/
bool RX_process( rxDataPacket_t *pRxDataPacket )
{
    bool bRetVal = false;
    
    if (bDataReady_)    // Is data ready?
    {
        (void)memcpy((void *)&rxData_.packet, (void *)&rxPacketBuffer_, sizeof(rxData_.packet)); // Cpy buf to data pckt
        bDataReady_ = false;
        (void)memcpy(&rxData_.packet.crc, &rxData_.packet.data[rxData_.packet.cnt], sizeof(rxData_.packet.crc));
        if (rxData_.packet.crc == 
            DVR_CRC_calc( &rxData_.packet, 1 + sizeof(rxData_.packet.serialNum) + rxData_.packet.cnt))
        {
            if (PROTOCOL == rxData_.packet.protocolVer)
            {
                /* Note:  The customer may wish to check the serial number.  For the demo, SN is just ignored. */
                
                pRxDataPacket->cnt = rxData_.packet.cnt;
                pRxDataPacket->msgRssi = rxData_.msgRssi;
                pRxDataPacket->noiseRssi = rxData_.noiseRssi;
                (void)memcpy(&pRxDataPacket->serialNum, &rxData_.packet.serialNum, sizeof(pRxDataPacket->serialNum));
                (void)memcpy(&pRxDataPacket->data[0], &rxData_.packet.data[0], rxData_.packet.cnt);
                bRetVal = true;
#if RX_ENG_DATA_ON == 1                
                engData_.validPackets++;
#endif
            }
#if RX_ENG_DATA_ON == 1            
            else
            {
                engData_.protocolFailures++;
            }
#endif            
        }
#if RX_ENG_DATA_ON == 1        
        else
        {
            engData_.crcFailures++;
        }
#endif
    }
    return(bRetVal);
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="void RX_enable( void )">
/***********************************************************************************************************************
 *
 * Function Name: RX_enable
 *
 * Purpose: Enables the driver
 *
 * Arguments: None
 *
 * Returns: None
 *
 * Side Effects: The timer for the radio RX detection will be enabled, CPU time will be consumed.
 *
 * Reentrant Code: Yes
 *
 **********************************************************************************************************************/
void RX_enable( void )
{
    MICRF_rxEnable(true);
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="void RX_disable( void )">
/***********************************************************************************************************************
 *
 * Function Name: RX_disable
 *
 * Purpose: Disables the driver
 *
 * Arguments: None
 *
 * Returns: None
 *
 * Side Effects: The timer for the radio RX detection will be disabled
 *
 * Reentrant Code: Yes
 *
 **********************************************************************************************************************/
void RX_disable( void )
{
    MICRF_rxEnable(false);
}
/* ****************************************************************************************************************** */
// </editor-fold>

#if RX_ENG_DATA_ON == 1

// <editor-fold defaultstate="collapsed" desc="void RX_getEngData( engData_t *pEngData )">
/***********************************************************************************************************************
 *
 * Function Name: RX_getEngData
 *
 * Purpose: Retrieves the engineering data.
 *
 * Arguments: engData_t *pEngData
 *
 * Returns: None
 *
 * Side Effects: The timer for the radio RX detection will be disabled
 *
 * Reentrant Code: Yes
 *
 **********************************************************************************************************************/
void RX_getEngData( engData_t *pEngData )
{
    (void)memcpy(pEngData, (void *)&engData_, sizeof(engData_));
}
/* ****************************************************************************************************************** */
// </editor-fold>

#endif

/* ****************************************************************************************************************** */
/* Local Functions */

/* ****************************************************************************************************************** */
/* Event Handlers */

// <editor-fold defaultstate="collapsed" desc="void RX_messageReceived( uint8_t *pData, uint8_t cnt )">
/***********************************************************************************************************************
 *
 * Function Name: RX_messageReceived
 *
 * Purpose: This function will be called at interrupt level.  This function needs to be kept to minimum CPU cycles.  If
 *          the buffer is empty and the count is valid, copy the data to the primary buffer.  This allows another
 *          message to be processed in the event the application hasn't processed the last message.
 *
 * Arguments: uint8_t *pData, uint8_t cnt
 *
 * Returns: N/A
 *
 * Side Effects: N/A
 *
 * Reentrant Code: No
 *
 **********************************************************************************************************************/
void RX_messageReceived( uint8_t *pData, uint8_t cnt )
{
    if (!bDataReady_)    // Don't collect unless the data in the buffer has already been copied.
    {
        if (cnt <= sizeof(rxPacketBuffer_)) // Is the count valid (will the source data fit in the buffer)?
        {
#if PIC_8_BIT == 1
            /* If using an 8-bit PIC micro, use a for-loop to copy the data over.  Using memcpy creates reentrant code
             * which the 8-bit PICs have an issue with (call graph). */
            uint8_t *pRxPacketBuffer = (uint8_t *)&rxPacketBuffer_;
            
            while(cnt--)
            {
                *pRxPacketBuffer++ = *pData++; // Copy the source data to the buffer
            }
#else            
            (void)memcpy(&rxPacketBuffer_, pData, cnt);     // Copy the source data to the buffer
#endif
            
#if MICRF_ENABLE_RSSI == 1            
            rxData_.msgRssi = MICRF_getRssiLastReceived();  // Get the RSSI of the message
            rxData_.noiseRssi = MICRF_getRssiNoiseFloor();  // Get the RSSI of the NoiseFloor
#endif
            bDataReady_ = true;                             // Set the flag that indicates we have a msg to process.
        }
#if RX_ENG_DATA_ON == 1        
        else
        {
            engData_.cntFailure++;  // Increment - the count was incorrect
        }
#endif        
    }
#if RX_ENG_DATA_ON == 1    
    else
    {
        engData_.bufferOverflow++; // Increment - the Buffer wasn't processed in a timely manner.
    }
#endif
}
/* ****************************************************************************************************************** */
// </editor-fold>

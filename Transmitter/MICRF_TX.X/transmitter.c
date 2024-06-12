// <editor-fold defaultstate="collapsed" desc="File Header">
/***********************************************************************************************************************
 *
 * Filename:   transmitter.c
 *
 * Global Designator: TX_
 *
 * Contents: Places the data in a packet to send to the driver module.
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
 * $Log$ Karl Davlin <karl.davlin@microchip.com> Created March 13, 2017, 11:42 AM
 *
 * Last Update:
 *
 * 2-01-2019 - Updated for XC2.05 and MPLAB X v5.10 with the latest MCC (see main.c file for details)
 * 
 **********************************************************************************************************************/
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Include Files">
/* ****************************************************************************************************************** */
/* INCLUDE FILES */

#include "transmitter.h"
#include "dvr_micrf112.h"
#include <string.h>
#include "mcc_generated_files/mcc.h"
#include "dvr_crc.h"

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Macro Definitions">
/* ****************************************************************************************************************** */
/* MACRO DEFINITIONS */

#define TX_PROTOCOLVER  ((uint8_t)1)

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Type Definitions">
/* ****************************************************************************************************************** */
/* TYPE DEFINITIONS */

typedef struct
{
    unsigned    protocolVer: 4; // Version of the protocol being sent
    unsigned    cnt:         4; // Number of data bytes being sent
    serialNum_t serialNum;      // Serial number of the transmitter
    uint8_t     data[15];       // Data to be sent
    uint16_t    crc;            // CRC
}txPacket_t;                    // Packet of information to be sent to the receiver.  Notice the structure is "packed".

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Constant Definitions">
/* ****************************************************************************************************************** */
/* CONSTANTS */

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="File Variables - Static">
/* ****************************************************************************************************************** */
/* FILE VARIABLE DEFINITIONS */

static volatile txPacket_t packet_;  /* Contains the packet data that will be transmitted. */

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Local Function Prototypes">
/* ****************************************************************************************************************** */
/* FUNCTION PROTOTYPES */

// </editor-fold>

/* ****************************************************************************************************************** */
/* FUNCTION DEFINITIONS */

// <editor-fold defaultstate="collapsed" desc="void TX_init( void )">
/***********************************************************************************************************************
 *
 * Function Name: TX_init
 *
 * Purpose: Initializes the transmitter module
 *
 * Arguments: None
 *
 * Returns: None
 *
 * Side Effects: Initializes the module and initializes the driver.
 *
 * Reentrant Code: No
 * 
 * Note:  The Serial number will not be lost if the module is re-initialized.
 *
 **********************************************************************************************************************/
void TX_init(void)
{
    uint16_t sn;    /* Temp variable to hold the serial number.  Re-initializing the module will not lose the sn. */
    
    sn = packet_.serialNum;
    (void)memset((void *)&packet_, 0, sizeof(packet_));     // Clear the data
    packet_.serialNum = sn;                         // Restore the SN
    MICRF_init();                                   // Initialize the driver
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="void TX_setSerialNumber(serialNum_t sn)">
/***********************************************************************************************************************
 *
 * Function Name: TX_setSerialNumber
 *
 * Purpose: Sets the serial number that will be transmitted with every packet of data
 *
 * Arguments: serialNum_t sn
 *
 * Returns: None
 *
 * Side Effects: Serial number is set
 *
 * Reentrant Code: No
 *
 **********************************************************************************************************************/
void TX_setSerialNumber(serialNum_t sn)
{
    // memcpy is used so that it doesn't matter how the typedef serialNum_t is defined.  It could be an array.
    (void)memcpy((void *)&packet_.serialNum, &sn, sizeof(packet_.serialNum));
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="bool TX_sendData(void *pData, uint8_t cnt)">
/***********************************************************************************************************************
 *
 * Function Name: TX_sendData
 *
 * Purpose: Builds a packet of data to send.  The *pData contains the data that will be sent.
 *
 * Arguments: void *pData, uint8_t cnt
 *
 * Returns: bool - true = Success, false = Failure
 *
 * Side Effects: Hardware CRC is invoked.
 *
 * Reentrant Code: No
 *
 **********************************************************************************************************************/
bool TX_sendData(void *pData, uint8_t cnt)
{
    bool bRetVal = false;   // Assume the data cannot be sent
    
    if (sizeof(packet_.data) >= cnt)    // Validate the number of bytes meets the minimum payload
    {
        if (MICRF_isTxIdle())           // Only the previous transmission is complete can the next transmission be started.
        {
            (void)memcpy((void *)&packet_.data[0], pData, cnt);                     // Copy the data 
            packet_.protocolVer = TX_PROTOCOLVER;                                   // Set the protocol version
            packet_.cnt = cnt;                                                      // Set the count
            // Calculate and set the CRC (generates a compiler warning, but has be verified to be okay.)
            packet_.crc = DVR_CRC_calc(&packet_, (uint8_t)(sizeof(packet_) - sizeof(packet_.crc) - 
                                       sizeof(packet_.data) + cnt));
            (void)memcpy((void *)&packet_.data[cnt], (void *)&packet_.crc, sizeof(packet_.crc)); // Move CRC to end of data.
            MICRF_transmit(&packet_, (sizeof(packet_) - sizeof(packet_.data)) + cnt); // Transmit the data
            bRetVal = true;
        }
    }
    return(bRetVal);
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="bool TX_isIdle(void)">
/***********************************************************************************************************************
 *
 * Function Name: TX_isIdle
 *
 * Purpose: Returns status of the driver
 *
 * Arguments: None
 *
 * Returns: bool - true = done transmitting or is idle, false = busy
 *
 * Side Effects: None
 *
 * Reentrant Code: Yes
 *
 **********************************************************************************************************************/
bool TX_isIdle(void)
{
    return(MICRF_isTxIdle());
}
/* ****************************************************************************************************************** */
// </editor-fold>

/* ****************************************************************************************************************** */
/* Local Functions */

/* ****************************************************************************************************************** */
/* Event Handlers */

/* ****************************************************************************************************************** */
/* Unit Test Code */

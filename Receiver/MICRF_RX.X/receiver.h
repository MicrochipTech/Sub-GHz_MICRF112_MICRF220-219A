/* ****************************************************************************************************************** */
/***********************************************************************************************************************
 *
 * Filename: receiver.h
 *
 * Contents: APIs for the receiver module.
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
 **********************************************************************************************************************/
#ifndef RECEIVER_H
#define RECEIVER_H

/* ****************************************************************************************************************** */
/* INCLUDE FILES */

#include <stdint.h>
#include <stdbool.h>

/* ****************************************************************************************************************** */
/* GLOBAL DEFINTION */

/* ****************************************************************************************************************** */
/* MACRO DEFINITIONS */

#define RX_ENG_DATA_ON      1

/* ****************************************************************************************************************** */
/* TYPE DEFINITIONS */

/* The demo uses at 16-bit serial number.  The customer may wish to have a 24-bit, 32-bit or some other size for the 
 * serial number.  So, this typedef will allow the customer to easily change the size to something for their product. */
typedef uint16_t serialNum_t;   // Used to easily define the serial number length

typedef struct
{
    uint16_t serialNum;         // Serial number of the transmitter
    uint8_t  cnt;               // Number of data bytes being sent
    uint8_t  data[15];          // Data to be sent
    int8_t   msgRssi;           // RSSI of the last message sent
    int8_t   noiseRssi;         // Noise floor 
}rxDataPacket_t;                // Received packet format

#if RX_ENG_DATA_ON == 1
typedef struct
{
    uint32_t  validPackets;
    uint32_t  crcFailures;
    uint32_t  protocolFailures;
    uint32_t  bufferOverflow;
    uint32_t  cntFailure;
}engData_t;
#endif

/* ****************************************************************************************************************** */
/* CONSTANTS */

/* ****************************************************************************************************************** */
/* GLOBAL VARIABLES */

/* ****************************************************************************************************************** */
/* FUNCTION PROTOTYPES */

/**
 * RX_init - Initializes the module and it's variables.
 *
 * @see:  N/A
 *
 * @param  None
 * 
 * @return None
 */
void RX_init( void );

/**
 * RX_process - Validates the incoming message and if it is value, returns true.
 *
 * @see:  N/A
 *
 * @param  rxDataPacket_t *pRxDataPacket - Pointer to the location to save the received data
 * 
 * @return bool - true a message has been received, false - no message has been received.
 */
bool RX_process( rxDataPacket_t *pRxDataPacket );

/**
 * RX_enable - Enables the receiver and timer
 *
 * @see:  N/A
 *
 * @param  None
 * 
 * @return None
 */
void RX_enable( void );

/**
 * RX_disable - Disables the receiver and timer
 *
 * @see:  N/A
 *
 * @param  None
 * 
 * @return None
 */
void RX_disable( void );

/**
 * RX_getEngData - Gets the engineering data from the last received message
 *
 * @see:  N/A
 *
 * @param  engData_t *pEngData - Location to store the engineering data
 * 
 * @return None
 */
void RX_getEngData( engData_t *pEngData );

#endif  /* RECEIVER_H */

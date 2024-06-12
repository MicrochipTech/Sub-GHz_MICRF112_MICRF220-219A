/* ****************************************************************************************************************** */
/***********************************************************************************************************************
 *
 * Filename: transmitter.h
 *
 * Contents: APIs for the transmitter module.
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
 **********************************************************************************************************************/
#ifndef TRANSMITTER_H
#define TRANSMITTER_H

/* ****************************************************************************************************************** */
/* INCLUDE FILES */

#include <stdint.h>
#include <stdbool.h>

/* ****************************************************************************************************************** */
/* GLOBAL DEFINTION */

/* ****************************************************************************************************************** */
/* MACRO DEFINITIONS */

/* ****************************************************************************************************************** */
/* TYPE DEFINITIONS */

/* The demo uses at 16-bit serial number.  The customer may wish to have a 24-bit, 32-bit or some other size for the 
 * serial number.  So, this typedef will allow the customer to easily change the size to something for their product. */
typedef uint16_t serialNum_t;   // Used to easily define the serial number length

/* ****************************************************************************************************************** */
/* CONSTANTS */

/* ****************************************************************************************************************** */
/* GLOBAL VARIABLES */

/* ****************************************************************************************************************** */
/* FUNCTION PROTOTYPES */

/**
 * TX_init - Initializes the transmitter module
 *
 * @see:  N/A
 *
 * @param  None
 * 
 * @return None
 */
void TX_init(void);

/**
 * TX_setSerialNumber - Sets the serial number that will be transmitted with every packet of data
 *
 * @see:  N/A
 *
 * @param  serialNum_t sn - Serial Number of the device
 * 
 * @return None
 */
void TX_setSerialNumber(serialNum_t sn);

/**
 * TX_sendData - Builds a packet of data to send.  The *pData contains the data that will be sent.
 *
 * @see:  N/A
 *
 * @param  void *pData - Pointer to data to be sent
 * @param  uint8_t cnt - Number of bytes to send (number of bytes in pData)
 * 
 * @return bool - true = Success, false = Failure
 */
bool TX_sendData(void *pData, uint8_t cnt);

/**
 * TX_isIdle - Returns status of the driver
 *
 * @see:  N/A
 *
 * @param  None
 * 
 * @return bool - true = idle, false = busy sending data
 */
bool TX_isIdle(void);

#endif  /* TRANSMITTER_H */

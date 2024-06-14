/* ****************************************************************************************************************** */
/***********************************************************************************************************************
 *
 * Filename: dvr_micrf112.h
 *
 * Contents: APIs for the MICRF112 driver module..
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
 * $Log$ Karl Davlin <karl.davlin@microchip.com> Created March 13, 2017, 10:59 AM
 *
 **********************************************************************************************************************/
#ifndef DVR_MICRF112_H
#define DVR_MICRF112_H

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

typedef enum
{
    eMICRF_success,     // Data sent
    eMICRF_failure,     // Failure
    eMICRF_dataLength   // Failed due to data length error
}eMICRF_response_t;

/* ****************************************************************************************************************** */
/* CONSTANTS */

/* ****************************************************************************************************************** */
/* GLOBAL VARIABLES */

/* ****************************************************************************************************************** */
/* FUNCTION PROTOTYPES */

/**
 * MICRF_init - Initializes the transmitter module
 *
 * @see:  N/A
 *
 * @param  None
 * 
 * @return None
 */
void MICRF_init(void);

/**
 * MICRF_transmit - Transmits a packet of data.  The count is checked to make sure it is within range.
 *
 * @see:  N/A
 *
 * @param  void *pData - Pointer to data packet to send
 * @param  uint8_t cnt - Number of bytes to send
 * 
 * @return eMICRF_response_t - Status
 */
eMICRF_response_t MICRF_transmit(volatile void *pData, uint8_t cnt);

/**
 * MICRF_isTxIdle - Returns true if the TX is complete or false if not complete
 *
 * @see:  N/A
 *
 * @param  None
 * 
 * @return bool - false = Busy, true = Idle
 */
bool MICRF_isTxIdle( void );


#endif  /* MICRF112_H */

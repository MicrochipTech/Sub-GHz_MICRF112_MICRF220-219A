/* ****************************************************************************************************************** */
/***********************************************************************************************************************
 *
 * Filename: dvr_micrf220_219a.h
 *
 * Contents: APIs for the MICRF_219A driver.
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
#ifndef DVR_MICRF_219A_H
#define DVR_MICRF220_219A_H

/* ****************************************************************************************************************** */
/* INCLUDE FILES */

#include <stdint.h>
#include <stdbool.h>

/* ****************************************************************************************************************** */
/* GLOBAL DEFINTION */

/* ****************************************************************************************************************** */
/* MACRO DEFINITIONS */

#define MICRF_ENABLE_RSSI   1   /* Set to 1 if RSSI is to be used. */

/* ****************************************************************************************************************** */
/* TYPE DEFINITIONS */

/* ****************************************************************************************************************** */
/* CONSTANTS */

/* ****************************************************************************************************************** */
/* GLOBAL VARIABLES */

/* ****************************************************************************************************************** */
/* FUNCTION PROTOTYPES */

/**
 * MICRF_init - Initializes the module and it's variables.
 *
 * @see:  N/A
 *
 * @param  None
 * 
 * @return None
 */
void   MICRF_init( void );

/**
 * MICRF_setMessageCallback - Once a valid message has been received, messageHandler is be called.
 *
 * @see:  N/A
 *
 * @param  void* messageHandler - Function to call on complete message
 * 
 * @return None
 */
void   MICRF_setMessageCallback( void (* messageHandler)( uint8_t *pData, uint8_t cnt ) );

/**
 * MICRF_rxEnable - Enables or Disables the Receiver
 *
 * @see:  N/A
 *
 * @param  bool bEnable - true = enable, false = disable
 * 
 * @return None
 */
void   MICRF_rxEnable( bool bEnable );

#if MICRF_ENABLE_RSSI == 1
/**
 * MICRF_getRssiNoiseFloor - Reads the latest noise floor value.
 *
 * @see:  N/A
 *
 * @param  None
 * 
 * @return int8_t - dBm
 */
int8_t MICRF_getRssiNoiseFloor( void );

/**
 * MICRF_getRssiLastReceived - Returns the RSSI of the last message
 *
 * @see:  N/A
 *
 * @param  None
 * 
 * @return int8_t - dBm
 */
int8_t MICRF_getRssiLastReceived( void );

/**
 * MICRF_getReceivingMsgDataStatus - Returns true if receiving data, false if looking for data.
 *
 * @see:  N/A
 *
 * @param  None
 * 
 * @return bool - Returns true if receiving data, false if looking for data.
 */
bool   MICRF_getReceivingMsgDataStatus( void );

/**
 * MICRF_setAdcValue - This function should be called with the latest ADC reading every 4 bits worth of data.  For 
 *                     example, if the bit rate is 2KHz, then this function should be called 2KHz / 4 = 500Hz or 2mS.  
 *                     The module will store the calculated data in an array to perform a running average.
 *
 * @see:  N/A
 *
 * @param  uint16_t adcVolts_mV - ADC reading of the RSSI analog input pin converted to mV.
 * 
 * @return None
 */
void   MICRF_setAdcValue( uint16_t adcVolts_mV );

#endif

#endif  /* MICRF220_219A_H */

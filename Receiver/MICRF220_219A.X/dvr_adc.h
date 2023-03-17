/* ****************************************************************************************************************** */
/***********************************************************************************************************************
 *
 * Filename: dvr_adc.h
 *
 * Contents: ToDo
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
 * $Log$ Karl Davlin <karl.davlin@microchip.com> Created April 22, 2017, 6:58 AM
 *
 **********************************************************************************************************************/
#ifndef DVR_ADC_H
#define DVR_ADC_H

/* ****************************************************************************************************************** */
/* INCLUDE FILES */

#include <stdint.h>

/* ****************************************************************************************************************** */
/* GLOBAL DEFINTION */

/* ****************************************************************************************************************** */
/* MACRO DEFINITIONS */

/* ****************************************************************************************************************** */
/* TYPE DEFINITIONS */

/* ****************************************************************************************************************** */
/* CONSTANTS */

/* ****************************************************************************************************************** */
/* GLOBAL VARIABLES */

/* ****************************************************************************************************************** */
/* FUNCTION PROTOTYPES */

void DVR_ADC_init( void );
void DVR_ADC_enable( void );
void DVR_ADC_disable( void );
void DVR_ADC_setCallback( void (* fpCallbackFunction)( uint16_t adcVolts_mV ) );
void DVR_ADC_processConversion( void );
void DVR_ADC_isr( void );

#endif  /* DVR_ADC_H */

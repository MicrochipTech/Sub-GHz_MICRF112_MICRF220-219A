// <editor-fold defaultstate="collapsed" desc="File Header">
/***********************************************************************************************************************
 *
 * Filename:   dvr_adc.c
 *
 * Global Designator: ToDo
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
 * Notes:  This ADC driver is simply an example of what a customer may use.  The ADC is NOT the intent of the demo.
 *         This module is created simply to convert the ADC reading from raw ADC counts to mV and send the data to the
 *         receiver module.  How the customer does this may vary.
 * 
 ***********************************************************************************************************************
 * 
 * $Log$ Karl Davlin <karl.davlin@microchip.com> Created April 22, 2017, 6:58 AM
 *
 * Last Update:
 *    2/1/2019 - Updated to use XC8 v2.05, MPLAB X v5.10
 * 
 **********************************************************************************************************************/
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Include Files">
/* ****************************************************************************************************************** */
/* INCLUDE FILES */

#include "dvr_adc.h"
#include <stdbool.h>
#include "mcc_generated_files/mcc.h"

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Macro Definitions">
/* ****************************************************************************************************************** */
/* MACRO DEFINITIONS */

/* The macros below are used to convert the ADC reading to millivolts.  In customer's projects, this may be done in
 * another module.  The function MICRF_setAdcValue() requires the data passed in to be in millivolts. */
#define ADC_MAX_nV              ((uint32_t)3300000000)
#define ADC_nV_PER_CNT          ((uint32_t)ADC_MAX_nV/65536)

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Type Definitions">
/* ****************************************************************************************************************** */
/* TYPE DEFINITIONS */

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Constant Definitions">
/* ****************************************************************************************************************** */
/* CONSTANTS */

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="File Variables - Static">
/* ****************************************************************************************************************** */
/* FILE VARIABLE DEFINITIONS */

static bool     bProcessAdcResult_ = false;
static uint16_t adcValue_;
static void (*fpAdcCallBack_)(uint16_t);

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Local Function Prototypes">
/* ****************************************************************************************************************** */
/* FUNCTION PROTOTYPES */

static uint16_t adcValTo_mV( uint16_t adcVal );

// </editor-fold>

/* ****************************************************************************************************************** */
/* FUNCTION DEFINITIONS */

// <editor-fold defaultstate="collapsed" desc="void DVR_ADC_init( void )">
/***********************************************************************************************************************
 *
 * Function Name: DVR_ADC_init
 *
 * Purpose: Initialize the ADC driver module
 *
 * Arguments: None
 *
 * Returns: N/A
 *
 * Side Effects: ADC will be running
 *
 * Reentrant Code: No
 *
 **********************************************************************************************************************/
void DVR_ADC_init( void )
{
    ADCC_StartConversion(AN_CH_RSSI);
    DVR_ADC_enable();
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="void DVR_ADC_enable( void )">
/***********************************************************************************************************************
 *
 * Function Name: DVR_ADC_enable
 *
 * Purpose: Enables the ADC converter for the demo
 *
 * Arguments: None
 *
 * Returns: N/A
 *
 * Side Effects: The ADC will be running!
 *
 * Reentrant Code: No
 *
 **********************************************************************************************************************/
void DVR_ADC_enable( void )
{
    ADCC_StartConversion(AN_CH_RSSI);
    TMR6_StartTimer();
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="void DVR_ADC_disable( void )">
/***********************************************************************************************************************
 *
 * Function Name: DVR_ADC_disable
 *
 * Purpose: Disables the ADC converter
 *
 * Arguments: None
 *
 * Returns: N/A
 *
 * Side Effects: The ADC will no longer be running
 *
 * Reentrant Code: No
 *
 **********************************************************************************************************************/
void DVR_ADC_disable( void )
{
    TMR6_StopTimer();
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="void DVR_ADC_setCallback( void (* fpCallbackFunction)( uint16_t adcVolts_mV ) )">
/***********************************************************************************************************************
 *
 * Function Name: DVR_ADC_setCallback
 *
 * Purpose: Sets a call-back function when the data has been processed.
 *
 * Arguments: void (* fpCallbackFunction)( uint16_t adcVolts_mV )
 *
 * Returns: None
 *
 * Side Effects: None
 *
 * Reentrant Code: No
 * 
 * Notes:  Call back at non-interrupt level!
 *
 **********************************************************************************************************************/
void DVR_ADC_setCallback( void (* fpCallbackFunction)( uint16_t adcVolts_mV ) )
{
    fpAdcCallBack_ = fpCallbackFunction;
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="void DVR_ADC_processConversion( void )">
/***********************************************************************************************************************
 *
 * Function Name: DVR_ADC_processConversion
 *
 * Purpose: Processes the ADC results and calls the callback function.
 *
 * Arguments: None
 *
 * Returns: None
 *
 * Side Effects: None
 *
 * Reentrant Code: No
 *
 **********************************************************************************************************************/
void DVR_ADC_processConversion( void )
{
    if (bProcessAdcResult_)
    {
        bProcessAdcResult_ = false;
        uint16_t mV = adcValTo_mV( adcValue_ );
        fpAdcCallBack_(mV);
    }
}
/* ****************************************************************************************************************** */
// </editor-fold>

/* ****************************************************************************************************************** */
/* LOCAL FUNCTIONS */

// <editor-fold defaultstate="collapsed" desc="static uint16_t adcValTo_mV( uint16_t adcVal )">
/***********************************************************************************************************************
 *
 * Function Name: adcValTo_mV
 *
 * Purpose: Converts Raw ADC counts to mV
 *
 * Arguments: uint16_t adcVal - Raw ADC value to convert
 *
 * Returns: uint16_t - mV
 *
 * Side Effects: None
 *
 * Reentrant Code: Yes
 *
 **********************************************************************************************************************/
static uint16_t adcValTo_mV( uint16_t adcVal )
{
    uint16_t mV = (uint16_t)((ADC_nV_PER_CNT * adcVal) / (uint32_t)1000000);    // Convert the ADC value to mV
    return(mV);
}
/* ****************************************************************************************************************** */
// </editor-fold>

/* ****************************************************************************************************************** */
/* EVENT/ISR HANDLERS */

// <editor-fold defaultstate="collapsed" desc="void DVR_ADC_isr( void )">
/***********************************************************************************************************************
 *
 * Function Name: DVR_ADC_isr
 *
 * Purpose: Must be called at a rate of 1/2 to 1/4 the data rate.
 *
 * Arguments: None
 *
 * Returns: None
 *
 * Side Effects: N/A
 *
 * Reentrant Code: No
 * 
 * Notes:  This function is called from the ADC module.  In the customer's application, the function may need to be
 *         removed and MICRF_setAdcValue() called from the customer's ADC module.
 *
 **********************************************************************************************************************/
void DVR_ADC_isr( void )
{
    bProcessAdcResult_ = true;
    adcValue_ = ADCC_GetConversionResult();
}
/* ****************************************************************************************************************** */
// </editor-fold>

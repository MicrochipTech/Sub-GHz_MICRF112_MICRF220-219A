// <editor-fold defaultstate="collapsed" desc="File Header">
/***********************************************************************************************************************
 *
 * Filename:   dvr_micrf220_219a.c
 *
 * Global Designator: MICRF_
 *
 * Contents: Driver for MICRF220_219A receiver.  Contains all of the APIs and ISR code for the timer interrupt.
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
 * $Log$ Karl Davlin <karl.davlin@microchip.com> Created March 13, 2017, 3:45 PM
 *
 * Last Update:
 *  4-10-2017 - KD - Added more comments.
 *  2-01-2019 - KD - Updated to use XC8 v2.05, MPLAB X v5.10
 ***********************************************************************************************************************
 * 
 * Connections to MICRF112 Demo Board using a Curiosity Board.  The Curiosity is using the PIC16F1619.
 * 
 * MICRF220_219A Pin out:
 *   J3-1: Vdd (3V)
 *   J3-2: GND
 *   J3-3: Data Output
 *   J3-4: SCLK
 *   J3-5: Shut Down
 *   J4-6: RSSI
 * 
 * Explorer Board Connections to MICRF220_219A - Plug the MICRF220_219A directly into J17 pins 1, 3, 5, 7, 9, 11.  Make sure Pin
 *                                          1 on the MICRF220_219A is connected to J17-11.  The MICRF220_219A will be face down.
 *                                          The Expl. Board will need a jumper on J16 to +3.3V, (pins 2 and 3).
 *    Exp Board      MICRF220_219A
 *   J17-11: Vdd    J3-1 - Vdd
 *   J17-9:  GND    J3-2 - GND
 *   J17-7:  RC6    J3-3 - Data Output
 *   J17-5:  RC7    J3-4 - SCLK
 *   J17-3:  RC1    J3-5 - Shut Down
 *   J17-1:  RC0    J3-6 - RSSI
 * 
 ***********************************************************************************************************************
 * Demo Board Notes:
 * 
 * Note on bit rate:  The default demo board is has Vsel1 = 0V and Vsel0 = 3V.  This means the "best" data rate is
 *                    between 3-4Kbits (see datasheet, page 5, lower left).  Remove 0 ohm resistor by JP1 which sets
 *                    Vsel1 and vsel0 = 3V and the best data should be between 10-20Kbit (see datasheet, page 6, upper
 *                    left).
 *                  
 ***********************************************************************************************************************
 * 
 * NOTE:  The datasheet used is Revision 2.0, August 19, 2015.
 * 
 **********************************************************************************************************************/
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Include Files">
/* ****************************************************************************************************************** */
/* INCLUDE FILES */

#include "dvr_micrf220_219a.h"
#include <string.h>
#include "mcc_generated_files/mcc.h"
#include "manchester.h"

#if MICRF_ENABLE_RSSI == 1              /* MICRF_ENABLE_RSSI is defined in the dvr_micrf220_219a.h file.  */
#include "dvr_adc.h"
#endif

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Macro Definitions">
/* ****************************************************************************************************************** */
/* MACRO DEFINITIONS */

/* The macro below is used with the Sample Timer to set the bit rate.  */
#define RX_SAMPLES_PER_BIT      ((uint8_t)10)           /* Sample rate based on the timer call-back. */
#define RX_DATA_ARRAY_SIZE      ((uint8_t)50)           /* Largest amount of decoded manchester data allowed */
#define RX_MINIMUM_PACKET_SIZE  ((uint8_t)3)            /* Minimum number of bytes to be considered a message */
#define PREAMBLE                ((uint16_t)0xAA3A)      /* Contains the last byte of training and the preamble. */

/* This is custom per project.  The values below work for the demo.  This timer value along with RX_SAMPLES_PER_BIT is 
 * used to set the bit rate. */
#define SAMPLE_TIMER_ISR_SET()  TMR4_SetInterruptHandler(MICRF_sampleTimerISR)  /* Sets the call-back function */
#define SAMPLE_TIMER_START()    TMR4_StartTimer()                               /* Used to start the timer */
#define SAMPLE_TIMER_STOP()     TMR4_StopTimer()                                /* Used to stop the timer */

/* RSSI information is NOT needed for data reception.  The RSSI can be useful when troubleshooting or diags. */
/* MICRF_ENABLE_RSSI is defined in the dvr_micrf220_219a.h file.  */
#if MICRF_ENABLE_RSSI == 1                              /* If disabled, don't enable the RSSI calculation functions */

#define ADC_SET_CALLBACK()      DVR_ADC_setCallback(MICRF_setAdcValue);
#define ADC_RUN()               DVR_ADC_enable()
#define ADC_STOP()              DVR_ADC_disable()        

#ifndef ARRAYIDXCNT             /* used to get the number of indecies in an array */
#define ARRAYIDXCNT(x)          (sizeof(x)/sizeof(x[0]))
#endif

/* This data is taken directly from the MICRF220_219A datasheet, page 4.  These macros are for converting the ADC mV value
 * to dBm.  The output to dBm is fairly accurate, but it doesn't follow the curve on the datasheet exactly.  It will
 * give the user a fairly good idea of dBm.  */
#define RSSI_MIN_mV             ((int16_t)500)              /* 0.5 Volts at -110dBm */
#define RSSI_MIN_dBm            ((int8_t)-110)
#define RSSI_MAX_mV             ((int16_t)2000)             /* 2.0 Volts at -50dBm */
#define RSSI_MAX_dBm            ((int8_t)-50)
#define RSSI_RANGE_mV           ((int16_t)(RSSI_MAX_mV - RSSI_MIN_mV))
#define RSSI_dBm_RANGE_100x     ((int16_t)(((int16_t)RSSI_MAX_dBm - RSSI_MIN_dBm)) * 100)
#define dBm_PER_VOLT_100x       ((int8_t)(RSSI_dBm_RANGE_100x / RSSI_RANGE_mV))
#define RSSI_mV_TO_dBm(x)       ((int8_t)(RSSI_MIN_dBm + (((x - RSSI_MIN_mV) * dBm_PER_VOLT_100x) / 100)))

#define RSSI_AVE_CNT            ((uint8_t)16)               /* Running average indecies, number of samples. */
#define RSSI_NF_CNT             ((uint8_t)10)               /* Number of ADC samples before logging RSSI sample. */
#define RSSI_NF_CNT_AFTER_DATA  ((uint8_t)250)              /* Number of ADC samples before logging RSSI sample. */

#endif

/* These pin values were defined and named used MCC. */
#define RX_DATA_PIN             RF_DATA_IN_PORT             /* The pin data is received on */
#define RX_DATA_PIN_CFG()       RF_DATA_IN_SetDigitalInput() /* Controls the data direction, sets pin to an input */

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Type Definitions">
/* ****************************************************************************************************************** */
/* TYPE DEFINITIONS */

#if MICRF_ENABLE_RSSI == 1                  /* MICRF_ENABLE_RSSI is defined in the dvr_micrf220_219a.h file.  */
typedef struct
{
    uint32_t arraySum;                      // Sum of all of array_mV.
    uint16_t array_mV[RSSI_AVE_CNT];        // Contains an array of the RSSI in mV
    int16_t  rssiAve_mV;                    // Contains the running average of the RSSI array.
    uint8_t  arrayIdx;                      // Contains the index to store the next sample in array_mV
    uint8_t  noiseFloorCnt;                 // Only take noise floor readings every xxx times.
}rssi_t;                                    // Contains all of the RSSI data
#endif

typedef struct
{
    uint16_t    manchesterWord;             // Current byte being received, 2 Manchester bytes = 1 decoded byte
    uint8_t     logicHighCnt;               // Used for voting if the sampling of a single bit is high or low
    uint8_t     sliceCnt;                   // Keeps track of the number of samples taken
    uint8_t     bitCnt;                     // Keeps track of the number of bits received
    uint8_t     data[RX_DATA_ARRAY_SIZE];   // Stores the decoded data
    uint8_t     dataIdx;                    // Index/count of the number of bytes received
    uint8_t     sliceInputStateFirst;       // Value of the 1st sample taken of the data bit
    bool        bCollectData;               // Indicates if data is being collected
    bool        bSkipSlice;                 // Indication to skip a sample, used to adjust the timing for sync
    bool        bLogMsgRssi;                // Is the ADC value detecting noise or a message
}rxData_t;                                  // Contains all data for collecting a message

typedef struct
{
#if MICRF_ENABLE_RSSI == 1                      /* MICRF_ENABLE_RSSI is defined in the dvr_micrf220_219a.h file.  */
    rssi_t      rssiNoiseFloor;                 /* Contains all of the RSSI values */
    rssi_t      rssiMessage;                    /* Contains all of the RSSI values */
#endif
    rxData_t    rxData;                         /* Contains all of received data information */
    void (*pRxFunctionPtr)(uint8_t *, uint8_t); /* Function that gets called when a message is received */
    bool        bRxEnabled;                     /* Enable or disable the RX module */
}rxVars_t;

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Local Function Prototypes">
/* ****************************************************************************************************************** */
/* FUNCTION PROTOTYPES */

void MICRF_sampleTimerISR( void );  // Technically, this is a global function, but only accessed by the interrupt.

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Constant Definitions">
/* ****************************************************************************************************************** */
/* CONSTANTS */

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="File Variables - Static">
/* ****************************************************************************************************************** */
/* FILE VARIABLE DEFINITIONS */

static volatile rxVars_t rxVars_;   // Contains all of the local data this module uses.

// </editor-fold>

/* ****************************************************************************************************************** */
/* FUNCTION DEFINITIONS */

// <editor-fold defaultstate="collapsed" desc="void MICRF_init( void )">
/***********************************************************************************************************************
 *
 * Function Name: MICRF_init
 *
 * Purpose: Initializes the module and it's variables.
 *
 * Arguments: None
 *
 * Returns: None
 *
 * Side Effects: Configures the RX data pin as an input.  Clears the rxVars.
 *
 * Reentrant Code: No
 *
 **********************************************************************************************************************/
void MICRF_init( void )
{
    RX_DATA_PIN_CFG();                                  // Configure the RX data pin as an input
    (void)memset((void *)&rxVars_, 0, sizeof(rxVars_)); // Clear all of the variables
    rxVars_.pRxFunctionPtr = NULL;                      // Set the function point to NULL
}
/* ****************************************************************************************************************** */
// </editor-fold>

#if MICRF_ENABLE_RSSI == 1  /* MICRF_ENABLE_RSSI is defined in the dvr_micrf220_219a.h file.  */

// <editor-fold defaultstate="collapsed" desc="int8_t MICRF_getRssiNoiseFloor( void )">
/***********************************************************************************************************************
 *
 * Function Name: MICRF_getRssiNoiseFloor
 *
 * Purpose: Reads the latest noise floor value.
 *
 * Arguments: None
 *
 * Returns: int8_t - dBm
 *
 * Side Effects: None
 *
 * Reentrant Code:
 *
 **********************************************************************************************************************/
int8_t MICRF_getRssiNoiseFloor( void )
{
    int8_t myVal = RSSI_mV_TO_dBm(rxVars_.rssiNoiseFloor.rssiAve_mV);
    return(myVal);
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="int8_t MICRF_getRssiLastReceived( void )">
/***********************************************************************************************************************
 *
 * Function Name: MICRF_getRssiLastReceived
 *
 * Purpose: Reads the last successful received data's RSSI
 *
 * Arguments: None
 *
 * Returns: int8_t - dBm
 *
 * Side Effects: None
 *
 * Reentrant Code:
 *
 **********************************************************************************************************************/
int8_t MICRF_getRssiLastReceived( void )
{
    return(RSSI_mV_TO_dBm(rxVars_.rssiMessage.rssiAve_mV));
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="bool MICRF_getReceivingMsgDataStatus( void )">
/***********************************************************************************************************************
 *
 * Function Name: MICRF_getReceivingMsgDataStatus
 *
 * Purpose: Returns true if receiving data, false if looking for data.
 *
 * Arguments: None
 *
 * Returns: bool - Returns true if receiving data, false if looking for data.
 *
 * Side Effects: No
 *
 * Reentrant Code: Yes
 *
 **********************************************************************************************************************/
bool MICRF_getReceivingMsgDataStatus( void )
{
    return(rxVars_.rxData.bCollectData);
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="void MICRF_setAdcValue( uint16_t adcVolts_mV )">
/***********************************************************************************************************************
 *
 * Function Name: MICRF_setAdcValue
 *
 * Purpose: This function should be called with the latest ADC reading every 4 bits worth of data.  For example, if the
 *          bit rate is 2KHz, then this function should be called 2KHz / 4 = 500Hz or 2mS.  The module will store the 
 *          calculated data in an array to perform a running average.
 *
 * Arguments: uint16_t adcVolts_mV - This function is expecting the voltage * 1000.  For example 1.234V would be 1234mV
 *
 * Returns: None
 *
 * Side Effects: Adds the ADC mV value to the array.
 *
 * Reentrant Code: No
 *
 * Notes:  For the demo, the ADC is triggered by the timer.  The ADC ISR is located in this module.  For the customer,
 *         the ADC may be other conversions.  So, it is up to the customer to configure their ADC, convert the ADC value
 *         to mV and call this function.
 * 
 **********************************************************************************************************************/
void MICRF_setAdcValue( uint16_t adcVolts_mV )
{
    if (rxVars_.rxData.bLogMsgRssi && rxVars_.rxData.bCollectData)  // Is the RSSI value for the Data Message?
    {   // Check bounds on the index before doing anything!
        if (rxVars_.rssiMessage.arrayIdx >= ARRAYIDXCNT(rxVars_.rssiMessage.array_mV))  
        { 
            rxVars_.rssiMessage.arrayIdx = 0;
        }
        // Compute the RSSI average
        rxVars_.rssiMessage.arraySum = (rxVars_.rssiMessage.arraySum + adcVolts_mV) - 
                                       rxVars_.rssiMessage.array_mV[rxVars_.rssiMessage.arrayIdx];
        rxVars_.rssiMessage.array_mV[rxVars_.rssiMessage.arrayIdx] = adcVolts_mV;
        rxVars_.rssiMessage.rssiAve_mV = rxVars_.rssiMessage.arraySum / ARRAYIDXCNT(rxVars_.rssiMessage.array_mV);
        rxVars_.rssiMessage.arrayIdx++;
        // Add a delay after collecting data to allow the RSSI on the MICRF220_219A to settle.
        rxVars_.rssiNoiseFloor.noiseFloorCnt = RSSI_NF_CNT_AFTER_DATA;  
    }
    else if (!rxVars_.rxData.bCollectData)  // If not collecting data, collect noise floor data
    {
        if (0 == rxVars_.rssiNoiseFloor.noiseFloorCnt--)    // slow down the noise floor collection by using this cntr.
        {
            rxVars_.rssiNoiseFloor.noiseFloorCnt = RSSI_NF_CNT; // Reset the counter value.
            // Check bounds on the index before doing anything!
            if (rxVars_.rssiNoiseFloor.arrayIdx >= ARRAYIDXCNT(rxVars_.rssiNoiseFloor.array_mV))  
            {   // Reset the index!
                rxVars_.rssiNoiseFloor.arrayIdx = 0;
            }
            // Compute the RSSI average
            rxVars_.rssiNoiseFloor.arraySum = (rxVars_.rssiNoiseFloor.arraySum + adcVolts_mV) - 
                                              rxVars_.rssiNoiseFloor.array_mV[rxVars_.rssiNoiseFloor.arrayIdx];
            rxVars_.rssiNoiseFloor.array_mV[rxVars_.rssiNoiseFloor.arrayIdx] = adcVolts_mV;
            rxVars_.rssiNoiseFloor.rssiAve_mV = rxVars_.rssiNoiseFloor.arraySum / 
                                                ARRAYIDXCNT(rxVars_.rssiNoiseFloor.array_mV);
            rxVars_.rssiNoiseFloor.arrayIdx++;
        }
    }
}
/* ****************************************************************************************************************** */
// </editor-fold>

#endif

// <editor-fold defaultstate="collapsed" desc="void MICRF_setMessageCallback(void (* messageHandler)(uint8_t *pData, uint8_t cnt))">
/***********************************************************************************************************************
 *
 * Function Name: MICRF_setMessageCallback
 *
 * Purpose: Once a valid message has been received, the function pointed to by mssageHandler will be called.
 *
 * Arguments: void (* messageHandler)( uint8_t *pData, uint8_t cnt )
 *
 * Returns: None
 *
 * Side Effects: Every time a preamble is detected and at least one byte is received, the callback function will be
 *               called.  The callback function MUST be small as it is called from interrupt level!
 *
 * Reentrant Code: No
 *
 **********************************************************************************************************************/
void MICRF_setMessageCallback( void (* messageHandler)( uint8_t *pData, uint8_t cnt ) )
{
    rxVars_.pRxFunctionPtr = messageHandler;
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="void MICRF_rxEnable( bool bEnable )">
/***********************************************************************************************************************
 *
 * Function Name: MICRF_rxEnable
 *
 * Purpose: Enables or Disables the Receiver
 *
 * Arguments: bool bEnable
 *
 * Returns: None
 *
 * Side Effects: The timer interrupts are enabled and CPU time will be consumed.  If RSSI enabled, the ADC interrupt
 *               will be enabled too.
 *
 * Reentrant Code: No
 *
 **********************************************************************************************************************/
void MICRF_rxEnable( bool bEnable )
{
    if (bEnable)
    {
        rxVars_.bRxEnabled = true;  // Set the flag that indicates the module is enabled
        MICRF_init();               // Initialize the module
        SAMPLE_TIMER_ISR_SET();     // Set the ISR callback 
        SAMPLE_TIMER_START();       // Start the timer for sampling
#if MICRF_ENABLE_RSSI == 1          /* MICRF_ENABLE_RSSI is defined in the dvr_micrf220_219a.h file.  */
        ADC_SET_CALLBACK();         // Set the ADC callback
        ADC_RUN();                  // Start the ADC running!
#endif
    }
    else
    {
        SAMPLE_TIMER_STOP();        // Stop the sample timer
#if MICRF_ENABLE_RSSI == 1        
        ADC_STOP();                 // Stop the ADC for the RSSI
#endif
        rxVars_.bRxEnabled = false; // We're no longer running
    }
}
/* ****************************************************************************************************************** */
// </editor-fold>

/* ****************************************************************************************************************** */
/* Local Functions */

/* ****************************************************************************************************************** */
/* Event Handlers */

// <editor-fold defaultstate="collapsed" desc="void MICRF_sampleTimerISR( void )">
/***********************************************************************************************************************
 *
 * Function Name: MICRF_sampleTimerISR
 *
 * Purpose: Must be called at a rate of x times the data rate, see RX_SAMPLES_PER_BIT macro.  The number of samples per
 *          bit has been tested between 4 and 20 times.  The value must be an even number.
 *
 * Arguments: None
 *
 * Returns: N/A
 *
 * Side Effects: The callback function will be called if a possible message has been received.
 *
 * Reentrant Code: No
 * 
 * Note:  This driver does not decode the message in any way.  Therefore, the customer can implement any protocol they 
 *        wish without modifying this code.
 *
 **********************************************************************************************************************/
void MICRF_sampleTimerISR( void )
{
    uint8_t sliceInputState = RX_DATA_PIN;      // Get the sample from the RX input pin immediately!  Do this first!
    bool    bOnBitBoundary = false;             // Assume the slice for the bit is not complete.
    
    if (!rxVars_.rxData.bSkipSlice)             // Skip a slice last time the bit boundary was ahead of the slicer.
    {
        rxVars_.rxData.logicHighCnt += sliceInputState; // logicHighCnt will be used to "vote" if bit was high or low.
        if (0 == rxVars_.rxData.sliceCnt)               // Is this the first slice?
        {   // Store the 1st slice state.
            rxVars_.rxData.sliceInputStateFirst = sliceInputState;  // Used to compute if timing needs to be adjusted.
        }
        rxVars_.rxData.sliceCnt++;
        if (rxVars_.rxData.sliceCnt >= RX_SAMPLES_PER_BIT)  // Check if this is the last slice for the bit
        { // The last slice (sample) has been taken.  Now, process the results!
            rxVars_.rxData.sliceCnt = 0;        // Reset the sliceCnt
            rxVars_.rxData.manchesterWord <<= 1;// Left shift the Manchester word.
            if (rxVars_.rxData.logicHighCnt >= (RX_SAMPLES_PER_BIT / 2))    // Voting, is the bit high or low?
            {   // The bit is high
                rxVars_.rxData.manchesterWord |= 1; // High bit, set the LSB to high (1).
                // Is the sampling centered around a bit.  For example, if there are 10 samples per bit, we want all 10
                // samples to read the bit and NOT read a part of one bit and a part of another.  Noise and signal
                // strength can affect the bit timing.  So, if only the first slice was not a 1 and the last slick was
                // a one, assume we a little too slow.  So, grab the next sample now.  This will effectively speed up
                // the slicer by one time slice (or sample).
                if ((0 == sliceInputState) && (0 != rxVars_.rxData.sliceInputStateFirst))
                {   // Vote was high, however, last bit was 0.  So, assume this sample is a part of the next bit.
                    rxVars_.rxData.logicHighCnt += sliceInputState;
                    rxVars_.rxData.sliceCnt++;
                    rxVars_.rxData.sliceInputStateFirst = sliceInputState;
                }
                else if ((0 == rxVars_.rxData.sliceInputStateFirst) && (0 != sliceInputState))
                {
                    // if only the first slice was a 1 and the last slick was a 0, assume we a little too quick.  So,
                    // skip the next sample.  This will effectively slow down the slicer by 1 slice time (or sample).
                    rxVars_.rxData.bSkipSlice = true;
                }
            }
            else
            {
                if ((1 == sliceInputState) && (1 != rxVars_.rxData.sliceInputStateFirst)) // See notes for the 1 bit.
                {
                    rxVars_.rxData.logicHighCnt += sliceInputState;
                    rxVars_.rxData.sliceCnt++;
                    rxVars_.rxData.sliceInputStateFirst = sliceInputState;
                }
                else if ((1 == rxVars_.rxData.sliceInputStateFirst) && (1 != sliceInputState))
                {
                    rxVars_.rxData.bSkipSlice = true;
                }
            }
            bOnBitBoundary = true;                  // We're on a bit boundary (or close).  Set the sliceDone.
            rxVars_.rxData.logicHighCnt = 0;        // Reset the voting variable.
        }

        /* If we're on a bit boundary AND the preamble matches the received word, then indicate we're going to start
         * processing data.  Even though we're processing data, we're always going to look for another valid preamble.
         * Since the preamble contains invalid Manchester data, we can re-start collecting data. */
        if (bOnBitBoundary && (PREAMBLE == rxVars_.rxData.manchesterWord))
        {
            rxVars_.rxData.bCollectData = true;     // Indicate we're now collecting data
            rxVars_.rxData.dataIdx = 0;             // Start collecting data at the 1st index.
            rxVars_.rxData.bitCnt = 0;              // Reset the bit counter, we're now sync'd
        }
        else if (bOnBitBoundary && rxVars_.rxData.bCollectData) // On a bit boundary and we're collecting data?
        {
            bool    bSendMsg = false;   // Assume we don't have enough data to send the message
            
            // If the Manchester coding is violated, don't bother doing anything else, just try to send the data.
            if (0 != rxVars_.rxData.dataIdx)    // Until the 1st byte has been received, don't check.  
            {   // Just get the 3 ls bits in the lsb variable.
                uint8_t lsb = (uint8_t)((uint8_t)rxVars_.rxData.manchesterWord & 7);
                
                if ((7 == lsb) || (0 == lsb))   // Are the LSBs 000 or 111, these are not valid a Manchester bits.
                {  // Now, we're going to try to send the message.  There is no need to try to decode the next bytes.
                    bSendMsg = true;    
                }
            }
            if (!bSendMsg)  // Need to process the incoming bits/bytes of data.
            {
                rxVars_.rxData.bitCnt++;            // We're going to process the next bit
                if (rxVars_.rxData.bitCnt >= 16)    // Have we collected 16-bits (a word)?
                {   // Yes, process the 16-bits of data
                    rxVars_.rxData.bitCnt = 0;      // Reset bit count.  Prepare to collect the next 16-bits.
                    // Swap the bytes (convert the endianess)
                    rxVars_.rxData.manchesterWord = (rxVars_.rxData.manchesterWord >> 8) | 
                                                    (rxVars_.rxData.manchesterWord << 8);
                    // Try to decode the Manchester data.  Convert 16-bits back to 8-bits.
                    if (ME_decode((void *)&rxVars_.rxData.data[rxVars_.rxData.dataIdx], 
                                   (void *)&rxVars_.rxData.manchesterWord,
                                   sizeof(rxVars_.rxData.manchesterWord)))
                    {  // Decoded properly
                        rxVars_.rxData.bLogMsgRssi = true;  // Collecting data, log RSSI (all RSSI samples are for msg.)
                        rxVars_.rxData.dataIdx++;           // Point the next buffer entry
                        if (rxVars_.rxData.dataIdx >= sizeof(rxVars_.rxData.data))  // At the end of the buffer?
                        {  // No more data will fit, try to send what we have.
                            bSendMsg = true;
                        }
                    }
                    else
                    {   // Manchester decoding failed.  So, assume we collected all available data.  Try to send it.
                        bSendMsg = true;
                    }
                }
            }
            if (bSendMsg) // Time to send message?
            {  // Lets pass the message to the receiver module to validate and decode
                rxVars_.rxData.bCollectData = false;    // No longer collecting data.  
                rxVars_.rxData.bLogMsgRssi = false;     // The new RSSI values are now for measuring the noise floor.
                // Is the function pointer valid AND the enough data was collected?
                if ((NULL != rxVars_.pRxFunctionPtr) && (rxVars_.rxData.dataIdx >= RX_MINIMUM_PACKET_SIZE))
                {  // All looks good, call the function.
                    rxVars_.pRxFunctionPtr((void *)&rxVars_.rxData.data[0], rxVars_.rxData.dataIdx);
                }
          }
        }
    }
    else    // if (!rxVars_.rxData.bSkipSlice)
    {
        rxVars_.rxData.bSkipSlice = false;  // Stop skipping slices!
    }
}
/* ****************************************************************************************************************** */
// </editor-fold>

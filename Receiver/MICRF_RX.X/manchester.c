// <editor-fold defaultstate="collapsed" desc="File Header">
/***********************************************************************************************************************
 *
 * Filename:   manchester.c
 *
 * Global Designator: ME_
 *
 * Contents: Performs Manchester encoding/decoding
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
 * $Log$ Karl Davlin <karl.davlin@microchip.com> Created March 14, 2017, 1:23 PM
 *
 * Last Update: 3/21/2017
 *
 * 
 **********************************************************************************************************************/
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Include Files">
/* ****************************************************************************************************************** */
/* INCLUDE FILES */

#include "manchester.h"

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Macro Definitions">
/* ****************************************************************************************************************** */
/* MACRO DEFINITIONS */

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Type Definitions">
/* ****************************************************************************************************************** */
/* TYPE DEFINITIONS */

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Local Function Prototypes">
/* ****************************************************************************************************************** */
/* FUNCTION PROTOTYPES */

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Constant Definitions">
/* ****************************************************************************************************************** */
/* CONSTANTS */

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="File Variables - Static">
/* ****************************************************************************************************************** */
/* FILE VARIABLE DEFINITIONS */

// </editor-fold>

/* ****************************************************************************************************************** */
/* FUNCTION DEFINITIONS */

// <editor-fold defaultstate="collapsed" desc="void ME_encode(void *pDst, void *pSrc, uint8_t cnt)">
/***********************************************************************************************************************
 *
 * Function Name: ME_encode
 *
 * Purpose: Encode a string of data
 *
 * Arguments: void *pDst, void *pSrc, uint8_t cnt
 *
 * Returns: N/A
 *
 * Side Effects: None
 *
 * Reentrant Code: Yes
 *
 **********************************************************************************************************************/
void ME_encode(void *pDst, void *pSrc, uint8_t cnt)
{
    uint8_t i = 0;
    uint16_t encodedBytes;
    uint8_t data;
    uint8_t *pSrcData = (uint8_t *)pSrc;
    uint8_t *pDstData = (uint8_t *)pDst;
    
    while (0 != cnt--)
    {
        for (i = 0, encodedBytes = 0, data = *pSrcData++; i < 8; i++, data <<= 1)
        { 
            encodedBytes <<= 2;
            if (data & 0x80)
            {
                encodedBytes |= 1;  // 1: low going to a high
            }
            else
            {
                encodedBytes |= 2;  // 0: high going to a low
            }
        }
        *pDstData++ = (uint8_t)encodedBytes;
        *pDstData++ = (uint8_t)(encodedBytes >> 8);
    }
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="bool ME_decode(void *pDst, void *pSrc, uint8_t cnt)">
/***********************************************************************************************************************
 *
 * Function Name: ME_decode
 *
 * Purpose: Encode a string of data
 *
 * Arguments: void *pDst, void *pSrc, uint8_t cnt
 *
 * Returns: bool - true = success, false = failure
 *
 * Side Effects: N/A
 *
 * Reentrant Code: Yes
 *
 **********************************************************************************************************************/
bool ME_decode(void *pDst, void *pSrc, uint8_t cnt)
{
    bool retVal = false;
    
    if (0 == (cnt % 2))
    {
        retVal = true;
        uint8_t i = 0;
        uint8_t encodedByte;
        uint8_t data = 0;
        uint8_t *pDstData = (uint8_t *)pDst;
        uint8_t *pSrcData = (uint8_t *)pSrc;

        while (retVal && (0 != cnt--))
        {
            for (i = 0, encodedByte = *pSrcData++; i < 4; i++, encodedByte >>= 2)
            { 
                data >>= 1;
                switch(encodedByte & 0x03)
                {
                    case 1:
                    {
                        data |= 0x80;
                        break;
                    }
                    case 2:
                    {
                        break;
                    }
                    default:
                    {
                        retVal = false;
                        break;
                    }
                }
            }
            if (0 == (cnt % 2))
            {
                *pDstData++ = data;
                data = 0;
                
            }
        }
    }
    return(retVal);
}
/* ****************************************************************************************************************** */
// </editor-fold>

/* ****************************************************************************************************************** */
/* Local Functions */

/* ****************************************************************************************************************** */
/* Event Handlers */

/* ****************************************************************************************************************** */
/* Unit Test Code */



/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - v3.00
        Device            :  PIC12LF1571
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20
*/

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

#define ORIGINAL_SENSOR

#include "mcc_generated_files/mcc.h"
#include "main.h"

// Serial number at program memory address 0x3FD define
const unsigned char serial[3] @ 0x3FD = {0x0F, 0x67, 0x32};

#define DOOR_BIT    0x80
#define TAMPER_BIT  0x40
#define BATTERY_BIT 0x08
//------------------------------------------------------------------------------------------------------------------
// Door and tamper switch customization:

#define DOOR_PIN    4       // Define the pin number of PORTA that is connected to the door switch
#define TAMPER_PIN  2       // Define the pin number of PORTA that is connected to the tamper switch

//#define INVERT_DOOR_SWITCH            // Uncomment this to invert the polarity of the door switch
//#define INVERT_TAMPER_SWITCH          // Uncomment this to invert the polarity of the door switch

// End of door and tamper switch customization
//------------------------------------------------------------------------------------------------------------------

// Define one or the other of the following to select the desired door sensor polarity (Not both!)
#define DOOR_CHECK  (PORTA & (1 << DOOR_PIN))
//#define DOOR_CHECK  (!(PORTA & 2))

// Define one or the other of the following to select the desired door sensor polarity (Not both!)
#define TAMPER_CHECK  (PORTA & (1 << TAMPER_PIN))
//#define DOOR_CHECK  (!(PORTA & 4))

#define SEND_LENGTH 16

#define INVERT_DOOR_SWITCH
#define INVERT_TAMPER_SWITCH

#ifdef INVERT_DOOR_SWITCH
    #define INVERT_DOOR !
#else
    #define INVERT_DOOR
#endif
#ifdef INVERT_TAMPER_SWITCH
    #define INVERT_TAMPER !
#else
    #define INVERT_TAMPER
#endif

typedef unsigned char U8;
typedef unsigned int U16;

U8 packet_t[8] = {
  0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

U8 encman[SEND_LENGTH];

void manchester_enc(U8 * inbuf, U8 *outbuf, U8 len)
{
    U8 i, k;
    U8 outbuf_idx = 0;
    U8 hbyte, lbyte;
    U8 tbyte;
    
    for (k = 0; k < len; k++)
    {
        hbyte = 0x00;
        lbyte = 0x00;
        tbyte = *(inbuf + k);

        for (i = 0; i < 4; i++)
        {
            if (tbyte & 0x80)
            {
                hbyte |= 0x01;
            }
            else
            {
                hbyte |= 0x02;
            }
            
            if (i < 3)
                hbyte = (hbyte << 2);

            if (tbyte & 0x08)
            {
                lbyte |= 0x01;
            }
            else
            {
                lbyte |= 0x02;
            }
            if (i < 3)
                lbyte = (lbyte << 2);
            
            tbyte = (tbyte << 1);
        }
        
        *(outbuf + outbuf_idx) = hbyte;
        *(outbuf + outbuf_idx + 1) = lbyte;
        outbuf_idx += 2;
    }
}

void crc12(U8 * inbuf, U8 *outbuf, U8 len)
{
    U16 crc = 0;
    U16 inbuf_t;
    U8 i, k;
    
    for (i = 0; i < len; i++)
    {
        inbuf_t = *(inbuf +i);
        crc ^= inbuf_t << 4;
        
        for (k = 0; k < 8; k++)
        {
            if (crc & 0x800)
            {
                crc = crc << 1;
                crc = (crc ^ 0x805) & 0xFFF;
            }
            else
            {
                crc = (crc << 1) & 0xFFF;
            }
        }
    }
    
    crc = (crc << 4);
    *outbuf = (U8)(crc >> 8);
    *(outbuf + 1) = (U8)crc;
}

void delay_us(U8 delay)
{
    U8 i, k;
    
    for (i = 0; i < delay; i++)
        for (k = 0; k < 1; k++)
        {
            NOP();
        }
}

void sendSignal(U8 * pt)
{
    U8 i, k, n;
    U8 wbyte;
    U8 old_state = 0;
    
    for (n = 0; n < 6; n++) {
        delay_us(250);
        RF_ENABLE;
        delay_us(20);
        // Add your application code
        for (i = 0; i < SEND_LENGTH ; i++) {
            wbyte = *(pt + i);

            for (k = 0; k < 8; k++) {
                if (wbyte & 0x80) {
                    RF_OUT_1;
                    delay_us(13);
                    if (old_state) delay_us(10);
                    old_state = 1;
                } else {
                    RF_OUT_0;
                    if (!old_state) delay_us(22);
                    else delay_us(34);

                    old_state = 0;
                }
                wbyte = (wbyte << 1);
            }
        }
        delay_us(20);
        RF_DISABLE;
        for (i = 0; i < 15; i++) delay_us(250);
    }
}

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    TRISA |= (1 << DOOR_PIN) | (1 << TAMPER_PIN);
    WPUA |= (1 << DOOR_PIN) | (1 << TAMPER_PIN);
    
    /* Copy serial to template buffer */
    packet_t[2] = (serial[0] & 0x0F) | 0xA0;
    packet_t[3] = serial[1];
    packet_t[4] = serial[2];
    
    while (1) {
        
        packet_t[5] = 0x00;
    
        if ( INVERT_DOOR (PORTAbits.RA4)) {
            packet_t[5] |= DOOR_BIT;
        } 
        if (INVERT_TAMPER (PORTAbits.RA2)) {
            packet_t[5] |= TAMPER_BIT;
        } 

        crc12(&packet_t[2], &packet_t[6], 4);
        manchester_enc(&packet_t[0], &encman[0], 8);
        sendSignal(&encman[0]);
    }
}
/**
 End of File
*/
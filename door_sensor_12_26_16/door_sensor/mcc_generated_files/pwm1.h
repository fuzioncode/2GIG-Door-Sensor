/**
  PWM1 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    pwm1.h

  @Summary
    This is the generated header file for the PWM1 driver using MPLAB(c) Code Configurator

  @Description
    This header file provides APIs for driver for PWM1.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 3.16
        Device            :  PIC12LF1571
        Driver Version    :  1.0
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#ifndef _PWM1_H
#define _PWM1_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: PWM Module APIs
*/

/**
  @Summary
    Initializes the PWM1

  @Description
    This routine initializes the Initializes the PWM1.
    This routine must be called before any other PWM routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment
    

  @Example
    <code>
    
    </code>
*/
void PWM1_Initialize(void);

/**
  @Summary
    This function starts the PWM1.

  @Description
    This function starts the PWM1 operation.
    This function must be called after the initialization of PWM1.

  @Preconditions
    Initialize  the PWM1 before calling this function.

   @Param
    None

  @Returns
    None

  @Example
    <code>
    // Initialize PWM1 module

    // Start PWM1
    PWM1_Start();

    // Do something else...
    </code>
*/
void PWM1_Start(void);

/**
  @Summary
    This function stops the PWM1.

  @Description
    This function stops the PWM1 operation.
    This function must be called after the start of PWM1.

  @Preconditions
    Initialize  the PWM1 before calling this function.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    // Initialize PWM1 module

    // Start PWM1
    PWM1_StartTimer();

    // Do something else...

    // Stop PWM1;
    PWM1_Stop();
    </code>
*/
void PWM1_Stop(void);


/**
  @Summary
    This function used to check output status of PWM1.

  @Description
    Check output status of PWM1 as High or Low.    

  @Preconditions
    Start the PWM1 before calling this function.

  @Param
    None

  @Returns
    true - Output High.
	false - Output Low.

  @Example
    <code>
    
    </code>
*/
bool PWM1_CheckOutputStatus(void);

/**
  @Summary
    This function is used to load buffer of PWM1 at the end of period.

  @Description
    load buffer of PWM1 at the end of period.

  @Preconditions
     Initialize  the PWM1 before calling this function.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    
    </code>
*/
void PWM1_LoadBufferSet(void);

/**
  @Summary
    Load required 16 bit phase count

  @Description
    Set the expected phase count

  @Preconditions
    None

  @Param
    Pass 16 bit phase count

  @Returns
    None

  @Example
    <code>
    
    </code>
*/
void PWM1_PhaseSet(uint16_t phaseCount);

/**
  @Summary
    Load required 16 bit Duty Cycle

  @Description
    Set the expected Duty Cycle

  @Preconditions
    None

  @Param
    Pass 16 bit Duty Cycle

  @Returns
    None

  @Example
    <code>
    
    </code>
*/
void PWM1_DutyCycleSet(uint16_t dutyCycleCount);

/**
  @Summary
    Load required 16 bit Period

  @Description
    Set the expected Period

  @Preconditions
    None

  @Param
    Pass 16 bit Period

  @Returns
    None

  @Example
    <code>
    
    </code>
*/
void PWM1_PeriodSet(uint16_t periodCount);

/**
  @Summary
    Load required 16 bit Offset

  @Description
    Set the expected Offset

  @Preconditions
    None

  @Param
    Pass 16 bit Offset

  @Returns
    None

  @Example
    <code>
    
    </code>
*/
void PWM1_OffsetSet(uint16_t offsetCount);

/**
  @Summary
    Read measured Timer count

  @Description    
    Read the measured Timer count
 * 
  @Preconditions
    None

  @Param
    None

  @Returns
    Return 16 bit Timer count

  @Example
    <code>
    
    </code>
*/
uint16_t PWM1_TimerCountGet(void);

/**
  @Summary
    Returns status of Offset interrupt flag bit (OFIF ).

  @Description    
    When PWMTMR = PWMOF value offset flag sets.

  @Preconditions
    None

  @Param
    None

  @Returns
    true - PWMTMR >= PWMOF value
    false - PWMTMR < PWMOF value

  @Example
    <code>
    
    </code>
*/
bool PWM1_IsOffsetMatchOccured(void);

/**
  @Summary
    Returns status of Phase interrupt flag bit (PHIF ).

  @Description    
    When PWMTMR = PWMPH value, Phase flag sets.

  @Preconditions
    None

  @Param
    None

  @Returns
    true - PWMTMR count is >= PWMPH value
    false - PWMTMR count is < PWMPH value

  @Example
    <code>
    
    </code>
*/
bool PWM1_IsPhaseMatchOccured(void);

/**
  @Summary
    Returns status of DutyCycle interrupt flag bit (DCIF ).

  @Description    
    When PWMTMR = PWMDC value DutyCycle flag sets.

  @Preconditions
    None

  @Param
    None

  @Returns
    true - PWMTMR count is >= PWMDC value
    false - PWMTMR count is < PWMDC value

  @Example
    <code>
    
    </code>
*/
bool PWM1_IsDutyCycleMatchOccured(void);

/**
  @Summary
    Returns status of Period interrupt flag bit (PRIF ).

  @Description    
    When PWMTMR = PWMPR value offset flag sets.

  @Preconditions
    None

  @Param
    None

  @Returns
    true - PWMTMR count is >= PWMPR value
    false - PWMTMR count is < PWMPR value

  @Example
    <code>
    
    </code>
*/
bool PWM1_IsPeriodMatchOccured(void);

#endif	/* PWM1_H */
/**
 End of File
*/

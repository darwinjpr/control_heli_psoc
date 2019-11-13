/*******************************************************************************
* File Name: pot_manual.c  
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the Quadrature Decoder
*  component.
*
* Note:
*  None.
*   
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "pot_manual.h"

#if (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT)
    #include "pot_manual_PVT.h"
#endif /* pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT */

uint8 pot_manual_initVar = 0u;


/*******************************************************************************
* Function Name: pot_manual_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default QuadDec configuration provided with customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void pot_manual_Init(void) 
{
    #if (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT)
        /* Disable Interrupt. */
        CyIntDisable(pot_manual_ISR_NUMBER);
        /* Set the ISR to point to the pot_manual_isr Interrupt. */
        (void) CyIntSetVector(pot_manual_ISR_NUMBER, & pot_manual_ISR);
        /* Set the priority. */
        CyIntSetPriority(pot_manual_ISR_NUMBER, pot_manual_ISR_PRIORITY);
    #endif /* pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: pot_manual_Enable
********************************************************************************
*
* Summary:
*  This function enable interrupts from Component and also enable Component's
*  ISR in case of 32-bit counter.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void pot_manual_Enable(void) 
{
    uint8 enableInterrupts;

    pot_manual_SetInterruptMask(pot_manual_INIT_INT_MASK);

    /* Clear pending interrupts. */
    (void) pot_manual_GetEvents();
    
    enableInterrupts = CyEnterCriticalSection();

    /* Enable interrupts from Statusi register */
    pot_manual_SR_AUX_CONTROL |= pot_manual_INTERRUPTS_ENABLE;

    CyExitCriticalSection(enableInterrupts);        

    #if (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT)
        /* Enable Component interrupts */
        CyIntEnable(pot_manual_ISR_NUMBER);
    #endif /* pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: pot_manual_Start
********************************************************************************
*
* Summary:
*  Initializes UDBs and other relevant hardware.
*  Resets counter, enables or disables all relevant interrupts.
*  Starts monitoring the inputs and counting.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  pot_manual_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void pot_manual_Start(void) 
{
    #if (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_8_BIT)
        pot_manual_Cnt8_Start();
        pot_manual_Cnt8_WriteCounter(pot_manual_COUNTER_INIT_VALUE);
    #else
        /* (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_16_BIT) || 
        *  (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT) 
        */
        pot_manual_Cnt16_Start();
        pot_manual_Cnt16_WriteCounter(pot_manual_COUNTER_INIT_VALUE);
    #endif /* pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_8_BIT */
    
    #if (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT)        
       pot_manual_count32SoftPart = 0;
    #endif /* pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT */

    if (pot_manual_initVar == 0u)
    {
        pot_manual_Init();
        pot_manual_initVar = 1u;
    }

    pot_manual_Enable();
}


/*******************************************************************************
* Function Name: pot_manual_Stop
********************************************************************************
*
* Summary:
*  Turns off UDBs and other relevant hardware.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void pot_manual_Stop(void) 
{
    uint8 enableInterrupts;

    #if (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_8_BIT)
        pot_manual_Cnt8_Stop();
    #else 
        /* (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_16_BIT) ||
        *  (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT)
        */
        pot_manual_Cnt16_Stop();    /* counter disable */
    #endif /* (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_8_BIT) */
 
    enableInterrupts = CyEnterCriticalSection();

    /* Disable interrupts interrupts from Statusi register */
    pot_manual_SR_AUX_CONTROL &= (uint8) (~pot_manual_INTERRUPTS_ENABLE);

    CyExitCriticalSection(enableInterrupts);

    #if (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT)
        CyIntDisable(pot_manual_ISR_NUMBER);    /* interrupt disable */
    #endif /* pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: pot_manual_GetCounter
********************************************************************************
*
* Summary:
*  Reports the current value of the counter.
*
* Parameters:
*  None.
*
* Return:
*  The counter value. Return type is signed and per the counter size setting.
*  A positive value indicates clockwise movement (B before A).
*
* Global variables:
*  pot_manual_count32SoftPart - used to get hi 16 bit for current value
*  of the 32-bit counter, when Counter size equal 32-bit.
*
*******************************************************************************/
int16 pot_manual_GetCounter(void) 
{
    int16 count;
    uint16 tmpCnt;

    #if (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT)
        int16 hwCount;

        CyIntDisable(pot_manual_ISR_NUMBER);

        tmpCnt = pot_manual_Cnt16_ReadCounter();
        hwCount = (int16) ((int32) tmpCnt - (int32) pot_manual_COUNTER_INIT_VALUE);
        count = pot_manual_count32SoftPart + hwCount;

        CyIntEnable(pot_manual_ISR_NUMBER);
    #else 
        /* (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_8_BIT) || 
        *  (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_16_BIT)
        */
        #if (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_8_BIT)
            tmpCnt = pot_manual_Cnt8_ReadCounter();
        #else /* (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_16_BIT) */
            tmpCnt = pot_manual_Cnt16_ReadCounter();
        #endif  /* pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_8_BIT */

        count = (int16) ((int32) tmpCnt -
                (int32) pot_manual_COUNTER_INIT_VALUE);

    #endif /* pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT */ 

    return (count);
}


/*******************************************************************************
* Function Name: pot_manual_SetCounter
********************************************************************************
*
* Summary:
*  Sets the current value of the counter.
*
* Parameters:
*  value:  The new value. Parameter type is signed and per the counter size
*  setting.
*
* Return:
*  None.
*
* Global variables:
*  pot_manual_count32SoftPart - modified to set hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void pot_manual_SetCounter(int16 value) 
{
    #if ((pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_8_BIT) || \
         (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_16_BIT))
        uint16 count;
        
        if (value >= 0)
        {
            count = (uint16) value + pot_manual_COUNTER_INIT_VALUE;
        }
        else
        {
            count = pot_manual_COUNTER_INIT_VALUE - (uint16)(-value);
        }
        #if (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_8_BIT)
            pot_manual_Cnt8_WriteCounter(count);
        #else /* (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_16_BIT) */
            pot_manual_Cnt16_WriteCounter(count);
        #endif  /* pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_8_BIT */
    #else /* (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT) */
        CyIntDisable(pot_manual_ISR_NUMBER);

        pot_manual_Cnt16_WriteCounter(pot_manual_COUNTER_INIT_VALUE);
        pot_manual_count32SoftPart = value;

        CyIntEnable(pot_manual_ISR_NUMBER);
    #endif  /* (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_8_BIT) ||
             * (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_16_BIT)
             */
}


/*******************************************************************************
* Function Name: pot_manual_GetEvents
********************************************************************************
* 
* Summary:
*   Reports the current status of events. This function clears the bits of the 
*   status register.
*
* Parameters:
*  None.
*
* Return:
*  The events, as bits in an unsigned 8-bit value:
*    Bit      Description
*     0        Counter overflow.
*     1        Counter underflow.
*     2        Counter reset due to index, if index input is used.
*     3        Invalid A, B inputs state transition.
*
*******************************************************************************/
uint8 pot_manual_GetEvents(void) 
{
    return (pot_manual_STATUS_REG & pot_manual_INIT_INT_MASK);
}


/*******************************************************************************
* Function Name: pot_manual_SetInterruptMask
********************************************************************************
*
* Summary:
*  Enables / disables interrupts due to the events.
*  For the 32-bit counter, the overflow, underflow and reset interrupts cannot
*  be disabled, these bits are ignored.
*
* Parameters:
*  mask: Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*
* Return:
*  None.
*
*******************************************************************************/
void pot_manual_SetInterruptMask(uint8 mask) 
{
    #if (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT)
        /* Underflow, Overflow and Reset interrupts for 32-bit Counter are always enable */
        mask |= (pot_manual_COUNTER_OVERFLOW | pot_manual_COUNTER_UNDERFLOW |
                 pot_manual_COUNTER_RESET);
    #endif /* pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT */

    pot_manual_STATUS_MASK = mask;
}


/*******************************************************************************
* Function Name: pot_manual_GetInterruptMask
********************************************************************************
*
* Summary:
*  Reports the current interrupt mask settings.
*
* Parameters:
*  None.
*
* Return:
*  Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*  For the 32-bit counter, the overflow, underflow and reset enable bits are
*  always set.
*
*******************************************************************************/
uint8 pot_manual_GetInterruptMask(void) 
{
    return (pot_manual_STATUS_MASK & pot_manual_INIT_INT_MASK);
}


/* [] END OF FILE */

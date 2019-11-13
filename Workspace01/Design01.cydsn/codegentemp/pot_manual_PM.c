/*******************************************************************************
* File Name: pot_manual_PM.c
* Version 3.0
*
* Description:
*  This file contains the setup, control and status commands to support 
*  component operations in low power mode.  
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

static pot_manual_BACKUP_STRUCT pot_manual_backup = {0u};


/*******************************************************************************
* Function Name: pot_manual_SaveConfig
********************************************************************************
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void pot_manual_SaveConfig(void) 
{
    #if (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_8_BIT)
        pot_manual_Cnt8_SaveConfig();
    #else 
        /* (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_16_BIT) || 
         * (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT)
         */
        pot_manual_Cnt16_SaveConfig();
    #endif /* (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: pot_manual_RestoreConfig
********************************************************************************
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void pot_manual_RestoreConfig(void) 
{
    #if (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_8_BIT)
        pot_manual_Cnt8_RestoreConfig();
    #else 
        /* (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_16_BIT) || 
         * (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT) 
         */
        pot_manual_Cnt16_RestoreConfig();
    #endif /* (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: pot_manual_Sleep
********************************************************************************
* 
* Summary:
*  Prepare Quadrature Decoder Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  pot_manual_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void pot_manual_Sleep(void) 
{
    if (0u != (pot_manual_SR_AUX_CONTROL & pot_manual_INTERRUPTS_ENABLE))
    {
        pot_manual_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        pot_manual_backup.enableState = 0u;
    }

    pot_manual_Stop();
    pot_manual_SaveConfig();
}


/*******************************************************************************
* Function Name: pot_manual_Wakeup
********************************************************************************
*
* Summary:
*  Prepare Quadrature Decoder Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  pot_manual_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void pot_manual_Wakeup(void) 
{
    pot_manual_RestoreConfig();

    if (pot_manual_backup.enableState != 0u)
    {
        #if (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_8_BIT)
            pot_manual_Cnt8_Enable();
        #else 
            /* (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_16_BIT) || 
            *  (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT) 
            */
            pot_manual_Cnt16_Enable();
        #endif /* (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        pot_manual_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */


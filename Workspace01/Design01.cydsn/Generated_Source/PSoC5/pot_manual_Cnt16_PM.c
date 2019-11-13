/*******************************************************************************
* File Name: pot_manual_Cnt16_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "pot_manual_Cnt16.h"

static pot_manual_Cnt16_backupStruct pot_manual_Cnt16_backup;


/*******************************************************************************
* Function Name: pot_manual_Cnt16_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  pot_manual_Cnt16_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void pot_manual_Cnt16_SaveConfig(void) 
{
    #if (!pot_manual_Cnt16_UsingFixedFunction)

        pot_manual_Cnt16_backup.CounterUdb = pot_manual_Cnt16_ReadCounter();

        #if(!pot_manual_Cnt16_ControlRegRemoved)
            pot_manual_Cnt16_backup.CounterControlRegister = pot_manual_Cnt16_ReadControlRegister();
        #endif /* (!pot_manual_Cnt16_ControlRegRemoved) */

    #endif /* (!pot_manual_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: pot_manual_Cnt16_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  pot_manual_Cnt16_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void pot_manual_Cnt16_RestoreConfig(void) 
{      
    #if (!pot_manual_Cnt16_UsingFixedFunction)

       pot_manual_Cnt16_WriteCounter(pot_manual_Cnt16_backup.CounterUdb);

        #if(!pot_manual_Cnt16_ControlRegRemoved)
            pot_manual_Cnt16_WriteControlRegister(pot_manual_Cnt16_backup.CounterControlRegister);
        #endif /* (!pot_manual_Cnt16_ControlRegRemoved) */

    #endif /* (!pot_manual_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: pot_manual_Cnt16_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  pot_manual_Cnt16_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void pot_manual_Cnt16_Sleep(void) 
{
    #if(!pot_manual_Cnt16_ControlRegRemoved)
        /* Save Counter's enable state */
        if(pot_manual_Cnt16_CTRL_ENABLE == (pot_manual_Cnt16_CONTROL & pot_manual_Cnt16_CTRL_ENABLE))
        {
            /* Counter is enabled */
            pot_manual_Cnt16_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            pot_manual_Cnt16_backup.CounterEnableState = 0u;
        }
    #else
        pot_manual_Cnt16_backup.CounterEnableState = 1u;
        if(pot_manual_Cnt16_backup.CounterEnableState != 0u)
        {
            pot_manual_Cnt16_backup.CounterEnableState = 0u;
        }
    #endif /* (!pot_manual_Cnt16_ControlRegRemoved) */
    
    pot_manual_Cnt16_Stop();
    pot_manual_Cnt16_SaveConfig();
}


/*******************************************************************************
* Function Name: pot_manual_Cnt16_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  pot_manual_Cnt16_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void pot_manual_Cnt16_Wakeup(void) 
{
    pot_manual_Cnt16_RestoreConfig();
    #if(!pot_manual_Cnt16_ControlRegRemoved)
        if(pot_manual_Cnt16_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            pot_manual_Cnt16_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!pot_manual_Cnt16_ControlRegRemoved) */
    
}


/* [] END OF FILE */

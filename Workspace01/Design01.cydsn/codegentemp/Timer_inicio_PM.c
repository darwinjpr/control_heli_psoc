/*******************************************************************************
* File Name: Timer_inicio_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer_inicio.h"

static Timer_inicio_backupStruct Timer_inicio_backup;


/*******************************************************************************
* Function Name: Timer_inicio_SaveConfig
********************************************************************************
*
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
*  Timer_inicio_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_inicio_SaveConfig(void) 
{
    #if (!Timer_inicio_UsingFixedFunction)
        Timer_inicio_backup.TimerUdb = Timer_inicio_ReadCounter();
        Timer_inicio_backup.InterruptMaskValue = Timer_inicio_STATUS_MASK;
        #if (Timer_inicio_UsingHWCaptureCounter)
            Timer_inicio_backup.TimerCaptureCounter = Timer_inicio_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_inicio_UDB_CONTROL_REG_REMOVED)
            Timer_inicio_backup.TimerControlRegister = Timer_inicio_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_inicio_RestoreConfig
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
*  Timer_inicio_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_inicio_RestoreConfig(void) 
{   
    #if (!Timer_inicio_UsingFixedFunction)

        Timer_inicio_WriteCounter(Timer_inicio_backup.TimerUdb);
        Timer_inicio_STATUS_MASK =Timer_inicio_backup.InterruptMaskValue;
        #if (Timer_inicio_UsingHWCaptureCounter)
            Timer_inicio_SetCaptureCount(Timer_inicio_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_inicio_UDB_CONTROL_REG_REMOVED)
            Timer_inicio_WriteControlRegister(Timer_inicio_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_inicio_Sleep
********************************************************************************
*
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
*  Timer_inicio_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_inicio_Sleep(void) 
{
    #if(!Timer_inicio_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_inicio_CTRL_ENABLE == (Timer_inicio_CONTROL & Timer_inicio_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_inicio_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_inicio_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_inicio_Stop();
    Timer_inicio_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_inicio_Wakeup
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
*  Timer_inicio_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_inicio_Wakeup(void) 
{
    Timer_inicio_RestoreConfig();
    #if(!Timer_inicio_UDB_CONTROL_REG_REMOVED)
        if(Timer_inicio_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_inicio_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */

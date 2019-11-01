/*******************************************************************************
* File Name: Motor_IN_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Motor_IN.h"

static Motor_IN_backupStruct Motor_IN_backup;


/*******************************************************************************
* Function Name: Motor_IN_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Motor_IN_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Motor_IN_SaveConfig(void) 
{

    #if(!Motor_IN_UsingFixedFunction)
        #if(!Motor_IN_PWMModeIsCenterAligned)
            Motor_IN_backup.PWMPeriod = Motor_IN_ReadPeriod();
        #endif /* (!Motor_IN_PWMModeIsCenterAligned) */
        Motor_IN_backup.PWMUdb = Motor_IN_ReadCounter();
        #if (Motor_IN_UseStatus)
            Motor_IN_backup.InterruptMaskValue = Motor_IN_STATUS_MASK;
        #endif /* (Motor_IN_UseStatus) */

        #if(Motor_IN_DeadBandMode == Motor_IN__B_PWM__DBM_256_CLOCKS || \
            Motor_IN_DeadBandMode == Motor_IN__B_PWM__DBM_2_4_CLOCKS)
            Motor_IN_backup.PWMdeadBandValue = Motor_IN_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Motor_IN_KillModeMinTime)
             Motor_IN_backup.PWMKillCounterPeriod = Motor_IN_ReadKillTime();
        #endif /* (Motor_IN_KillModeMinTime) */

        #if(Motor_IN_UseControl)
            Motor_IN_backup.PWMControlRegister = Motor_IN_ReadControlRegister();
        #endif /* (Motor_IN_UseControl) */
    #endif  /* (!Motor_IN_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Motor_IN_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Motor_IN_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Motor_IN_RestoreConfig(void) 
{
        #if(!Motor_IN_UsingFixedFunction)
            #if(!Motor_IN_PWMModeIsCenterAligned)
                Motor_IN_WritePeriod(Motor_IN_backup.PWMPeriod);
            #endif /* (!Motor_IN_PWMModeIsCenterAligned) */

            Motor_IN_WriteCounter(Motor_IN_backup.PWMUdb);

            #if (Motor_IN_UseStatus)
                Motor_IN_STATUS_MASK = Motor_IN_backup.InterruptMaskValue;
            #endif /* (Motor_IN_UseStatus) */

            #if(Motor_IN_DeadBandMode == Motor_IN__B_PWM__DBM_256_CLOCKS || \
                Motor_IN_DeadBandMode == Motor_IN__B_PWM__DBM_2_4_CLOCKS)
                Motor_IN_WriteDeadTime(Motor_IN_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Motor_IN_KillModeMinTime)
                Motor_IN_WriteKillTime(Motor_IN_backup.PWMKillCounterPeriod);
            #endif /* (Motor_IN_KillModeMinTime) */

            #if(Motor_IN_UseControl)
                Motor_IN_WriteControlRegister(Motor_IN_backup.PWMControlRegister);
            #endif /* (Motor_IN_UseControl) */
        #endif  /* (!Motor_IN_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Motor_IN_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Motor_IN_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Motor_IN_Sleep(void) 
{
    #if(Motor_IN_UseControl)
        if(Motor_IN_CTRL_ENABLE == (Motor_IN_CONTROL & Motor_IN_CTRL_ENABLE))
        {
            /*Component is enabled */
            Motor_IN_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Motor_IN_backup.PWMEnableState = 0u;
        }
    #endif /* (Motor_IN_UseControl) */

    /* Stop component */
    Motor_IN_Stop();

    /* Save registers configuration */
    Motor_IN_SaveConfig();
}


/*******************************************************************************
* Function Name: Motor_IN_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Motor_IN_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Motor_IN_Wakeup(void) 
{
     /* Restore registers values */
    Motor_IN_RestoreConfig();

    if(Motor_IN_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Motor_IN_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */

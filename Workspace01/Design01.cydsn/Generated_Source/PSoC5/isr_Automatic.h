/*******************************************************************************
* File Name: isr_Automatic.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_isr_Automatic_H)
#define CY_ISR_isr_Automatic_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isr_Automatic_Start(void);
void isr_Automatic_StartEx(cyisraddress address);
void isr_Automatic_Stop(void);

CY_ISR_PROTO(isr_Automatic_Interrupt);

void isr_Automatic_SetVector(cyisraddress address);
cyisraddress isr_Automatic_GetVector(void);

void isr_Automatic_SetPriority(uint8 priority);
uint8 isr_Automatic_GetPriority(void);

void isr_Automatic_Enable(void);
uint8 isr_Automatic_GetState(void);
void isr_Automatic_Disable(void);

void isr_Automatic_SetPending(void);
void isr_Automatic_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_Automatic ISR. */
#define isr_Automatic_INTC_VECTOR            ((reg32 *) isr_Automatic__INTC_VECT)

/* Address of the isr_Automatic ISR priority. */
#define isr_Automatic_INTC_PRIOR             ((reg8 *) isr_Automatic__INTC_PRIOR_REG)

/* Priority of the isr_Automatic interrupt. */
#define isr_Automatic_INTC_PRIOR_NUMBER      isr_Automatic__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_Automatic interrupt. */
#define isr_Automatic_INTC_SET_EN            ((reg32 *) isr_Automatic__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_Automatic interrupt. */
#define isr_Automatic_INTC_CLR_EN            ((reg32 *) isr_Automatic__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_Automatic interrupt state to pending. */
#define isr_Automatic_INTC_SET_PD            ((reg32 *) isr_Automatic__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_Automatic interrupt. */
#define isr_Automatic_INTC_CLR_PD            ((reg32 *) isr_Automatic__INTC_CLR_PD_REG)


#endif /* CY_ISR_isr_Automatic_H */


/* [] END OF FILE */

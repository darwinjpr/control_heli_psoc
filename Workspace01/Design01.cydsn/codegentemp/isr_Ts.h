/*******************************************************************************
* File Name: isr_Ts.h
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
#if !defined(CY_ISR_isr_Ts_H)
#define CY_ISR_isr_Ts_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isr_Ts_Start(void);
void isr_Ts_StartEx(cyisraddress address);
void isr_Ts_Stop(void);

CY_ISR_PROTO(isr_Ts_Interrupt);

void isr_Ts_SetVector(cyisraddress address);
cyisraddress isr_Ts_GetVector(void);

void isr_Ts_SetPriority(uint8 priority);
uint8 isr_Ts_GetPriority(void);

void isr_Ts_Enable(void);
uint8 isr_Ts_GetState(void);
void isr_Ts_Disable(void);

void isr_Ts_SetPending(void);
void isr_Ts_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_Ts ISR. */
#define isr_Ts_INTC_VECTOR            ((reg32 *) isr_Ts__INTC_VECT)

/* Address of the isr_Ts ISR priority. */
#define isr_Ts_INTC_PRIOR             ((reg8 *) isr_Ts__INTC_PRIOR_REG)

/* Priority of the isr_Ts interrupt. */
#define isr_Ts_INTC_PRIOR_NUMBER      isr_Ts__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_Ts interrupt. */
#define isr_Ts_INTC_SET_EN            ((reg32 *) isr_Ts__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_Ts interrupt. */
#define isr_Ts_INTC_CLR_EN            ((reg32 *) isr_Ts__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_Ts interrupt state to pending. */
#define isr_Ts_INTC_SET_PD            ((reg32 *) isr_Ts__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_Ts interrupt. */
#define isr_Ts_INTC_CLR_PD            ((reg32 *) isr_Ts__INTC_CLR_PD_REG)


#endif /* CY_ISR_isr_Ts_H */


/* [] END OF FILE */

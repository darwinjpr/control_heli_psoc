/*******************************************************************************
* File Name: pot_manual.h  
* Version 3.0
*
* Description:
*  This file provides constants and parameter values for the Quadrature
*  Decoder component.
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

#if !defined(CY_QUADRATURE_DECODER_pot_manual_H)
#define CY_QUADRATURE_DECODER_pot_manual_H

#include "cyfitter.h"
#include "CyLib.h"
#include "cytypes.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component QuadDec_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#define pot_manual_COUNTER_SIZE               (16u)
#define pot_manual_COUNTER_SIZE_8_BIT         (8u)
#define pot_manual_COUNTER_SIZE_16_BIT        (16u)
#define pot_manual_COUNTER_SIZE_32_BIT        (32u)

#if (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_8_BIT)
    #include "pot_manual_Cnt8.h"
#else 
    /* (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_16_BIT) || 
    *  (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT) 
    */
    #include "pot_manual_Cnt16.h"
#endif /* pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_8_BIT */

extern uint8 pot_manual_initVar;


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define pot_manual_COUNTER_RESOLUTION         (1u)


/***************************************
*       Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} pot_manual_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  pot_manual_Init(void) ;
void  pot_manual_Start(void) ;
void  pot_manual_Stop(void) ;
void  pot_manual_Enable(void) ;
uint8 pot_manual_GetEvents(void) ;
void  pot_manual_SetInterruptMask(uint8 mask) ;
uint8 pot_manual_GetInterruptMask(void) ;
int16 pot_manual_GetCounter(void) ;
void  pot_manual_SetCounter(int16 value)
;
void  pot_manual_Sleep(void) ;
void  pot_manual_Wakeup(void) ;
void  pot_manual_SaveConfig(void) ;
void  pot_manual_RestoreConfig(void) ;

#if (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT)
    CY_ISR_PROTO(pot_manual_ISR);
#endif /* pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT */


/***************************************
*           API Constants
***************************************/

#if (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT)
    #define pot_manual_ISR_NUMBER             ((uint8) pot_manual_isr__INTC_NUMBER)
    #define pot_manual_ISR_PRIORITY           ((uint8) pot_manual_isr__INTC_PRIOR_NUM)
#endif /* pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT */


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define pot_manual_GLITCH_FILTERING           (1u)
#define pot_manual_INDEX_INPUT                (0u)


/***************************************
*    Initial Parameter Constants
***************************************/

#if (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_8_BIT)
    #define pot_manual_COUNTER_INIT_VALUE    (0x80u)
#else 
    /* (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_16_BIT) ||
    *  (pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_32_BIT)
    */
    #define pot_manual_COUNTER_INIT_VALUE    (0x8000u)
    #define pot_manual_COUNTER_MAX_VALUE     (0x7FFFu)
#endif /* pot_manual_COUNTER_SIZE == pot_manual_COUNTER_SIZE_8_BIT */


/***************************************
*             Registers
***************************************/

#define pot_manual_STATUS_REG                 (* (reg8 *) pot_manual_bQuadDec_Stsreg__STATUS_REG)
#define pot_manual_STATUS_PTR                 (  (reg8 *) pot_manual_bQuadDec_Stsreg__STATUS_REG)
#define pot_manual_STATUS_MASK                (* (reg8 *) pot_manual_bQuadDec_Stsreg__MASK_REG)
#define pot_manual_STATUS_MASK_PTR            (  (reg8 *) pot_manual_bQuadDec_Stsreg__MASK_REG)
#define pot_manual_SR_AUX_CONTROL             (* (reg8 *) pot_manual_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)
#define pot_manual_SR_AUX_CONTROL_PTR         (  (reg8 *) pot_manual_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)


/***************************************
*        Register Constants
***************************************/

#define pot_manual_COUNTER_OVERFLOW_SHIFT     (0x00u)
#define pot_manual_COUNTER_UNDERFLOW_SHIFT    (0x01u)
#define pot_manual_COUNTER_RESET_SHIFT        (0x02u)
#define pot_manual_INVALID_IN_SHIFT           (0x03u)
#define pot_manual_COUNTER_OVERFLOW           ((uint8) (0x01u << pot_manual_COUNTER_OVERFLOW_SHIFT))
#define pot_manual_COUNTER_UNDERFLOW          ((uint8) (0x01u << pot_manual_COUNTER_UNDERFLOW_SHIFT))
#define pot_manual_COUNTER_RESET              ((uint8) (0x01u << pot_manual_COUNTER_RESET_SHIFT))
#define pot_manual_INVALID_IN                 ((uint8) (0x01u << pot_manual_INVALID_IN_SHIFT))

#define pot_manual_INTERRUPTS_ENABLE_SHIFT    (0x04u)
#define pot_manual_INTERRUPTS_ENABLE          ((uint8)(0x01u << pot_manual_INTERRUPTS_ENABLE_SHIFT))
#define pot_manual_INIT_INT_MASK              (0x0Fu)


/******************************************************************************************
* Following code are OBSOLETE and must not be used starting from Quadrature Decoder 2.20
******************************************************************************************/
#define pot_manual_DISABLE                    (0x00u)


#endif /* CY_QUADRATURE_DECODER_pot_manual_H */


/* [] END OF FILE */

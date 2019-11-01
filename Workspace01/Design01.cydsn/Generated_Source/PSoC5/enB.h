/*******************************************************************************
* File Name: enB.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_enB_H) /* Pins enB_H */
#define CY_PINS_enB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "enB_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 enB__PORT == 15 && ((enB__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    enB_Write(uint8 value);
void    enB_SetDriveMode(uint8 mode);
uint8   enB_ReadDataReg(void);
uint8   enB_Read(void);
void    enB_SetInterruptMode(uint16 position, uint16 mode);
uint8   enB_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the enB_SetDriveMode() function.
     *  @{
     */
        #define enB_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define enB_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define enB_DM_RES_UP          PIN_DM_RES_UP
        #define enB_DM_RES_DWN         PIN_DM_RES_DWN
        #define enB_DM_OD_LO           PIN_DM_OD_LO
        #define enB_DM_OD_HI           PIN_DM_OD_HI
        #define enB_DM_STRONG          PIN_DM_STRONG
        #define enB_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define enB_MASK               enB__MASK
#define enB_SHIFT              enB__SHIFT
#define enB_WIDTH              1u

/* Interrupt constants */
#if defined(enB__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in enB_SetInterruptMode() function.
     *  @{
     */
        #define enB_INTR_NONE      (uint16)(0x0000u)
        #define enB_INTR_RISING    (uint16)(0x0001u)
        #define enB_INTR_FALLING   (uint16)(0x0002u)
        #define enB_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define enB_INTR_MASK      (0x01u) 
#endif /* (enB__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define enB_PS                     (* (reg8 *) enB__PS)
/* Data Register */
#define enB_DR                     (* (reg8 *) enB__DR)
/* Port Number */
#define enB_PRT_NUM                (* (reg8 *) enB__PRT) 
/* Connect to Analog Globals */                                                  
#define enB_AG                     (* (reg8 *) enB__AG)                       
/* Analog MUX bux enable */
#define enB_AMUX                   (* (reg8 *) enB__AMUX) 
/* Bidirectional Enable */                                                        
#define enB_BIE                    (* (reg8 *) enB__BIE)
/* Bit-mask for Aliased Register Access */
#define enB_BIT_MASK               (* (reg8 *) enB__BIT_MASK)
/* Bypass Enable */
#define enB_BYP                    (* (reg8 *) enB__BYP)
/* Port wide control signals */                                                   
#define enB_CTL                    (* (reg8 *) enB__CTL)
/* Drive Modes */
#define enB_DM0                    (* (reg8 *) enB__DM0) 
#define enB_DM1                    (* (reg8 *) enB__DM1)
#define enB_DM2                    (* (reg8 *) enB__DM2) 
/* Input Buffer Disable Override */
#define enB_INP_DIS                (* (reg8 *) enB__INP_DIS)
/* LCD Common or Segment Drive */
#define enB_LCD_COM_SEG            (* (reg8 *) enB__LCD_COM_SEG)
/* Enable Segment LCD */
#define enB_LCD_EN                 (* (reg8 *) enB__LCD_EN)
/* Slew Rate Control */
#define enB_SLW                    (* (reg8 *) enB__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define enB_PRTDSI__CAPS_SEL       (* (reg8 *) enB__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define enB_PRTDSI__DBL_SYNC_IN    (* (reg8 *) enB__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define enB_PRTDSI__OE_SEL0        (* (reg8 *) enB__PRTDSI__OE_SEL0) 
#define enB_PRTDSI__OE_SEL1        (* (reg8 *) enB__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define enB_PRTDSI__OUT_SEL0       (* (reg8 *) enB__PRTDSI__OUT_SEL0) 
#define enB_PRTDSI__OUT_SEL1       (* (reg8 *) enB__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define enB_PRTDSI__SYNC_OUT       (* (reg8 *) enB__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(enB__SIO_CFG)
    #define enB_SIO_HYST_EN        (* (reg8 *) enB__SIO_HYST_EN)
    #define enB_SIO_REG_HIFREQ     (* (reg8 *) enB__SIO_REG_HIFREQ)
    #define enB_SIO_CFG            (* (reg8 *) enB__SIO_CFG)
    #define enB_SIO_DIFF           (* (reg8 *) enB__SIO_DIFF)
#endif /* (enB__SIO_CFG) */

/* Interrupt Registers */
#if defined(enB__INTSTAT)
    #define enB_INTSTAT            (* (reg8 *) enB__INTSTAT)
    #define enB_SNAP               (* (reg8 *) enB__SNAP)
    
	#define enB_0_INTTYPE_REG 		(* (reg8 *) enB__0__INTTYPE)
#endif /* (enB__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_enB_H */


/* [] END OF FILE */

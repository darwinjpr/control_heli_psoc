/*******************************************************************************
* File Name: enA.h  
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

#if !defined(CY_PINS_enA_H) /* Pins enA_H */
#define CY_PINS_enA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "enA_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 enA__PORT == 15 && ((enA__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    enA_Write(uint8 value);
void    enA_SetDriveMode(uint8 mode);
uint8   enA_ReadDataReg(void);
uint8   enA_Read(void);
void    enA_SetInterruptMode(uint16 position, uint16 mode);
uint8   enA_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the enA_SetDriveMode() function.
     *  @{
     */
        #define enA_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define enA_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define enA_DM_RES_UP          PIN_DM_RES_UP
        #define enA_DM_RES_DWN         PIN_DM_RES_DWN
        #define enA_DM_OD_LO           PIN_DM_OD_LO
        #define enA_DM_OD_HI           PIN_DM_OD_HI
        #define enA_DM_STRONG          PIN_DM_STRONG
        #define enA_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define enA_MASK               enA__MASK
#define enA_SHIFT              enA__SHIFT
#define enA_WIDTH              1u

/* Interrupt constants */
#if defined(enA__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in enA_SetInterruptMode() function.
     *  @{
     */
        #define enA_INTR_NONE      (uint16)(0x0000u)
        #define enA_INTR_RISING    (uint16)(0x0001u)
        #define enA_INTR_FALLING   (uint16)(0x0002u)
        #define enA_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define enA_INTR_MASK      (0x01u) 
#endif /* (enA__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define enA_PS                     (* (reg8 *) enA__PS)
/* Data Register */
#define enA_DR                     (* (reg8 *) enA__DR)
/* Port Number */
#define enA_PRT_NUM                (* (reg8 *) enA__PRT) 
/* Connect to Analog Globals */                                                  
#define enA_AG                     (* (reg8 *) enA__AG)                       
/* Analog MUX bux enable */
#define enA_AMUX                   (* (reg8 *) enA__AMUX) 
/* Bidirectional Enable */                                                        
#define enA_BIE                    (* (reg8 *) enA__BIE)
/* Bit-mask for Aliased Register Access */
#define enA_BIT_MASK               (* (reg8 *) enA__BIT_MASK)
/* Bypass Enable */
#define enA_BYP                    (* (reg8 *) enA__BYP)
/* Port wide control signals */                                                   
#define enA_CTL                    (* (reg8 *) enA__CTL)
/* Drive Modes */
#define enA_DM0                    (* (reg8 *) enA__DM0) 
#define enA_DM1                    (* (reg8 *) enA__DM1)
#define enA_DM2                    (* (reg8 *) enA__DM2) 
/* Input Buffer Disable Override */
#define enA_INP_DIS                (* (reg8 *) enA__INP_DIS)
/* LCD Common or Segment Drive */
#define enA_LCD_COM_SEG            (* (reg8 *) enA__LCD_COM_SEG)
/* Enable Segment LCD */
#define enA_LCD_EN                 (* (reg8 *) enA__LCD_EN)
/* Slew Rate Control */
#define enA_SLW                    (* (reg8 *) enA__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define enA_PRTDSI__CAPS_SEL       (* (reg8 *) enA__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define enA_PRTDSI__DBL_SYNC_IN    (* (reg8 *) enA__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define enA_PRTDSI__OE_SEL0        (* (reg8 *) enA__PRTDSI__OE_SEL0) 
#define enA_PRTDSI__OE_SEL1        (* (reg8 *) enA__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define enA_PRTDSI__OUT_SEL0       (* (reg8 *) enA__PRTDSI__OUT_SEL0) 
#define enA_PRTDSI__OUT_SEL1       (* (reg8 *) enA__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define enA_PRTDSI__SYNC_OUT       (* (reg8 *) enA__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(enA__SIO_CFG)
    #define enA_SIO_HYST_EN        (* (reg8 *) enA__SIO_HYST_EN)
    #define enA_SIO_REG_HIFREQ     (* (reg8 *) enA__SIO_REG_HIFREQ)
    #define enA_SIO_CFG            (* (reg8 *) enA__SIO_CFG)
    #define enA_SIO_DIFF           (* (reg8 *) enA__SIO_DIFF)
#endif /* (enA__SIO_CFG) */

/* Interrupt Registers */
#if defined(enA__INTSTAT)
    #define enA_INTSTAT            (* (reg8 *) enA__INTSTAT)
    #define enA_SNAP               (* (reg8 *) enA__SNAP)
    
	#define enA_0_INTTYPE_REG 		(* (reg8 *) enA__0__INTTYPE)
#endif /* (enA__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_enA_H */


/* [] END OF FILE */

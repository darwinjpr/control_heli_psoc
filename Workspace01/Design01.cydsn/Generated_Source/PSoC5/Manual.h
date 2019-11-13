/*******************************************************************************
* File Name: Manual.h  
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

#if !defined(CY_PINS_Manual_H) /* Pins Manual_H */
#define CY_PINS_Manual_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Manual_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Manual__PORT == 15 && ((Manual__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Manual_Write(uint8 value);
void    Manual_SetDriveMode(uint8 mode);
uint8   Manual_ReadDataReg(void);
uint8   Manual_Read(void);
void    Manual_SetInterruptMode(uint16 position, uint16 mode);
uint8   Manual_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Manual_SetDriveMode() function.
     *  @{
     */
        #define Manual_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Manual_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Manual_DM_RES_UP          PIN_DM_RES_UP
        #define Manual_DM_RES_DWN         PIN_DM_RES_DWN
        #define Manual_DM_OD_LO           PIN_DM_OD_LO
        #define Manual_DM_OD_HI           PIN_DM_OD_HI
        #define Manual_DM_STRONG          PIN_DM_STRONG
        #define Manual_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Manual_MASK               Manual__MASK
#define Manual_SHIFT              Manual__SHIFT
#define Manual_WIDTH              1u

/* Interrupt constants */
#if defined(Manual__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Manual_SetInterruptMode() function.
     *  @{
     */
        #define Manual_INTR_NONE      (uint16)(0x0000u)
        #define Manual_INTR_RISING    (uint16)(0x0001u)
        #define Manual_INTR_FALLING   (uint16)(0x0002u)
        #define Manual_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Manual_INTR_MASK      (0x01u) 
#endif /* (Manual__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Manual_PS                     (* (reg8 *) Manual__PS)
/* Data Register */
#define Manual_DR                     (* (reg8 *) Manual__DR)
/* Port Number */
#define Manual_PRT_NUM                (* (reg8 *) Manual__PRT) 
/* Connect to Analog Globals */                                                  
#define Manual_AG                     (* (reg8 *) Manual__AG)                       
/* Analog MUX bux enable */
#define Manual_AMUX                   (* (reg8 *) Manual__AMUX) 
/* Bidirectional Enable */                                                        
#define Manual_BIE                    (* (reg8 *) Manual__BIE)
/* Bit-mask for Aliased Register Access */
#define Manual_BIT_MASK               (* (reg8 *) Manual__BIT_MASK)
/* Bypass Enable */
#define Manual_BYP                    (* (reg8 *) Manual__BYP)
/* Port wide control signals */                                                   
#define Manual_CTL                    (* (reg8 *) Manual__CTL)
/* Drive Modes */
#define Manual_DM0                    (* (reg8 *) Manual__DM0) 
#define Manual_DM1                    (* (reg8 *) Manual__DM1)
#define Manual_DM2                    (* (reg8 *) Manual__DM2) 
/* Input Buffer Disable Override */
#define Manual_INP_DIS                (* (reg8 *) Manual__INP_DIS)
/* LCD Common or Segment Drive */
#define Manual_LCD_COM_SEG            (* (reg8 *) Manual__LCD_COM_SEG)
/* Enable Segment LCD */
#define Manual_LCD_EN                 (* (reg8 *) Manual__LCD_EN)
/* Slew Rate Control */
#define Manual_SLW                    (* (reg8 *) Manual__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Manual_PRTDSI__CAPS_SEL       (* (reg8 *) Manual__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Manual_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Manual__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Manual_PRTDSI__OE_SEL0        (* (reg8 *) Manual__PRTDSI__OE_SEL0) 
#define Manual_PRTDSI__OE_SEL1        (* (reg8 *) Manual__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Manual_PRTDSI__OUT_SEL0       (* (reg8 *) Manual__PRTDSI__OUT_SEL0) 
#define Manual_PRTDSI__OUT_SEL1       (* (reg8 *) Manual__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Manual_PRTDSI__SYNC_OUT       (* (reg8 *) Manual__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Manual__SIO_CFG)
    #define Manual_SIO_HYST_EN        (* (reg8 *) Manual__SIO_HYST_EN)
    #define Manual_SIO_REG_HIFREQ     (* (reg8 *) Manual__SIO_REG_HIFREQ)
    #define Manual_SIO_CFG            (* (reg8 *) Manual__SIO_CFG)
    #define Manual_SIO_DIFF           (* (reg8 *) Manual__SIO_DIFF)
#endif /* (Manual__SIO_CFG) */

/* Interrupt Registers */
#if defined(Manual__INTSTAT)
    #define Manual_INTSTAT            (* (reg8 *) Manual__INTSTAT)
    #define Manual_SNAP               (* (reg8 *) Manual__SNAP)
    
	#define Manual_0_INTTYPE_REG 		(* (reg8 *) Manual__0__INTTYPE)
#endif /* (Manual__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Manual_H */


/* [] END OF FILE */

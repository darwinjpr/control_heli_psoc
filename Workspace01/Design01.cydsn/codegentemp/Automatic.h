/*******************************************************************************
* File Name: Automatic.h  
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

#if !defined(CY_PINS_Automatic_H) /* Pins Automatic_H */
#define CY_PINS_Automatic_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Automatic_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Automatic__PORT == 15 && ((Automatic__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Automatic_Write(uint8 value);
void    Automatic_SetDriveMode(uint8 mode);
uint8   Automatic_ReadDataReg(void);
uint8   Automatic_Read(void);
void    Automatic_SetInterruptMode(uint16 position, uint16 mode);
uint8   Automatic_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Automatic_SetDriveMode() function.
     *  @{
     */
        #define Automatic_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Automatic_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Automatic_DM_RES_UP          PIN_DM_RES_UP
        #define Automatic_DM_RES_DWN         PIN_DM_RES_DWN
        #define Automatic_DM_OD_LO           PIN_DM_OD_LO
        #define Automatic_DM_OD_HI           PIN_DM_OD_HI
        #define Automatic_DM_STRONG          PIN_DM_STRONG
        #define Automatic_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Automatic_MASK               Automatic__MASK
#define Automatic_SHIFT              Automatic__SHIFT
#define Automatic_WIDTH              1u

/* Interrupt constants */
#if defined(Automatic__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Automatic_SetInterruptMode() function.
     *  @{
     */
        #define Automatic_INTR_NONE      (uint16)(0x0000u)
        #define Automatic_INTR_RISING    (uint16)(0x0001u)
        #define Automatic_INTR_FALLING   (uint16)(0x0002u)
        #define Automatic_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Automatic_INTR_MASK      (0x01u) 
#endif /* (Automatic__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Automatic_PS                     (* (reg8 *) Automatic__PS)
/* Data Register */
#define Automatic_DR                     (* (reg8 *) Automatic__DR)
/* Port Number */
#define Automatic_PRT_NUM                (* (reg8 *) Automatic__PRT) 
/* Connect to Analog Globals */                                                  
#define Automatic_AG                     (* (reg8 *) Automatic__AG)                       
/* Analog MUX bux enable */
#define Automatic_AMUX                   (* (reg8 *) Automatic__AMUX) 
/* Bidirectional Enable */                                                        
#define Automatic_BIE                    (* (reg8 *) Automatic__BIE)
/* Bit-mask for Aliased Register Access */
#define Automatic_BIT_MASK               (* (reg8 *) Automatic__BIT_MASK)
/* Bypass Enable */
#define Automatic_BYP                    (* (reg8 *) Automatic__BYP)
/* Port wide control signals */                                                   
#define Automatic_CTL                    (* (reg8 *) Automatic__CTL)
/* Drive Modes */
#define Automatic_DM0                    (* (reg8 *) Automatic__DM0) 
#define Automatic_DM1                    (* (reg8 *) Automatic__DM1)
#define Automatic_DM2                    (* (reg8 *) Automatic__DM2) 
/* Input Buffer Disable Override */
#define Automatic_INP_DIS                (* (reg8 *) Automatic__INP_DIS)
/* LCD Common or Segment Drive */
#define Automatic_LCD_COM_SEG            (* (reg8 *) Automatic__LCD_COM_SEG)
/* Enable Segment LCD */
#define Automatic_LCD_EN                 (* (reg8 *) Automatic__LCD_EN)
/* Slew Rate Control */
#define Automatic_SLW                    (* (reg8 *) Automatic__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Automatic_PRTDSI__CAPS_SEL       (* (reg8 *) Automatic__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Automatic_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Automatic__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Automatic_PRTDSI__OE_SEL0        (* (reg8 *) Automatic__PRTDSI__OE_SEL0) 
#define Automatic_PRTDSI__OE_SEL1        (* (reg8 *) Automatic__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Automatic_PRTDSI__OUT_SEL0       (* (reg8 *) Automatic__PRTDSI__OUT_SEL0) 
#define Automatic_PRTDSI__OUT_SEL1       (* (reg8 *) Automatic__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Automatic_PRTDSI__SYNC_OUT       (* (reg8 *) Automatic__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Automatic__SIO_CFG)
    #define Automatic_SIO_HYST_EN        (* (reg8 *) Automatic__SIO_HYST_EN)
    #define Automatic_SIO_REG_HIFREQ     (* (reg8 *) Automatic__SIO_REG_HIFREQ)
    #define Automatic_SIO_CFG            (* (reg8 *) Automatic__SIO_CFG)
    #define Automatic_SIO_DIFF           (* (reg8 *) Automatic__SIO_DIFF)
#endif /* (Automatic__SIO_CFG) */

/* Interrupt Registers */
#if defined(Automatic__INTSTAT)
    #define Automatic_INTSTAT            (* (reg8 *) Automatic__INTSTAT)
    #define Automatic_SNAP               (* (reg8 *) Automatic__SNAP)
    
	#define Automatic_0_INTTYPE_REG 		(* (reg8 *) Automatic__0__INTTYPE)
#endif /* (Automatic__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Automatic_H */


/* [] END OF FILE */

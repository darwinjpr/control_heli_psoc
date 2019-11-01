/*******************************************************************************
* File Name: Aumentar.h  
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

#if !defined(CY_PINS_Aumentar_H) /* Pins Aumentar_H */
#define CY_PINS_Aumentar_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Aumentar_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Aumentar__PORT == 15 && ((Aumentar__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Aumentar_Write(uint8 value);
void    Aumentar_SetDriveMode(uint8 mode);
uint8   Aumentar_ReadDataReg(void);
uint8   Aumentar_Read(void);
void    Aumentar_SetInterruptMode(uint16 position, uint16 mode);
uint8   Aumentar_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Aumentar_SetDriveMode() function.
     *  @{
     */
        #define Aumentar_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Aumentar_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Aumentar_DM_RES_UP          PIN_DM_RES_UP
        #define Aumentar_DM_RES_DWN         PIN_DM_RES_DWN
        #define Aumentar_DM_OD_LO           PIN_DM_OD_LO
        #define Aumentar_DM_OD_HI           PIN_DM_OD_HI
        #define Aumentar_DM_STRONG          PIN_DM_STRONG
        #define Aumentar_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Aumentar_MASK               Aumentar__MASK
#define Aumentar_SHIFT              Aumentar__SHIFT
#define Aumentar_WIDTH              1u

/* Interrupt constants */
#if defined(Aumentar__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Aumentar_SetInterruptMode() function.
     *  @{
     */
        #define Aumentar_INTR_NONE      (uint16)(0x0000u)
        #define Aumentar_INTR_RISING    (uint16)(0x0001u)
        #define Aumentar_INTR_FALLING   (uint16)(0x0002u)
        #define Aumentar_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Aumentar_INTR_MASK      (0x01u) 
#endif /* (Aumentar__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Aumentar_PS                     (* (reg8 *) Aumentar__PS)
/* Data Register */
#define Aumentar_DR                     (* (reg8 *) Aumentar__DR)
/* Port Number */
#define Aumentar_PRT_NUM                (* (reg8 *) Aumentar__PRT) 
/* Connect to Analog Globals */                                                  
#define Aumentar_AG                     (* (reg8 *) Aumentar__AG)                       
/* Analog MUX bux enable */
#define Aumentar_AMUX                   (* (reg8 *) Aumentar__AMUX) 
/* Bidirectional Enable */                                                        
#define Aumentar_BIE                    (* (reg8 *) Aumentar__BIE)
/* Bit-mask for Aliased Register Access */
#define Aumentar_BIT_MASK               (* (reg8 *) Aumentar__BIT_MASK)
/* Bypass Enable */
#define Aumentar_BYP                    (* (reg8 *) Aumentar__BYP)
/* Port wide control signals */                                                   
#define Aumentar_CTL                    (* (reg8 *) Aumentar__CTL)
/* Drive Modes */
#define Aumentar_DM0                    (* (reg8 *) Aumentar__DM0) 
#define Aumentar_DM1                    (* (reg8 *) Aumentar__DM1)
#define Aumentar_DM2                    (* (reg8 *) Aumentar__DM2) 
/* Input Buffer Disable Override */
#define Aumentar_INP_DIS                (* (reg8 *) Aumentar__INP_DIS)
/* LCD Common or Segment Drive */
#define Aumentar_LCD_COM_SEG            (* (reg8 *) Aumentar__LCD_COM_SEG)
/* Enable Segment LCD */
#define Aumentar_LCD_EN                 (* (reg8 *) Aumentar__LCD_EN)
/* Slew Rate Control */
#define Aumentar_SLW                    (* (reg8 *) Aumentar__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Aumentar_PRTDSI__CAPS_SEL       (* (reg8 *) Aumentar__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Aumentar_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Aumentar__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Aumentar_PRTDSI__OE_SEL0        (* (reg8 *) Aumentar__PRTDSI__OE_SEL0) 
#define Aumentar_PRTDSI__OE_SEL1        (* (reg8 *) Aumentar__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Aumentar_PRTDSI__OUT_SEL0       (* (reg8 *) Aumentar__PRTDSI__OUT_SEL0) 
#define Aumentar_PRTDSI__OUT_SEL1       (* (reg8 *) Aumentar__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Aumentar_PRTDSI__SYNC_OUT       (* (reg8 *) Aumentar__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Aumentar__SIO_CFG)
    #define Aumentar_SIO_HYST_EN        (* (reg8 *) Aumentar__SIO_HYST_EN)
    #define Aumentar_SIO_REG_HIFREQ     (* (reg8 *) Aumentar__SIO_REG_HIFREQ)
    #define Aumentar_SIO_CFG            (* (reg8 *) Aumentar__SIO_CFG)
    #define Aumentar_SIO_DIFF           (* (reg8 *) Aumentar__SIO_DIFF)
#endif /* (Aumentar__SIO_CFG) */

/* Interrupt Registers */
#if defined(Aumentar__INTSTAT)
    #define Aumentar_INTSTAT            (* (reg8 *) Aumentar__INTSTAT)
    #define Aumentar_SNAP               (* (reg8 *) Aumentar__SNAP)
    
	#define Aumentar_0_INTTYPE_REG 		(* (reg8 *) Aumentar__0__INTTYPE)
#endif /* (Aumentar__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Aumentar_H */


/* [] END OF FILE */

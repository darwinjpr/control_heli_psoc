/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

/* Declaración de variables */
int16 control=120;
int counter=0;

/* Métodos de interrupción */

CY_ISR(AumentarInt)
{
    if(control<200)
    {
        control=control+1;
        PWM_Motor_WriteCompare(control);
        Reset_PWM_Write(1);
        Reset_PWM_Write(0);
        
        LED_Write(1);
        
        LCD_ClearDisplay();
        LCD_Position(0,0);
        LCD_PrintString("control:");
    
        LCD_Position(0,10);
        LCD_PrintNumber(control);
        
        LCD_Position(1,0);
        LCD_PrintString("angulo:");
        LCD_Position(1,10);
        LCD_PrintNumber(counter);
        
    }
}

CY_ISR(DisminuirInt)
{
    if(control>100)
    {
        control=control-1;
        PWM_Motor_WriteCompare(control);
        Reset_PWM_Write(1);
        Reset_PWM_Write(0);
        
        LED_Write(0);
        
        LCD_ClearDisplay();
        LCD_Position(0,0);
        LCD_PrintString("control:");
    
        LCD_Position(0,10);
        LCD_PrintNumber(control);
        
        LCD_Position(1,0);
        LCD_PrintString("angulo:");
        LCD_Position(1,10);
        LCD_PrintNumber(counter);
    }
}

CY_ISR(Muestreo)
{
    counter=QuadDec_GetCounter();
    
    LCD_ClearDisplay();
    LCD_Position(0,0);
    LCD_PrintString("control:");

    LCD_Position(0,10);
    LCD_PrintNumber(control);
    
    LCD_Position(1,0);
    LCD_PrintString("angulo:");
    LCD_Position(1,10);
    LCD_PrintNumber(counter);
    
}

int main(void)
{
    PWM_Motor_Start();
    LCD_Start();
    timer_clock_Start();
    QuadDec_Start();
    Timer_Start();
    
    /*QuadDec_SetCounter(0);*/
    
    LCD_Position(0,0);
    LCD_PrintString("control:");
    LCD_Position(0,10);
    LCD_PrintNumber(control);
    
    LCD_Position(1,0);
    LCD_PrintString("angulo:");
    LCD_Position(1,10);
    LCD_PrintNumber(counter);
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    isr_Aumentar_StartEx(AumentarInt);
    isr_Disminuir_StartEx(DisminuirInt);
    isr_Ts_StartEx(Muestreo);
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    
    for(;;)
    {
        
    }
}

/* [] END OF FILE */

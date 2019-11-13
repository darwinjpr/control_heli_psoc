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
float Ts=0.01; /* Periodo de muestreo de 10ms */
int16 control_manual=120;
int16 control_auto=100;
volatile float control_anterior=0;
int angulo=0;
int ref_angulo=162;
/* seleccion de control */
int16 control=0;    
/* Variables de control */
float radio = 0.15;
float PkP=10;
float PkI=0.01;/*************IMPORTANTE REVISAR EN LABORATORIO (talvez hay que aumentarlo, ya que tiene una reaccion muy lenta)**************/
float PkD=500;
volatile float error,error_anterior;
volatile float Pkp,Pki,Pkd;
volatile float Pki_anterior=0;
/*Variable de inicio para ESC*/
int ready=0;

/* Métodos de interrupción */
CY_ISR(Manual_Int)
{
    if(ready==1){ 
        control=0;
        LED_Write(0);
        pot_manual_SetCounter(140);/*valor de entrada de pwm*/
    }
}

CY_ISR(Automatic_Int)
{
    if(ready==1){ 
        control=1;
        LED_Write(1);
        pot_manual_SetCounter(160);/*valor de referencia de ángulo*/
    }
}

CY_ISR(Muestreo)
{
    if(ready==1){ 

        /*****falta agregar constantes para medir el ángulo en grados******/
        angulo=QuadDec_GetCounter();
        if (control==0)
        {   
            control_manual=pot_manual_GetCounter();
            PWM_Motor_WriteCompare(control_manual);
            Reset_PWM_Write(1);
            Reset_PWM_Write(0);
            
            LCD_ClearDisplay();
            LCD_Position(0,0);
            LCD_PrintString("Ctrl:");
            LCD_Position(0,5);
            LCD_PrintNumber(control_manual);        
            LCD_Position(1,0);
            LCD_PrintString("Angu:");
            LCD_Position(1,5);
            LCD_PrintNumber(angulo);
            
            LCD_Position(0,15);
            LCD_PrintString("M");           
        }
        if (control==1)/* calculo de la salida de control automático */
        {
            ref_angulo=pot_manual_GetCounter();
            error=radio*(ref_angulo-angulo);
            Pkp=PkP*error;
            Pki=Pki_anterior+PkI*error;
            Pkd=PkD*(error-error_anterior)/Ts;
            control_auto= 125+Pkp+Pki+Pkd;
            /* Prevenciones (prevenciones de visualizacion en psoc)*/
            /***Para hacer pruebas con la planta cambiar limites a 120 y 200***/
            if(control_auto>200){control_auto=200;}
            if(control_auto<0){control_auto=125;}
            /**Indicador LED***/
            if(control_auto<control_anterior){LED_Write(0);}
            if(control_auto>control_anterior){LED_Write(1);}
            
            PWM_Motor_WriteCompare(control_auto);
            Reset_PWM_Write(1);
            Reset_PWM_Write(0);
            
            control_anterior=control_auto;
            
            Pki_anterior=Pki;
            error_anterior=error;
            
            
            LCD_ClearDisplay();
            LCD_Position(0,0);
            LCD_PrintString("Ctrl:");
            LCD_Position(0,5);
            LCD_PrintNumber(control_auto);        
            LCD_Position(1,0);
            LCD_PrintString("Angu:");
            LCD_Position(1,5);
            LCD_PrintNumber(angulo);
            
            LCD_Position(0,15);
            LCD_PrintString("A");     
            LCD_Position(1,9);
            LCD_PrintString("ref:");  
            LCD_Position(1,13);
            LCD_PrintNumber(ref_angulo);
            
        }

    }
    
}

CY_ISR(inicio)
{
    ready=1;
}
int main(void)
{
    PWM_Motor_Start();
    LCD_Start();
    timer_clock_Start();
    QuadDec_Start();
    pot_manual_Start();
    Timer_Start();
    Clock_lento_Start();
    Timer_inicio_Start();
    
    
    /*QuadDec_SetCounter(0);*/
    
    LCD_Position(0,0);
    LCD_PrintString("Ctrl:");
    LCD_Position(0,6);
    if (control==0)
    {
        LCD_PrintNumber(control_manual);
        LCD_Position(0,15);
        LCD_PrintString("M"); 
        pot_manual_SetCounter(140);
    }
    if (control==1)
    {
        LCD_PrintNumber(control_auto);
        LCD_Position(0,15);
        LCD_PrintString("A"); 
        pot_manual_SetCounter(160);
    }
    LCD_Position(1,0);
    LCD_PrintString("Angu:");
    LCD_Position(1,6);
    LCD_PrintNumber(angulo);
    
    QuadDec_SetCounter(160);
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    isr_Manual_StartEx(Manual_Int);
    isr_Automatic_StartEx(Automatic_Int);
    isr_Ts_StartEx(Muestreo);
    isr_inicio_StartEx(inicio);
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    
    for(;;)
    {
        
    }
}

/* [] END OF FILE */

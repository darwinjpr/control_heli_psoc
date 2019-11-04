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
int ref_angulo=81;
/* seleccion de control */
int16 control=1;    
/* Variables de control */
float radio = 0.1;
float PkP=0.3;
float PkI=0.001;/**************IMPORTANTE REVISAR EN LABORATORIO (talvez hay que aumentarlo, ya que tiene una reaccion muy lenta)**************/
float PkD=1000;
volatile float error,error_anterior;
volatile float Pkp,Pki,Pkd;
volatile float Pki_anterior=0;


/* Métodos de interrupción */
CY_ISR(AumentarInt)
{
    if(control_manual<200)
    {
        control_manual=control_manual+1;
        PWM_Motor_WriteCompare(control_manual);
        Reset_PWM_Write(1);
        Reset_PWM_Write(0);
        
        LED_Write(1);
        
        LCD_ClearDisplay();
        LCD_Position(0,0);
        LCD_PrintString("control:");
    
        LCD_Position(0,10);
        LCD_PrintNumber(control_manual);
        
        LCD_Position(1,0);
        LCD_PrintString("angulo:");
        LCD_Position(1,10);
        LCD_PrintNumber(angulo);
        
    }
}

CY_ISR(DisminuirInt)
{
    if(control_manual>100)
    {
        control_manual=control_manual-1;
        PWM_Motor_WriteCompare(control_manual);
        Reset_PWM_Write(1);
        Reset_PWM_Write(0);
        
        LED_Write(0);
        
        LCD_ClearDisplay();
        LCD_Position(0,0);
        LCD_PrintString("control:");
    
        LCD_Position(0,10);
        LCD_PrintNumber(control_manual);
        
        LCD_Position(1,0);
        LCD_PrintString("angulo:");
        LCD_Position(1,10);
        LCD_PrintNumber(angulo);
    }
}

CY_ISR(Muestreo)
{
    /*****falta agregar constantes para medir el ángulo en grados******/
    angulo=QuadDec_GetCounter();
    
    LCD_ClearDisplay();
    LCD_Position(0,0);
    LCD_PrintString("control:");

    LCD_Position(0,10);
    if (control==0)
    {
        LCD_PrintNumber(control_manual);
    }
    if (control==1)
    /* calculo de la salida de control automático */
    {
        error=radio*(ref_angulo-angulo);
        Pkp=PkP*error;
        Pki=Pki_anterior+PkI*error;
        Pkd=PkD*(error_anterior-error)/Ts;
        control_auto=165+Pkp+Pki+Pkd;
        /* Prevenciones (prevenciones de visualizacion en psoc)*/
        /***Para hacer pruebas con la planta cambiar limites a 120 y 200***/
        if(control_auto>32000){control_auto=32000;}
        if(control_auto<0){control_auto=0;}
        /**Indicador LED***/
        if(control_auto<control_anterior){LED_Write(0);}
        if(control_auto>control_anterior){LED_Write(1);}
        control_anterior=control_auto;
        
        Pki_anterior=Pki;
        error_anterior=error;
        LCD_PrintNumber(control_auto);
    }
    LCD_Position(1,0);
    LCD_PrintString("angulo:");
    LCD_Position(1,10);
    LCD_PrintNumber(angulo);
    
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
    if (control==0)
    {
        LCD_PrintNumber(control_manual);
    }
    if (control==1)
    {
        LCD_PrintNumber(control_auto);
    }
    LCD_Position(1,0);
    LCD_PrintString("angulo:");
    LCD_Position(1,10);
    LCD_PrintNumber(angulo);
    
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

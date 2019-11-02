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
float Ts=0.005;
int16 control_manual=120;
int16 control_auto=100;
int counter=0;
int ref_counter=80;
/* seleccion de control */
int16 control=1;    
/* Variables de control */
float PkP=0.982;/*tiene lógica, probar constantes al verificar funcionamiento*/
float PkI=0.1555;
float PkD=0.02554;
float N=165.9;
volatile float error,error_anterior;
volatile float Pkp,Pki,Pkd;
volatile float Pkp_anterior=0,Pki_anterior=0,Pkd_anterior=0;;


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
        LCD_PrintNumber(counter);
        
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
    if (control==0)
    {
        LCD_PrintNumber(control_manual);
    }
    if (control==1)
    /* calculo de la salida de control automático */
    {
        error=ref_counter-counter;
        Pkp=PkP*error;
        Pki=PkI*(error+Pki_anterior);
         /*Pkd=(PkD*N*(error-error_anterior)+PkD_anterior)/(1+N*Ts);
        control_auto=Pkp+Pki+Pkd;
        control_auto=(control_auto+7.4221)/0.0481;
        Prevenciones
        if(control_auto>200){control_auto=200;}
        if(control_auto<120){control_auto=120;}*/
        
        Pkp_anterior=Pkp;
        Pki_anterior=Pki;
        Pkd_anterior=Pkd;
        error_anterior=error;
        
        control_auto=165+Pkp;
        LCD_PrintNumber(control_auto);
    }
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

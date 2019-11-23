/* ========================================
 * Implementacion de control PID para planta helicoptero 
 * ========================================
*/
#include "project.h"

#include <stdio.h>
#include <stdlib.h>

/* Declaración de variables */
float Ts=0.01; /* Periodo de muestreo de 10ms */
int16 control_manual=120;
int16 control_auto=100;
volatile float control_anterior=0;
int angulo=0;
int ref_angulo=162;
/* seleccion de control manual o automatico, 1 para auto 0 para manual */
int16 control=0;    
/* Variables de control */
float radio = 0.15;
float PkP=10;
float PkI=0.01;
float PkD=500;
volatile float error,error_anterior;
volatile float Pkp,Pki,Pkd;
volatile float Pki_anterior=0;
/*Variable de inicio para ESC*/
int ready=0;

/* Métodos de interrupción */
/* Al presionar un boton específico en psoc selecciona el modo manual */
CY_ISR(Manual_Int)
{
    if(ready==1){ 
        control=0;
        LED_Write(0);
        pot_manual_SetCounter(140);/*valor de entrada de pwm*/
    }
}
/* Al presionar un boton específico en psoc selecciona el modo auto */
CY_ISR(Automatic_Int)
{
    if(ready==1){ 
        control=1;
        LED_Write(1);
        pot_manual_SetCounter(160);/*valor de referencia de ángulo*/
    }
}
/* Realimentación del sistema */
CY_ISR(Muestreo)
{
    if(ready==1){ 

        /*****lee el dato del codificador que recibe la señal de medicion del decoder******/
        angulo=QuadDec_GetCounter();
        
        /*Actualización del controlador manual*/
        /*este modo lee directamente el valor del PWM que entra a la planta *
         *el mismo se puede modifical al girar manualmente un encoderexterno ubicado en la psoc */
        if (control==0)
        {   
            control_manual=pot_manual_GetCounter();/*lee decoder*/
            PWM_Motor_WriteCompare(control_manual);/*actualiza valor de entrada del motor al valor ubicado manualmente*/
            /*actualiza PWM con valor manual*/
            Reset_PWM_Write(1);
            Reset_PWM_Write(0);
            /*actualiza display*/
            LCD_ClearDisplay();
            LCD_Position(0,0);
            LCD_PrintString("Ctrl:");
            LCD_Position(0,5);
            LCD_PrintNumber(control_manual);        
            LCD_Position(1,0);
            LCD_PrintString("Angu:");
            LCD_Position(1,5);
            LCD_PrintNumber(angulo);
            /*indicador al usuario para saber que está en modo manual*/
            LCD_Position(0,15);
            LCD_PrintString("M");           
        }
        /*Actualiza el controlador automatico*/
        /*se implementa un controlador PID*/
        /*toma la medición de referencia, la compara con la real,y calcula la entrada del motor*/
        if (control==1)
        {      
            /*lectura de la referencia definida por el usuario*/
            ref_angulo=pot_manual_GetCounter();
            /*Cálculo de PID*/
            error=radio*(ref_angulo-angulo);
            Pkp=PkP*error;
            Pki=Pki_anterior+PkI*error;
            Pkd=PkD*(error-error_anterior)/Ts;
            control_auto= 125+Pkp+Pki+Pkd;/*suma125 para linealizar (debido al comportamiento de la planta)*/
            /* Prevenciones (prevenciones de visualizacion en psoc)*/
            if(control_auto>200){control_auto=200;}
            if(control_auto<0){control_auto=125;}
            /**Indicador LED***/
            if(control_auto<control_anterior){LED_Write(0);}
            if(control_auto>control_anterior){LED_Write(1);}
            /*actualiza PWM con valor calculado por PID*/
            PWM_Motor_WriteCompare(control_auto);
            Reset_PWM_Write(1);
            Reset_PWM_Write(0);
            /*guarda datos para el cálculo en el siguiente muestreo*/
            control_anterior=control_auto;          
            Pki_anterior=Pki;
            error_anterior=error;
            
            /*Actualiza display*/
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
/*toma en cuenta de un tiempo muerto que requieren los motores para empezar a funcionar*/
CY_ISR(inicio)
{
    ready=1;
}
/*MAIN del programa*/
int main(void)
{
    /*Se inicializan los módulos requeridos*/
    PWM_Motor_Start();
    LCD_Start();
    timer_clock_Start();
    QuadDec_Start();
    pot_manual_Start();
    Timer_Start();
    Clock_lento_Start();
    Timer_inicio_Start();
    
    /*Inicializa display*/
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
    
    CyGlobalIntEnable; 
    /* Enable global interrupts. */
    isr_Manual_StartEx(Manual_Int);
    isr_Automatic_StartEx(Automatic_Int);
    isr_Ts_StartEx(Muestreo);
    isr_inicio_StartEx(inicio);
    
    /*loop del programa*/
    for(;;)
    {
        
    }
}

/* FINAL DEL DOCUMENTO */

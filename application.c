/* 
 * File:   application.c
 * Author: Mohamed Osama
 * Description: This Application is used for Pulse Measurement it is used to 
 *              measure frequency and duty cycle of pulses using CCP1 Capture Mode 
 *              Also it uses either CCP2 PWM Mode or Compare Mode to Generate Signals to test it
 *              You can Choose which mode used to Generate Signal to test it by PreCompile Configurations 
 *              in Pulse_Meter_CFG.h file    
 *              CCP2 Compare Mode Generates 50HZ with 75% Duty Cycle Signal                   
 *              CCP2 PWM Mode Generates 1KHZ with  6% Duty Cycle Signal
 *              For Accuracy use 16MHZ Crystal and The Range of :
 *              1. Frequency : 1 -> 1000 Hz  
 *              2. Duty Cycle: 6 -> 93 %
 * 
 * Created on January 8, 2024, 1:34 PM
 */

#include "application.h"

uint8 Duty_Cycle = ZERO_INIT; // The Duty Cycle Calculated is saved in this variable
uint32 Frequency = ZERO_INIT; // The Frequency Calculated is saved in this variable
int main() 
{
    
    Pulse_Meter_Init();  // Initializes the Pulse Meter system

    Welcome_Message();  // Displays a welcome message on the LCD for the Pulse Meter project

#if (FREQUENCY_GENERATED_BY == CCP2_PWM_MODE)
    CCP_PWM_Set_Duty(&ccp2_obj,6);  // Sets the duty cycle for CCP2 PWM mode to 6%
#endif

    while(1)
    { 
        Pulse_Meter_Calculate(16,1,&Frequency,&Duty_Cycle);  // Calculates the pulse frequency and duty cycle
        Pulse_Meter_Display(Frequency,Duty_Cycle);  // Displays the pulse frequency and duty cycle on an LCD
    }
        return (EXIT_SUCCESS);
}



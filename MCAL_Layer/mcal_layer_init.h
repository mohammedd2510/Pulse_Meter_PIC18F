/* 
 * File:   mcal_layer_init.h
 * Author: Mohamed Osama
 *
 * Created on January 7, 2024, 4:46 PM
 */

#ifndef MCAL_LAYER_INIT_H
#define	MCAL_LAYER_INIT_H

/* Section : Includes */
#include "CCP/hal_ccp.h"
#include"Timer2/hal_timer2.h"
#include"Timer3/hal_timer3.h"
#include"Timer1/hal_timer1.h"
#include"../Pulse_Meter_CFG.h"
/* Section : Macros Declaration */


/* Section : Macro Functions Declaration */


/* Section : Data Types Declaration */
extern timer1_t timer1_obj;
extern timer3_t timer3_obj;
extern ccp_t ccp2_obj;
extern ccp_t ccp1_obj;

/* Section : Functions Declaration */
void Timer2_Timer_Init(void);
void Timer1_Timer_Init(void);
void Timer3_Timer_Init(void);
void CCP2_PWM_1KHZ_INIT(void);
void CCP1_Capture_Mode_Init(void);
void CCP2_COMPARE_50HZ_75Duty_INIT(void);
void CCP1_Callback_ISR(void);
void CCP2_Callback_ISR(void);
void TMR1_Callback_ISR(void);
void mcal_layer_initialize(void);
#endif	/* MCAL_LAYER_INIT_H */

/* 
 * File:   mcal_interrupt_manager.h
 * Author: Mohamed Osama
 *
 * Created on September 12, 2023, 12:37 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/* Section : Includes */
#include "mcal_interrupt_config.h"

/* Section : Macros Declaration */


/* Section : Macro Functions Declaration */


/* Section : Data Types Declaration */


/* Section : Functions Declaration */
extern volatile  uint8 RB4_pin_init_value;
extern volatile uint8 RB5_pin_init_value;
extern volatile  uint8 RB6_pin_init_value;
extern volatile  uint8 RB7_pin_init_value;

void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(void);
void RB5_ISR(void);
void RB6_ISR(void);
void RB7_ISR(void);
void ADC_ISR (void);
void TMR0_ISR (void);
void TMR1_ISR (void);
void TMR2_ISR (void);
void TMR3_ISR (void);
void CCP1_ISR(void);
void CCP2_ISR(void);
#endif	/* MCAL_INTERRUPT_MANAGER_H */


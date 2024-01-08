/* 
 * File:   mcal_internal_interrupt.h
 * Author: Mohamed Osama
 *
 * Created on September 12, 2023, 12:35 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/* Section : Includes */

#include "mcal_interrupt_config.h"
#include "../ADC/hal_adc.h"
/* Section : Macros Declaration */


/* Section : Macro Functions Declaration */

#if (ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    /* This routing clears the interrupt enable for the ADC Module */
    #define ADC_InterruptDisable() (PIE1_bits.ADIE=0)
    /* This routing sets the interrupt enable for the ADC Module */
    #define ADC_InterruptEnable() (PIE1_bits.ADIE=1)
    /* This routing clears the interrupt flag for the ADC Module */
    #define ADC_InterruptFlagClear() (PIR1_bits.ADIF=0)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 
        /* This routing sets the ADC MODULE interrupt priority to be High priority */
        #define ADC_HighPrioritySet() (IPR1_bits.ADIP=1)
        /* This routing sets the ADC MODULE interrupt priority to be Low priority */
        #define ADC_LowPrioritySet() (IPR1_bits.ADIP=0)
    #endif
#endif

#if (TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    /* This routing clears the interrupt enable for the Timer0 Module */
    #define TIMER0_InterruptDisable() (INTCON_bits.TMR0IE=0)
    /* This routing sets the interrupt enable for the Timer0 Module */
    #define TIMER0_InterruptEnable() (INTCON_bits.TMR0IE=1)
    /* This routing clears the interrupt flag for the Timer0 Module */
    #define TIMER0_InterruptFlagClear() (INTCON_bits.TMR0IF=0)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 
        /* This routing sets the Timer0 Module interrupt priority to be High priority */
        #define TIMER0_HighPrioritySet() (INTCON2_bits.TMR0IP=1)
        /* This routing sets the Timer0 Module interrupt priority to be Low priority */
        #define TIMER0_LowPrioritySet() (INTCON2_bits.TMR0IP=0)
    #endif
#endif


#if (TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    /* This routing clears the interrupt enable for the Timer1 Module */
    #define TIMER1_InterruptDisable() (PIE1_bits.TMR1IE=0)
    /* This routing sets the interrupt enable for the Timer1 Module */
    #define TIMER1_InterruptEnable() (PIE1_bits.TMR1IE=1)
    /* This routing clears the interrupt flag for the Timer1 Module */
    #define TIMER1_InterruptFlagClear() (PIR1_bits.TMR1IF=0)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 
        /* This routing sets the Timer1 Module interrupt priority to be High priority */
        #define TIMER1_HighPrioritySet() (IPR1_bits.TMR1IP=1)
        /* This routing sets the Timer1 Module interrupt priority to be Low priority */
        #define TIMER1_LowPrioritySet() (IPR1_bits.TMR1IP=0)
    #endif
#endif

#if (TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    /* This routing clears the interrupt enable for the Timer2 Module */
    #define TIMER2_InterruptDisable() (PIE1_bits.TMR2IE=0)
    /* This routing sets the interrupt enable for the Timer2 Module */
    #define TIMER2_InterruptEnable() (PIE1_bits.TMR2IE=1)
    /* This routing clears the interrupt flag for the Timer2 Module */
    #define TIMER2_InterruptFlagClear() (PIR1_bits.TMR2IF=0)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 
        /* This routing sets the Timer2 Module interrupt priority to be High priority */
        #define TIMER2_HighPrioritySet() (IPR1_bits.TMR2IP=1)
        /* This routing sets the Timer2 Module interrupt priority to be Low priority */
        #define TIMER2_LowPrioritySet() (IPR1_bits.TMR2IP=0)
    #endif
#endif

#if (TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    /* This routing clears the interrupt enable for the Timer3 Module */
    #define TIMER3_InterruptDisable() (PIE2_bits.TMR3IE=0)
    /* This routing sets the interrupt enable for the Timer3 Module */
    #define TIMER3_InterruptEnable() (PIE2_bits.TMR3IE=1)
    /* This routing clears the interrupt flag for the Timer3 Module */
    #define TIMER3_InterruptFlagClear() (PIR2_bits.TMR3IF=0)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 
        /* This routing sets the Timer3 Module interrupt priority to be High priority */
        #define TIMER3_HighPrioritySet() (IPR2_bits.TMR3IP=1)
        /* This routing sets the Timer3 Module interrupt priority to be Low priority */
        #define TIMER3_LowPrioritySet() (IPR2_bits.TMR3IP=0)
    #endif
#endif

#if ( CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE )
    /* This routing clears the interrupt enable for the CCP1 Module */
    #define CCP1_InterruptDisable() (PIE1_bits.CCP1IE=0)
    /* This routing sets the interrupt enable for the CCP1 Module */
    #define CCP1_InterruptEnable() (PIE1_bits.CCP1IE=1)
    /* This routing clears the interrupt flag for the CCP1 Module */
    #define CCP1_InterruptFlagClear() (PIR1_bits.CCP1IF=0)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 
        /* This routing sets the CCP1 Module interrupt priority to be High priority */
        #define CCP1_HighPrioritySet() (IPR1_bits.CCP1IP=1)
        /* This routing sets the CCP1 Module interrupt priority to be Low priority */
        #define CCP1_LowPrioritySet() (IPR1_bits.CCP1IP=0)
    #endif
#endif
#if ( CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE )
    /* This routing clears the interrupt enable for the CCP2 Module */
    #define CCP2_InterruptDisable() (PIE2_bits.CCP2IE=0)
    /* This routing sets the interrupt enable for the CCP2 Module */
    #define CCP2_InterruptEnable() (PIE2_bits.CCP2IE=1)
    /* This routing clears the interrupt flag for the CCP2 Module */
    #define CCP2_InterruptFlagClear() (PIR2_bits.CCP2IF=0)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 
        /* This routing sets the CCP2 Module interrupt priority to be High priority */
        #define CCP2_HighPrioritySet() (IPR2_bits.CCP2IP=1)
        /* This routing sets the CCP2 Module interrupt priority to be Low priority */
        #define CCP2_LowPrioritySet() (IPR2_bits.CCP2IP=0)
    #endif 
#endif

/* Section : Data Types Declaration */


/* Section : Functions Declaration */

#endif	/* MCAL_INTERNAL_INTERRUPT_H */


/* 
 * File:   mcal_external_interrupt.h
 * Author: Mohamed Osama
 *
 * Created on September 12, 2023, 12:36 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* Section : Includes */
#include "mcal_interrupt_config.h"

/* Section : Macros Declaration */


/* Section : Macro Functions Declaration */
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE 
/* This routing clears the interrupt enable for the external interrupt ,INT0 */
#define EXT_INT0_InterruptDisable() (INTCON_bits.INT0IE=0)
/* This routing sets the interrupt enable for the external interrupt ,INT0 */
#define EXT_INT0_InterruptEnable() (INTCON_bits.INT0IE=1)
/* This routing clears the interrupt flag for the external interrupt ,INT0 */
#define EXT_INT0_InterruptFlagClear() (INTCON_bits.INT0IF=0)
/* This routing sets the edge detect for the external interrupt INT0 to rising edge */
#define EXT_INT0_RisingEdgeSet() (INTCON2_bits.INTEDG0=1)
/* This routing sets the edge detect for the external interrupt INT0 to falling edge */
#define EXT_INT0_FallingEdgeSet() (INTCON2_bits.INTEDG0=0)

/* This routing clears the interrupt enable for the external interrupt ,INT1 */
#define EXT_INT1_InterruptDisable() (INTCON3_bits.INT1IE=0)
/* This routing sets the interrupt enable for the external interrupt ,INT1 */
#define EXT_INT1_InterruptEnable() (INTCON3_bits.INT1IE=1)
/* This routing clears the interrupt flag for the external interrupt ,INT1 */
#define EXT_INT1_InterruptFlagClear() (INTCON3_bits.INT1IF=0)
/* This routing sets the edge detect for the external interrupt INT1 to rising edge */
#define EXT_INT1_RisingEdgeSet() (INTCON2_bits.INTEDG1=1)
/* This routing sets the edge detect for the external interrupt INT1 to falling edge */
#define EXT_INT1_FallingEdgeSet() (INTCON2_bits.INTEDG1=0)

/* This routing clears the interrupt enable for the external interrupt ,INT2 */
#define EXT_INT2_InterruptDisable() (INTCON3_bits.INT2IE=0)
/* This routing sets the interrupt enable for the external interrupt ,INT2 */
#define EXT_INT2_InterruptEnable() (INTCON3_bits.INT2IE=1)
/* This routing clears the interrupt flag for the external interrupt ,INT2 */
#define EXT_INT2_InterruptFlagClear() (INTCON3_bits.INT2IF=0)
/* This routing sets the edge detect for the external interrupt INT2 to rising edge */
#define EXT_INT2_RisingEdgeSet() (INTCON2_bits.INTEDG2=1)
/* This routing sets the edge detect for the external interrupt INT2 to falling edge */
#define EXT_INT2_FallingEdgeSet() (INTCON2_bits.INTEDG2=0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 
/* This routing sets the INT1 External interrupt priority to be High priority */
#define EXT_INT1_HighPrioritySet() (INTCON3_bits.INT1IP=1)
/* This routing sets the INT1 External interrupt priority to be Low priority */
#define EXT_INT1_LowPrioritySet() (INTCON3_bits.INT1IP=0)
/* This routing sets the INT2 External interrupt priority to be High priority */
#define EXT_INT2_HighPrioritySet() (INTCON3_bits.INT2IP=1)
/* This routing sets the INT1 External interrupt priority to be Low priority */
#define EXT_INT2_LowPrioritySet() (INTCON3_bits.INT2IP=1)
#endif

#endif

#if  (EXTERNAL_INTERRUPT_OnCHANGE_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE ) 
/* This routing clears the interrupt enable for the external interrupt ,RBx */
#define EXT_RBx_InterruptDisable() (INTCON_bits.RBIE=0)
/* This routing sets the interrupt enable for the external interrupt ,RBx*/
#define EXT_RBx_InterruptEnable() (INTCON_bits.RBIE=1)
/* This routing clears the interrupt flag for the external interrupt ,RBx */
#define EXT_RBx_InterruptFlagClear() (INTCON_bits.RBIF=0)

#endif

#if ( INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE ) 
/* This routing sets the RBx External interrupt priority to be High priority */
#define EXT_RBx_HighPrioritySet() (INTCON2_bits.RBIP=1)
/* This routing sets the RBx External interrupt priority to be Low priority */
#define EXT_RBx_LowPrioritySet() (INTCON2_bits.RBIP=0)

#endif

/* Section : Data Types Declaration */



typedef enum {
    INTERRUPT_FALLING_EDGE = 0 ,
    INTERRUPT_RISING_EDGE          
}interrupt_INTx_edge;

typedef enum {
    INTERRUPT_EXTERNAL_INT0 = 0 ,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2
}interrupt_INTx_src;



typedef struct {
    void (*EXT_InterruptHandler)(void);
    pin_config_t mcu_pin;
    interrupt_INTx_edge edge ;
    interrupt_INTx_src  source ;
    interrupt_priority_cfg priority;
}interrupt_INTx_t;

typedef struct {
    void (*EXT_InterruptHandler)(void);
    pin_config_t mcu_pin;
    interrupt_priority_cfg priority;
    uint8 RBx_Pin_init_value;
}interrupt_RBx_t;

/* Section : Functions Declaration */
Std_ReturnType Interrupt_INTx_Init (const interrupt_INTx_t *int_obj);
Std_ReturnType Interrupt_INTx_DeInit (const interrupt_INTx_t *int_obj);
Std_ReturnType Interrupt_RBx_Init (const interrupt_RBx_t *int_obj);
Std_ReturnType Interrupt_RBx_DeInit (const interrupt_RBx_t *int_obj);


#endif	/* MCAL_EXTERNAL_INTERRUPT_H */


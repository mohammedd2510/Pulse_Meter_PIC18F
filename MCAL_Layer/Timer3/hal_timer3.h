/* 
 * File:   hal_timer3.h
 * Author: Mohamed Osama
 *
 * Created on November 29, 2023, 6:49 PM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/* Section : Includes */
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../mcal_std_types.h"
#include "../my_pic18f4620.h"

/* Timer3 Clock Source (Timer or Counter) */
#define TIMER3_TIMER_MODE   0
#define TIMER3_COUNTER_MODE 1
/* Timer3 External Clock Input Synchronization*/
#define TIMER3_ASYNC_COUNTER_MODE   1
#define TIMER3_SYNC_COUNTER_MODE    0

/* Timer3 Input Clock Pre-Scaler */
#define TIMER3_PRESCALER_DIV_BY_1       0U
#define TIMER3_PRESCALER_DIV_BY_2       1U
#define TIMER3_PRESCALER_DIV_BY_4       2U
#define TIMER3_PRESCALER_DIV_BY_8       3U

/* 16-Bit Read/Write Mode */
#define TIMER3_RW_REG_8BIT_MODE         0U
#define TIMER3_RW_REG_16BIT_MODE        1U

/* Section : Macro Functions Declaration */

/* Enable or Disable Timer3 Module*/
#define TIMER3_MODULE_ENABLE() (T3CON_bits.TMR3ON = 1)
#define TIMER3_MODULE_DISABLE() (T3CON_bits.TMR3ON = 0)
/* Timer3 Clock Source (Timer or Counter) */
#define TIMER3_TIMER_MODE_ENABLE() (T3CON_bits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE_ENABLE() (T3CON_bits.TMR3CS = 1)
/* Timer3 External Clock Input Synchronization*/
#define TIMER3_ASYNC_COUNTER_MODE_ENABLE() (T3CON_bits.T3SYNC = 1)
#define TIMER3_SYNC_COUNTER_MODE_ENABLE() (T3CON_bits.T3SYNC = 0)

/* Timer3 Input Clock Pre-Scaler */
#define TIMER3_PRESCALER_SELECT(_PRESCALER_)  (T3CON_bits.T3CKPS = _PRESCALER_)


/* 16-Bit Read/Write Mode */
#define TIMER3_RW_REG_8BIT_MODE_ENABLE()     (T3CON_bits.RD16= 0)    
#define TIMER3_RW_REG_16BIT_MODE_ENABLE()    (T3CON_bits.RD16= 1)

/* Section : Data Types Declaration */
typedef struct
{
    #if (TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
        void(*TMR3_InterruptHandler)(void);
        #if (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE )
        interrupt_priority_cfg priority;
        #endif
    #endif
    uint16 timer3_preload_value;
    uint8 prescaler_value       :2;
    uint8 timer3_mode           :1;
    uint8 timer3_counter_mode   :1;
    uint8 timer3_reg_wr_mode    :1;
    uint8 timer3_reserved       :3;
}timer3_t;

/* Section : Functions Declaration */
Std_ReturnType Timer3_Init(const timer3_t *_timer);
Std_ReturnType Timer3_DeInit(const timer3_t *_timer);
Std_ReturnType Timer3_Write_Value(const timer3_t *_timer , uint16 _value);
Std_ReturnType Timer3_Read_Value(const timer3_t *_timer , uint16 *_value);
/* Section : Functions Declaration */

#endif	/* HAL_TIMER3_H */


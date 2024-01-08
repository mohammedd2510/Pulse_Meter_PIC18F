/* 
 * File:   hal_timer2.h
 * Author: Mohamed Osama
 *
 * Created on November 29, 2023, 6:48 PM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/* Section : Includes */
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../mcal_std_types.h"
#include "../my_pic18f4620.h"

/* Section : Macros Declaration */

/* Timer2 Input Clock Post-Scaler */
#define TIMER2_POSTSCALER_DIV_BY_1        1U
#define TIMER2_POSTSCALER_DIV_BY_2        2U
#define TIMER2_POSTSCALER_DIV_BY_3        3U
#define TIMER2_POSTSCALER_DIV_BY_4        4U
#define TIMER2_POSTSCALER_DIV_BY_5        5U
#define TIMER2_POSTSCALER_DIV_BY_6        6U
#define TIMER2_POSTSCALER_DIV_BY_7        7U
#define TIMER2_POSTSCALER_DIV_BY_8        8U
#define TIMER2_POSTSCALER_DIV_BY_9        9U
#define TIMER2_POSTSCALER_DIV_BY_10       10U
#define TIMER2_POSTSCALER_DIV_BY_11       11U
#define TIMER2_POSTSCALER_DIV_BY_12       12U
#define TIMER2_POSTSCALER_DIV_BY_13       13U
#define TIMER2_POSTSCALER_DIV_BY_14       14U
#define TIMER2_POSTSCALER_DIV_BY_15       15U
#define TIMER2_POSTSCALER_DIV_BY_16       16U

/* Timer2 Input Clock Pre-Scaler */
#define TIMER2_PRESCALER_DIV_BY_1        0U
#define TIMER2_PRESCALER_DIV_BY_4        1U
#define TIMER2_PRESCALER_DIV_BY_16       2U


/* Section : Macro Functions Declaration */

/* Enable or Disable Timer2 Module*/
#define TIMER2_MODULE_ENABLE() (T2CON_bits.TMR2ON = 1)
#define TIMER2_MODULE_DISABLE() (T2CON_bits.TMR2ON = 0)

/* Timer2 Input Clock Pre-Scaler */
#define TIMER2_PRESCALER_SELECT(_PRESCALER_)  (T2CON_bits.T2CKPS = _PRESCALER_)

/* Timer2 Input Clock Post-Scaler */
#define TIMER2_POSTSCALER_SELECT(_POSTSCALER_)  (T2CON_bits.T2OUTPS = _POSTSCALER_)

/* Section : Data Types Declaration */
typedef struct
{
    #if (TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
        void(*TMR2_InterruptHandler)(void);
        #if (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE )
        interrupt_priority_cfg priority;
        #endif
    #endif
    uint8 timer2_preload_value;
    uint8 prescaler_value       :2;
    uint8 postscaler_value      :4;
    uint8 timer2_reserved       :2;
}timer2_t;

/* Section : Functions Declaration */
Std_ReturnType Timer2_Init(const timer2_t *_timer);
Std_ReturnType Timer2_DeInit(const timer2_t *_timer);
Std_ReturnType Timer2_Write_Value(const timer2_t *_timer , uint8 _value);
Std_ReturnType Timer2_Read_Value(const timer2_t *_timer , uint8 *_value);
#endif	/* HAL_TIMER2_H */


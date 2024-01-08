#include"hal_timer3.h"
#if (TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
InterruptHandler TMR3_InterruptHandler = NULL;
#endif
static uint16 timer3_preload;
static inline void Timer3_Mode_Select(const timer3_t *_timer);
/**
 * 
 * @param _timer
 * @return 
 */
Std_ReturnType Timer3_Init(const timer3_t *_timer)
{
     Std_ReturnType ret=E_OK;
    if(_timer==NULL){
        ret=E_NOT_OK;
    }
    else
    {
        TIMER3_MODULE_DISABLE();
        TIMER3_PRESCALER_SELECT(_timer->prescaler_value);
        Timer3_Mode_Select(_timer);
        TMR3H = (_timer->timer3_preload_value) >> 8 ;
        TMR3L = (uint8)(_timer->timer3_preload_value);
        timer3_preload = _timer->timer3_preload_value;
/*   Interrupt Configurations   */
#if (TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
        TIMER3_InterruptEnable();
        TIMER3_InterruptFlagClear();
        TMR3_InterruptHandler = _timer->TMR3_InterruptHandler;
    /*   Interrupt  Priority Configurations   */    
    #if (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE)
            INTERRUPT_PriorityLevelsDisable();
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
    #elif (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE)
            INTERRUPT_PriorityLevelsEnable();
            if(_timer->priority == INTERRUPT_HIGH_PRIORITY){
                TIMER3_HighPrioritySet();
                INTERRUPT_GlobalInterruptHighEnable();
            }
            else if(_timer->priority == INTERRUPT_LOW_PRIORITY)
            {
             TIMER3_LowPrioritySet();
             INTERRUPT_GlobalInterruptHighEnable();
             INTERRUPT_GlobalInterruptLowEnable();   
            }
    #endif 
#endif        
        TIMER3_MODULE_ENABLE();
    }
    return ret;
}
/**
 * 
 * @param _timer
 * @return 
 */
Std_ReturnType Timer3_DeInit(const timer3_t *_timer)
{
    Std_ReturnType ret=E_OK;
    if(_timer==NULL){
        ret=E_NOT_OK;
    }
    else
    {
#if (TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
        TIMER3_InterruptDisable();
#endif
        TIMER3_MODULE_DISABLE();
    }
    return ret;
}
/**
 * 
 * @param _timer
 * @param _value
 * @return 
 */
Std_ReturnType Timer3_Write_Value(const timer3_t *_timer , uint16 _value)
{
    Std_ReturnType ret=E_OK;
    if(_timer==NULL){
        ret=E_NOT_OK;
    }
    else
    {
        TMR3H = (_value)>>8;
        TMR3L = (uint8)(_value);
    }
    return ret;
}
/**
 * 
 * @param _timer
 * @param _value
 * @return 
 */
Std_ReturnType Timer3_Read_Value(const timer3_t *_timer , uint16 *_value)
{
    Std_ReturnType ret=E_OK;
    uint8 tmr3_L = ZERO_INIT , tmr3_H = ZERO_INIT ;
    if((_timer==NULL)||(_value == NULL)){
        ret=E_NOT_OK;
    }
    else
    {
        tmr3_L = TMR3L;
        tmr3_H = TMR3H;
        *_value = (uint16)((tmr3_H << 8) | tmr3_L );
    }
    return ret;
}

/**
 * 
 * @param _timer
 */
static inline void Timer3_Mode_Select(const timer3_t *_timer){
   if (TIMER3_TIMER_MODE == _timer->timer3_mode){
        TIMER3_TIMER_MODE_ENABLE();
    }
    else if (TIMER3_COUNTER_MODE == _timer->timer3_mode){
        TIMER3_COUNTER_MODE_ENABLE();
            if (TIMER3_SYNC_COUNTER_MODE == _timer->timer3_counter_mode)
            {
               TIMER3_SYNC_COUNTER_MODE_ENABLE(); 
            }
            else if (TIMER3_ASYNC_COUNTER_MODE == _timer->timer3_counter_mode)
            {
               TIMER3_ASYNC_COUNTER_MODE_ENABLE(); 
            }
            else {/*Nothing*/}
    }
    else {/*Nothing*/} 
}


void TMR3_ISR (void)
{
    TMR3H = (timer3_preload)>>8;
    TMR3L = (uint8)(timer3_preload);
    TIMER3_InterruptFlagClear();
      if(TMR3_InterruptHandler){
       TMR3_InterruptHandler();
    }
     else{ } 
}
#include"hal_timer1.h"
#if (TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
InterruptHandler TMR1_InterruptHandler = NULL;
#endif
static uint16 timer1_preload;
static inline void Timer1_Mode_Select(const timer1_t *_timer);
/**
 * 
 * @param _timer
 * @return 
 */
Std_ReturnType Timer1_Init(const timer1_t *_timer)
{
    Std_ReturnType ret=E_OK;
    if(_timer==NULL){
        ret=E_NOT_OK;
    }
    else
    {
        TIMER1_MODULE_DISABLE();
        TIMER1_PRESCALER_SELECT(_timer->prescaler_value);
        Timer1_Mode_Select(_timer);
        TMR1H = (_timer->timer1_preload_value) >> 8 ;
        TMR1L = (uint8)(_timer->timer1_preload_value);
        timer1_preload = _timer->timer1_preload_value;
/*   Interrupt Configurations   */
#if (TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
        TIMER1_InterruptEnable();
        TIMER1_InterruptFlagClear();
        TMR1_InterruptHandler = _timer->TMR1_InterruptHandler;
    /*   Interrupt  Priority Configurations   */    
    #if (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE)
            INTERRUPT_PriorityLevelsDisable();
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
    #elif (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE)
            INTERRUPT_PriorityLevelsEnable();
            if(_timer->priority == INTERRUPT_HIGH_PRIORITY){
                TIMER1_HighPrioritySet();
                INTERRUPT_GlobalInterruptHighEnable();
            }
            else if(_timer->priority == INTERRUPT_LOW_PRIORITY)
            {
             TIMER1_LowPrioritySet();
             INTERRUPT_GlobalInterruptHighEnable();
             INTERRUPT_GlobalInterruptLowEnable();   
            }
    #endif 
#endif        
        TIMER1_MODULE_ENABLE();
    }
    return ret;
}
/**
 * 
 * @param _timer
 * @return 
 */
Std_ReturnType Timer1_DeInit(const timer1_t *_timer)
{
    Std_ReturnType ret=E_OK;
    if(_timer==NULL){
        ret=E_NOT_OK;
    }
    else
    {
#if (TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
        TIMER1_InterruptDisable();
#endif
        TIMER1_MODULE_DISABLE();
    }
    return ret;
}
/**
 * 
 * @param _timer
 * @param _value
 * @return 
 */
Std_ReturnType Timer1_Write_Value(const timer1_t *_timer , uint16 _value)
{
    Std_ReturnType ret=E_OK;
    if(_timer==NULL){
        ret=E_NOT_OK;
    }
    else
    {
        TMR1H = (_value)>>8;
        TMR1L = (uint8)(_value);
    }
    return ret;
}
/**
 * 
 * @param _timer
 * @param _value
 * @return 
 */
Std_ReturnType Timer1_Read_Value(const timer1_t *_timer , uint16 *_value)
{
    Std_ReturnType ret=E_OK;
    uint8 tmr1_L = ZERO_INIT , tmr1_H = ZERO_INIT ;
    if((_timer==NULL)||(_value == NULL)){
        ret=E_NOT_OK;
    }
    else
    {
        tmr1_L = TMR1L;
        tmr1_H = TMR1H;
        *_value = (uint16)((tmr1_H << 8) | tmr1_L );
    }
    return ret;
}
void TMR1_ISR(void){
    TMR1H = (timer1_preload)>>8;
    TMR1L = (uint8)(timer1_preload);
    TIMER1_InterruptFlagClear();
      if(TMR1_InterruptHandler){
       TMR1_InterruptHandler();
    }
     else{ }
}
/**
 * 
 * @param _timer
 */
static inline void Timer1_Mode_Select(const timer1_t *_timer){
   if (TIMER1_TIMER_MODE == _timer->timer1_mode){
        TIMER1_TIMER_MODE_ENABLE();
    }
    else if (TIMER1_COUNTER_MODE == _timer->timer1_mode){
        TIMER1_COUNTER_MODE_ENABLE();
            if (TIMER1_SYNC_COUNTER_MODE == _timer->timer1_counter_mode)
            {
               TIMER1_SYNC_COUNTER_MODE_ENABLE(); 
            }
            else if (TIMER1_ASYNC_COUNTER_MODE == _timer->timer1_counter_mode)
            {
               TIMER1_ASYNC_COUNTER_MODE_ENABLE(); 
            }
            else {/*Nothing*/}
    }
    else {/*Nothing*/} 
}
#include"hal_timer2.h"

#if (TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
InterruptHandler TMR2_InterruptHandler = NULL;
#endif
static uint8 timer2_preload;

/**
 * 
 * @param _timer
 * @return 
 */
Std_ReturnType Timer2_Init(const timer2_t *_timer)
{
    Std_ReturnType ret=E_OK;
    if(_timer==NULL){
        ret=E_NOT_OK;
    }
    else
    {
        TIMER2_MODULE_DISABLE();
        TIMER2_POSTSCALER_SELECT(_timer->postscaler_value);
        TIMER2_PRESCALER_SELECT(_timer->prescaler_value);
        TMR2 = _timer->timer2_preload_value;
        timer2_preload = _timer->timer2_preload_value;
        /*   Interrupt Configurations   */
#if (TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
        TIMER2_InterruptEnable();
        TIMER2_InterruptFlagClear();
        TMR2_InterruptHandler = _timer->TMR2_InterruptHandler;
    /*   Interrupt  Priority Configurations   */    
    #if (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE)
            INTERRUPT_PriorityLevelsDisable();
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
    #elif (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE)
            INTERRUPT_PriorityLevelsEnable();
            if(_timer->priority == INTERRUPT_HIGH_PRIORITY){
                TIMER2_HighPrioritySet();
                INTERRUPT_GlobalInterruptHighEnable();
            }
            else if(_timer->priority == INTERRUPT_LOW_PRIORITY)
            {
             TIMER2_LowPrioritySet();
             INTERRUPT_GlobalInterruptHighEnable();
             INTERRUPT_GlobalInterruptLowEnable();   
            }
    #endif 
#endif        
        TIMER2_MODULE_ENABLE();
    }
    return ret;
}
/**
 * 
 * @param _timer
 * @return 
 */
Std_ReturnType Timer2_DeInit(const timer2_t *_timer)
{
    Std_ReturnType ret=E_OK;
    if(_timer==NULL){
        ret=E_NOT_OK;
    }
    else
    {
#if (TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
        TIMER2_InterruptDisable();
#endif
        TIMER2_MODULE_DISABLE();
    }
    return ret;
}
/**
 * 
 * @param _timer
 * @param _value
 * @return 
 */
Std_ReturnType Timer2_Write_Value(const timer2_t *_timer , uint8 _value)
{
    Std_ReturnType ret=E_OK;
    if(_timer==NULL){
        ret=E_NOT_OK;
    }
    else
    {
        TMR2 = _value;
    }
    return ret;
}
/**
 * 
 * @param _timer
 * @param _value
 * @return 
 */
Std_ReturnType Timer2_Read_Value(const timer2_t *_timer , uint8 *_value)
{
    Std_ReturnType ret=E_OK;
    if((_timer==NULL)||(_value == NULL)){
        ret=E_NOT_OK;
    }
    else
    {
        *_value =TMR2;
    }
    return ret;
}

void TMR2_ISR(void){
    TMR2 = timer2_preload;
    #if (TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    TIMER2_InterruptFlagClear();
      if(TMR2_InterruptHandler){
       TMR2_InterruptHandler();
    }
     else{ }
    #endif
}

#include "mcal_internal_interrupt.h"

void ADC_ISR(void){
  #if (ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
       ADC_InterruptFlagClear();
      if(ADC_InterruptHandler){
       ADC_InterruptHandler();
    }
     else{ }
   #endif
   
}

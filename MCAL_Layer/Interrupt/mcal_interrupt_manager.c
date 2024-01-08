#include "mcal_interrupt_manager.h"
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 
void __interrupt() InterruptManagerHigh(void){
    if((INTERRUPT_ENABLE == INTCON_bits.INT0IE)&&(INTERRUPT_OCCUR == INTCON_bits.INT0IF)){
        INT0_ISR();
    }
    else {/*Nothing*/}
     if((INTERRUPT_PRIORITY_HIGH == INTCON3_bits.INT1IP)&&(INTERRUPT_OCCUR == INTCON3_bits.INT1IF)){
        INT1_ISR();
    }
    else {/*Nothing*/}
    if((INTERRUPT_PRIORITY_HIGH == INTCON3_bits.INT2IP)&&(INTERRUPT_OCCUR == INTCON3_bits.INT2IF)){
        INT2_ISR();
    }
    else {/*Nothing*/}
     if((INTERRUPT_PRIORITY_HIGH == INTCON2_bits.RBIP)&&(INTERRUPT_OCCUR == INTCON_bits.RBIF) && ((GET_BIT(PORTB,4))!=RB4_pin_init_value)){
        RB4_pin_init_value^=1;
        RB4_ISR();
    }
    else {/*Nothing*/}
       if((INTERRUPT_PRIORITY_HIGH == INTCON2_bits.RBIP)&&(INTERRUPT_OCCUR == INTCON_bits.RBIF) && ((GET_BIT(PORTB,5))!=RB5_pin_init_value)){
        RB5_pin_init_value^=1;
        RB5_ISR();
    }
    else {/*Nothing*/}
       if((INTERRUPT_PRIORITY_HIGH == INTCON2_bits.RBIP)&&(INTERRUPT_OCCUR == INTCON_bits.RBIF) && ((GET_BIT(PORTB,6))!=RB6_pin_init_value)){
        RB6_pin_init_value^=1;
        RB6_ISR();
    }
    else {/*Nothing*/}
       if((INTERRUPT_PRIORITY_HIGH == INTCON2_bits.RBIP)&&(INTERRUPT_OCCUR == INTCON_bits.RBIF) && ((GET_BIT(PORTB,7))!=RB7_pin_init_value)){
        RB7_pin_init_value^=1;
        RB7_ISR();
    }
    else {/*Nothing*/}
    if((INTERRUPT_PRIORITY_HIGH == IPR1_bits.ADIP)&&(INTERRUPT_OCCUR == PIR1_bits.ADIF)){
        ADC_ISR();
    }
    else {/*Nothing*/}
    if((INTERRUPT_PRIORITY_HIGH == INTCON2_bits.TMR0IP)&&(INTERRUPT_OCCUR == INTCON_bits.TMR0IF)){
        TMR0_ISR();
    }
    else {/*Nothing*/}
    if((INTERRUPT_PRIORITY_HIGH == IPR1_bits.TMR1IP)&&(INTERRUPT_OCCUR == PIR1_bits.TMR1IF)){
        TMR1_ISR();
    }
    else {/*Nothing*/}
    if((INTERRUPT_PRIORITY_HIGH == IPR1_bits.TMR2IP)&&(INTERRUPT_OCCUR == PIR1_bits.TMR2IF)){
        TMR2_ISR();
    }
    else {/*Nothing*/}
    if((INTERRUPT_PRIORITY_HIGH == IPR2_bits.TMR3IP)&&(INTERRUPT_OCCUR == PIR2_bits.TMR3IF)){
        TMR3_ISR();
    }
    else {/*Nothing*/}
    if((INTERRUPT_PRIORITY_HIGH == IPR1_bits.CCP1IP)&&(INTERRUPT_OCCUR == PIR1_bits.CCP1IF)){
        CCP1_ISR();
    }
    else {/*Nothing*/}
      if((INTERRUPT_PRIORITY_HIGH == IPR2_bits.CCP2IP)&&(INTERRUPT_OCCUR == PIR2_bits.CCP2IF)){
        CCP2_ISR();
    }
    else {/*Nothing*/}
}
void __interrupt(low_priority) InterruptManagerLow(void){
      if((INTERRUPT_PRIORITY_LOW == INTCON3_bits.INT1IP)&&(INTERRUPT_OCCUR == INTCON3_bits.INT1IF)){
        INT1_ISR();
    }
    else {/*Nothing*/}
    if((INTERRUPT_PRIORITY_LOW == INTCON3_bits.INT2IP)&&(INTERRUPT_OCCUR == INTCON3_bits.INT2IF)){
        INT2_ISR();
    }
    else {/*Nothing*/}
     if((INTERRUPT_PRIORITY_LOW == INTCON2_bits.RBIP)&&(INTERRUPT_OCCUR == INTCON_bits.RBIF) && ((GET_BIT(PORTB,4))!=RB4_pin_init_value)){
        RB4_pin_init_value^=1;
        RB4_ISR();
    }
    else {/*Nothing*/}
       if((INTERRUPT_PRIORITY_LOW == INTCON2_bits.RBIP)&&(INTERRUPT_OCCUR == INTCON_bits.RBIF) && ((GET_BIT(PORTB,5))!=RB5_pin_init_value)){
        RB5_pin_init_value^=1;
        RB5_ISR();
    }
    else {/*Nothing*/}
       if((INTERRUPT_PRIORITY_LOW == INTCON2_bits.RBIP)&&(INTERRUPT_OCCUR == INTCON_bits.RBIF) && ((GET_BIT(PORTB,6))!=RB6_pin_init_value)){
        RB6_pin_init_value^=1;
        RB6_ISR();
    }
    else {/*Nothing*/}
       if((INTERRUPT_PRIORITY_LOW == INTCON2_bits.RBIP)&&(INTERRUPT_OCCUR == INTCON_bits.RBIF) && ((GET_BIT(PORTB,7))!=RB7_pin_init_value)){
        RB7_pin_init_value^=1;
        RB7_ISR();
    }
    else {/*Nothing*/}
     if((INTERRUPT_PRIORITY_LOW == IPR1_bits.ADIP)&&(INTERRUPT_OCCUR == PIR1_bits.ADIF)){
        ADC_ISR();
    }
    else {/*Nothing*/}
    if((INTERRUPT_PRIORITY_LOW == INTCON2_bits.TMR0IP)&&(INTERRUPT_OCCUR == INTCON_bits.TMR0IF)){
        TMR0_ISR();
    }
    else {/*Nothing*/}
    if((INTERRUPT_PRIORITY_LOW == IPR1_bits.TMR1IP)&&(INTERRUPT_OCCUR == PIR1_bits.TMR1IF)){
        TMR1_ISR();
    }
    else {/*Nothing*/}
      if((INTERRUPT_PRIORITY_LOW == IPR1_bits.TMR2IP)&&(INTERRUPT_OCCUR == PIR1_bits.TMR2IF)){
        TMR2_ISR();
    }
    else {/*Nothing*/}
     if((INTERRUPT_PRIORITY_LOW == IPR2_bits.TMR3IP)&&(INTERRUPT_OCCUR == PIR2_bits.TMR3IF)){
        TMR3_ISR();
    }
    else {/*Nothing*/} 
      if((INTERRUPT_PRIORITY_LOW == IPR1_bits.CCP1IP)&&(INTERRUPT_OCCUR == PIR1_bits.CCP1IF)){
        CCP1_ISR();
    }
    else {/*Nothing*/}
      if((INTERRUPT_PRIORITY_LOW == IPR2_bits.CCP2IP)&&(INTERRUPT_OCCUR == PIR2_bits.CCP2IF)){
        CCP2_ISR();
    }
    else {/*Nothing*/}
}
#else
void __interrupt() InterruptManager(void){
    if((INTERRUPT_ENABLE == INTCON_bits.INT0IE)&&(INTERRUPT_OCCUR == INTCON_bits.INT0IF)){
        INT0_ISR();
    }
    else {/*Nothing*/}
    if((INTERRUPT_ENABLE == INTCON3_bits.INT1IE)&&(INTERRUPT_OCCUR == INTCON3_bits.INT1IF)){
        INT1_ISR();
    }
    else {/*Nothing*/}
    if((INTERRUPT_ENABLE == INTCON3_bits.INT2IE)&&(INTERRUPT_OCCUR == INTCON3_bits.INT2IF)){
        INT2_ISR();
    }
    else {/*Nothing*/}
    if((INTERRUPT_ENABLE == INTCON_bits.RBIE)&&(INTERRUPT_OCCUR == INTCON_bits.RBIF) && ((GET_BIT(PORTB,4))!=RB4_pin_init_value)){
        RB4_pin_init_value^=1;
        RB4_ISR();
    }
    else {/*Nothing*/}
       if((INTERRUPT_ENABLE == INTCON_bits.RBIE)&&(INTERRUPT_OCCUR == INTCON_bits.RBIF) && ((GET_BIT(PORTB,5))!=RB5_pin_init_value)){
        RB5_pin_init_value^=1;
        RB5_ISR();
    }
    else {/*Nothing*/}
       if((INTERRUPT_ENABLE == INTCON_bits.RBIE)&&(INTERRUPT_OCCUR == INTCON_bits.RBIF) && ((GET_BIT(PORTB,6))!=RB6_pin_init_value)){
        RB6_pin_init_value^=1;
        RB6_ISR();
    }
    else {/*Nothing*/}
       if((INTERRUPT_ENABLE == INTCON_bits.RBIE)&&(INTERRUPT_OCCUR == INTCON_bits.RBIF) && ((GET_BIT(PORTB,7))!=RB7_pin_init_value)){
        RB7_pin_init_value^=1;
        RB7_ISR();
    }
    else {/*Nothing*/}
     if((INTERRUPT_ENABLE== PIE1_bits.ADIE)&&(INTERRUPT_OCCUR == PIR1_bits.ADIF)){
        ADC_ISR();
    }
    else {/*Nothing*/}
       if((INTERRUPT_ENABLE == INTCON_bits.TMR0IE)&&(INTERRUPT_OCCUR == INTCON_bits.TMR0IF)){
        TMR0_ISR();
    }
    else {/*Nothing*/}
    if((INTERRUPT_ENABLE == PIE1_bits.TMR1IE)&&(INTERRUPT_OCCUR ==PIR1_bits.TMR1IF)){
        TMR1_ISR();
    }
    else {/*Nothing*/}
    if((INTERRUPT_ENABLE == PIE1_bits.TMR2IE)&&(INTERRUPT_OCCUR ==PIR1_bits.TMR2IF)){
        TMR2_ISR();
    }
    else {/*Nothing*/}
    if((INTERRUPT_ENABLE == PIE2_bits.TMR3IE)&&(INTERRUPT_OCCUR ==PIR2_bits.TMR3IF)){
        TMR3_ISR();
    }
    else {/*Nothing*/}
    if((INTERRUPT_ENABLE == PIE1_bits.CCP1IE)&&(INTERRUPT_OCCUR ==PIR1_bits.CCP1IF)){
        CCP1_ISR();
    }
    else {/*Nothing*/}
    if((INTERRUPT_ENABLE == PIE2_bits.CCP2IE)&&(INTERRUPT_OCCUR ==PIR2_bits.CCP2IF)){
        CCP2_ISR();
    }
    else {/*Nothing*/}
}
#endif
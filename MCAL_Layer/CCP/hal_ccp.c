#include"hal_ccp.h"
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED))
static Std_ReturnType CCP_Capture_Mode_Init(const ccp_t * _ccp_obj );
#endif
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED))
static Std_ReturnType CCP_Compare_Mode_Init(const ccp_t * _ccp_obj );
#endif
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED))
static Std_ReturnType CCP_PWM_Mode_Init(const ccp_t * _ccp_obj );
#endif
#if ( CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE )
static Std_ReturnType CCP1_Interrupt_Init(const ccp_t * _ccp_obj );
InterruptHandler CCP1_InterruptHandler = NULL;
#endif
#if ( CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE )
static Std_ReturnType CCP2_Interrupt_Init(const ccp_t * _ccp_obj );
InterruptHandler CCP2_InterruptHandler = NULL;
#endif
#if ((CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE )|| ( CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE ))
static Std_ReturnType CCP_Interrupt_Init(const ccp_t * _ccp_obj );
#endif
void CCP1_ISR(void);
void CCP2_ISR(void);
static Std_ReturnType CCP_Capture_Compare_Timer_Config(const ccp_t * _ccp_obj);

Std_ReturnType CCP_Init(const ccp_t * _ccp_obj){
    Std_ReturnType ret=E_OK;
    if(_ccp_obj==NULL)
    {
        ret=E_NOT_OK;
    }
    else
    {
        /* CCP Module Disable */
        if (_ccp_obj->ccp_inst == CCP1_INST){
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
        }
        else if (_ccp_obj->ccp_inst == CCP2_INST){
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
        }
        else {ret = E_NOT_OK;}
        /* CCP Mode Initialization */
        switch(_ccp_obj->ccp_mode)
        {
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED))
            case CCP_CAPTURE_MODE_SELECTED:
                /* CCP Capture Mode Initialization */
                ret &= CCP_Capture_Mode_Init(_ccp_obj);
                break;
#endif   
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED))
            case CCP_COMPARE_MODE_SELECTED:
                /* CCP Compare Mode Initialization */
                ret &= CCP_Compare_Mode_Init(_ccp_obj);
                break;
#endif
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED))
            case CCP_PWM_MODE_SELECTED:
                /* CCP PWM Mode Initialization */
                ret &= CCP_PWM_Mode_Init(_ccp_obj);
                break;
#endif
            default: ret=E_NOT_OK;    
        }
            /* CCP Pin Configurations Initialization */
        ret &= gpio_pin_initialize(&(_ccp_obj->ccp_pin));
                /* Interrupt Configurations */
#if ((CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE )|| ( CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE ))
       ret&= CCP_Interrupt_Init(_ccp_obj);
#endif
    }
    return ret;
}
Std_ReturnType CCP_DeInit(const ccp_t * _ccp_obj)
{
    Std_ReturnType ret=E_OK;
    if(_ccp_obj==NULL)
    {
        ret=E_NOT_OK;
    }
    else
    {
        /* CCP Module Disable */
        if (_ccp_obj->ccp_inst == CCP1_INST){
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
#if ( CCP_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE )
            CCP1_InterruptDisable();     
#endif
        }
        else if (_ccp_obj->ccp_inst == CCP2_INST)
        {
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
#if ( CCP_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE )
            CCP2_InterruptDisable();     
 #endif
        }
        else {ret = E_NOT_OK;}

    }
    return ret;
}

#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED))
Std_ReturnType CCP_IsCapturedDataReady (const ccp_t * _ccp_obj, uint8 * _capture_status){
    Std_ReturnType ret=E_OK;
    if( (_capture_status==NULL) || (_ccp_obj == NULL) )
    {
        ret=E_NOT_OK;
    }
    else
    {
        if (_ccp_obj->ccp_inst == CCP1_INST)
        {
            if (CCP_CAPTURE_READY == CCP1_INT_FLAG)
            {
                *_capture_status =CCP_CAPTURE_READY;
                CCP1_InterruptFlagClear();
            }
            else if (CCP_CAPTURE_NOT_READY == CCP1_INT_FLAG)
            {
                *_capture_status =CCP_CAPTURE_NOT_READY;
            }
            else { ret = E_NOT_OK;}
        }
        else if (_ccp_obj->ccp_inst == CCP2_INST)
        {
            if (CCP_CAPTURE_READY == CCP2_INT_FLAG)
            {
                *_capture_status =CCP_CAPTURE_READY;
                CCP2_InterruptFlagClear();
            }
            else if (CCP_CAPTURE_NOT_READY == CCP2_INT_FLAG)
            {
                *_capture_status =CCP_CAPTURE_NOT_READY;
            }
            else { ret = E_NOT_OK;}
        }
        else {ret = E_NOT_OK;}
    }
    return ret;
}
Std_ReturnType CCP_Capture_Mode_Read_Value (const ccp_t * _ccp_obj, uint32 * capture_value)
{
    Std_ReturnType ret=E_OK;
    CCP_REG_T capture_temp_value = {ZERO_INIT};
    if( (capture_value==NULL) || (_ccp_obj == NULL) )
    {
        ret=E_NOT_OK;
    }
    else
    {
        if (_ccp_obj->ccp_inst == CCP1_INST)
        { 
           capture_temp_value.ccpr_low  = CCPR1L;
           capture_temp_value.ccpr_high = CCPR1H;  
        }
        else if (_ccp_obj->ccp_inst == CCP2_INST)
        {
           capture_temp_value.ccpr_low  = CCPR2L;
           capture_temp_value.ccpr_high = CCPR2H;   
        }
        else {ret = E_NOT_OK;}
        *capture_value = capture_temp_value.ccpr_16Bit;
    }
    return ret;
}
#endif

#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED))
/**
 * 
 * @param _ccp_obj
 * @param _compare_status
 * @return 
 */
Std_ReturnType CCP_IsCompareComplete (const ccp_t * _ccp_obj, uint8 * _compare_status)
{
   Std_ReturnType ret=E_OK;
     if( (_compare_status==NULL) || (_ccp_obj == NULL) )
    {
        ret=E_NOT_OK;
    }
    else
    {
        if (_ccp_obj->ccp_inst == CCP1_INST)
        {
            if (CCP_COMPARE_READY == CCP1_INT_FLAG)
            {
                *_compare_status =CCP_COMPARE_READY;
                CCP1_InterruptFlagClear();
            }
            else if (CCP_COMPARE_NOT_READY == CCP1_INT_FLAG)
            {
                *_compare_status =CCP_COMPARE_NOT_READY;
            }
            else { ret = E_NOT_OK;}
        }
        else if (_ccp_obj->ccp_inst == CCP2_INST)
        {
           if (CCP_COMPARE_READY == CCP2_INT_FLAG)
            {
                *_compare_status =CCP_COMPARE_READY;
                CCP1_InterruptFlagClear();
            }
            else if (CCP_COMPARE_NOT_READY == CCP2_INT_FLAG)
            {
                *_compare_status =CCP_COMPARE_NOT_READY;
            }
            else { ret = E_NOT_OK;}  
        }
        else {ret = E_NOT_OK;}
    }
    return ret; 
}
Std_ReturnType CCP_Compare_Mode_Set_Value (const ccp_t * _ccp_obj, uint16 compare_value)
{
    Std_ReturnType ret=E_OK;
    CCP_REG_T compare_temp_value = {ZERO_INIT};
    if(_ccp_obj==NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        compare_temp_value.ccpr_16Bit = compare_value;
        if (_ccp_obj->ccp_inst == CCP1_INST)
        {
            CCPR1L =compare_temp_value.ccpr_low;
            CCPR1H =compare_temp_value.ccpr_high;
        }
        else if (_ccp_obj->ccp_inst == CCP2_INST)
        {
            CCPR2L =compare_temp_value.ccpr_low;
            CCPR2H =compare_temp_value.ccpr_high;
        }
        else {ret = E_NOT_OK;}
    }
    return ret;    
}
#endif

#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED))
Std_ReturnType CCP_PWM_Set_Duty(const ccp_t * _ccp_obj, const uint8 _duty)
{
    Std_ReturnType ret=E_OK;
    uint16 l_duty_temp = ZERO_INIT;
    if(_ccp_obj==NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        l_duty_temp = (uint16) ( ((4*(PR2+1)))*(_duty/100.0) );
        if (_ccp_obj->ccp_inst == CCP1_INST)
        {
            CCP1CON_bits.DC1B =  (uint8)(l_duty_temp & 0x03);
            CCPR1L = (uint8)(l_duty_temp >> 2);
            
        }
        else if (_ccp_obj->ccp_inst == CCP2_INST)
        {
           CCP2CON_bits.DC2B =  (uint8)(l_duty_temp & 0x03);
           CCPR2L = (uint8)(l_duty_temp >> 2);  
        }
        else {ret = E_NOT_OK;}
    }
    return ret;   
}
Std_ReturnType CCP_PWM_Start(const ccp_t * _ccp_obj)
{
    Std_ReturnType ret=E_OK;
    if(_ccp_obj==NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if (_ccp_obj->ccp_inst == CCP1_INST)
        {
           CCP1_SET_MODE(CCP_PWM_MODE);  
        }
        else if (_ccp_obj->ccp_inst == CCP2_INST)
        {
           CCP2_SET_MODE(CCP_PWM_MODE);
        }
        else {ret = E_NOT_OK;}
    }
    return ret;    
}
Std_ReturnType CCP_PWM_Stop(const ccp_t * _ccp_obj)
{
    Std_ReturnType ret=E_OK;
    if(_ccp_obj==NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if (_ccp_obj->ccp_inst == CCP1_INST)
        {
           CCP1_SET_MODE(CCP_MODULE_DISABLE);  
        }
        else if (_ccp_obj->ccp_inst == CCP2_INST)
        {
           CCP2_SET_MODE(CCP_MODULE_DISABLE);
        }
        else {ret = E_NOT_OK;}
    }
    return ret;      
}
#endif

#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED))
static Std_ReturnType CCP_Capture_Mode_Init(const ccp_t * _ccp_obj )
{
    Std_ReturnType ret = E_OK;
    if (NULL == _ccp_obj)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        CCP_Capture_Compare_Timer_Config(_ccp_obj);
        if (_ccp_obj->ccp_inst == CCP1_INST)
        {
            switch (_ccp_obj->ccp_mode_variant)
            {
            case CCP_CAPTURE_MODE_1_FALLING_EDGE :
                CCP1_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);
                break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE:
                CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE:
                CCP1_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE:
                CCP1_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);
                break;
            default: ret = E_NOT_OK;    
            }   
        }
        else if (_ccp_obj->ccp_inst == CCP2_INST)
        {
            switch (_ccp_obj->ccp_mode_variant)
            {
            case CCP_CAPTURE_MODE_1_FALLING_EDGE :
                CCP2_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);
                break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE:
                CCP2_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE:
                CCP2_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE:
                CCP2_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);
                break;
            default: ret = E_NOT_OK;    
            }   
        }
        else {ret = E_NOT_OK;}
        
    }
    return ret;
}
#endif

#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED))
static Std_ReturnType CCP_Compare_Mode_Init(const ccp_t * _ccp_obj )
{
    Std_ReturnType ret = E_OK;
    if (NULL == _ccp_obj)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        CCP_Capture_Compare_Timer_Config(_ccp_obj);
        if (_ccp_obj->ccp_inst == CCP1_INST)
        {
            switch (_ccp_obj->ccp_mode_variant)
            {
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH :
                CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);
                break;
            case CCP_COMPARE_MODE_SET_PIN_HIGH:
                CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
                break;
            case CCP_COMPARE_MODE_SET_PIN_LOW:
                CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
                break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT:
                CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);
                break;
            case CCP_COMPARE_MODE_GEN_EVENT:
                CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);
                break;
            default: ret = E_NOT_OK;    
            }  
        }
        else if (_ccp_obj->ccp_inst == CCP2_INST)
        {
            switch (_ccp_obj->ccp_mode_variant)
            {
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH :
                CCP2_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);
                break;
            case CCP_COMPARE_MODE_SET_PIN_HIGH:
                CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
                break;
            case CCP_COMPARE_MODE_SET_PIN_LOW:
                CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
                break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT:
                CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);
                break;
            case CCP_COMPARE_MODE_GEN_EVENT:
                CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);
                break;
            default: ret = E_NOT_OK;    
            }
        }
        else {ret = E_NOT_OK;}
    }
    return ret;
}
#endif

#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED))
static Std_ReturnType CCP_PWM_Mode_Init(const ccp_t * _ccp_obj )
{
    Std_ReturnType ret = E_OK;
    if (NULL == _ccp_obj)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        if (_ccp_obj->ccp_inst == CCP1_INST)
        {
            if(CCP_PWM_MODE ==_ccp_obj->ccp_mode_variant)
            {   
            CCP1_SET_MODE(CCP_PWM_MODE);
            }
            else 
            { 
            ret = E_NOT_OK;  
            }   
        }
        else if (_ccp_obj->ccp_inst == CCP2_INST)
        {
            if(CCP_PWM_MODE ==_ccp_obj->ccp_mode_variant)
            {   
            CCP2_SET_MODE(CCP_PWM_MODE);
            }
            else 
            { 
            ret = E_NOT_OK;  
            }   
        }
        else {ret = E_NOT_OK;}
         /* Initializing PWM Frequency */
         PR2 = (uint8)((_XTAL_FREQ/(_ccp_obj->PWM_Frequency * _ccp_obj->Timer2_Prescaler_Value * 4))-1);
    }
    return ret;
}
#endif
static Std_ReturnType CCP_Capture_Compare_Timer_Config(const ccp_t * _ccp_obj)
{
   Std_ReturnType ret = E_OK;
    if (NULL == _ccp_obj)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        if (_ccp_obj->ccp_capt_comp_timer == CCP1_CCP2_TIMER1)
        {
            CCP_CAPT_COMP_TIMER_SELECT(CCP1_CCP2_TIMER1);
        }
        else if (_ccp_obj->ccp_capt_comp_timer == CCP1_TIMER1_CCP2_TIMER3)
        {
            CCP_CAPT_COMP_TIMER_SELECT(CCP1_TIMER1_CCP2_TIMER3);
        }
        else if (_ccp_obj->ccp_capt_comp_timer == CCP1_CCP2_TIMER3)
        {
            CCP_CAPT_COMP_TIMER_SELECT(CCP1_CCP2_TIMER3);
        }
        else {ret = E_NOT_OK;}
    }
   return ret;
}

#if ( CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE )
static Std_ReturnType CCP1_Interrupt_Init(const ccp_t * _ccp_obj )
{
    Std_ReturnType ret=E_OK;
    if(_ccp_obj==NULL)
    {
        ret=E_NOT_OK;
    }
    else
    {
        CCP1_InterruptEnable();
        CCP1_InterruptFlagClear();
        CCP1_InterruptHandler = _ccp_obj->CCP_Interrupt_Handler;
    /*   Interrupt  Priority Configurations   */    
    #if (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE)
            INTERRUPT_PriorityLevelsDisable();
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
    #elif (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE)
            INTERRUPT_PriorityLevelsEnable();
            if(_ccp_obj->priority == INTERRUPT_HIGH_PRIORITY){
                CCP1_HighPrioritySet();
                INTERRUPT_GlobalInterruptHighEnable();
            }
            else if(_ccp_obj->priority == INTERRUPT_LOW_PRIORITY)
            {
             CCP1_LowPrioritySet();
             INTERRUPT_GlobalInterruptHighEnable();
             INTERRUPT_GlobalInterruptLowEnable();   
            }
            else {ret = E_NOT_OK;}
    #endif 
    }
    return ret;
}
#endif

#if ( CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE )
static Std_ReturnType CCP2_Interrupt_Init(const ccp_t * _ccp_obj )
{
    Std_ReturnType ret=E_OK;
    if(_ccp_obj==NULL)
    {
        ret=E_NOT_OK;
    }
    else
    {
        CCP2_InterruptEnable();
        CCP2_InterruptFlagClear();
        CCP2_InterruptHandler = _ccp_obj->CCP_Interrupt_Handler;
    /*   Interrupt  Priority Configurations   */    
    #if (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE)
            INTERRUPT_PriorityLevelsDisable();
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
    #elif (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE)
            INTERRUPT_PriorityLevelsEnable();
            if(_ccp_obj->priority == INTERRUPT_HIGH_PRIORITY){
                CCP2_HighPrioritySet();
                INTERRUPT_GlobalInterruptHighEnable();
            }
            else if(_ccp_obj->priority == INTERRUPT_LOW_PRIORITY)
            {
             CCP2_LowPrioritySet();
             INTERRUPT_GlobalInterruptHighEnable();
             INTERRUPT_GlobalInterruptLowEnable();   
            }
            else {ret = E_NOT_OK;}
    #endif 
    }
    return ret;
}
#endif

#if ((CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE )|| ( CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE ))
static Std_ReturnType CCP_Interrupt_Init(const ccp_t * _ccp_obj )
{
    Std_ReturnType ret=E_OK;
    if(_ccp_obj==NULL)
    {
        ret=E_NOT_OK;
    }
    else
    {
     switch (_ccp_obj->ccp_inst){
#if ( CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE )
            case CCP1_INST:CCP1_Interrupt_Init(_ccp_obj);
                break;
#endif  
#if ( CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE )
            case CCP2_INST:CCP2_Interrupt_Init(_ccp_obj);
                break;
#endif
            default: ret = E_NOT_OK;
        }   
    }
    return ret;
}
#endif


void CCP1_ISR(void)
{
    #if (CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    CCP1_InterruptFlagClear();
      if(CCP1_InterruptHandler){
       CCP1_InterruptHandler();
    }
     else{ /* Nothing */}
    #endif
}
void CCP2_ISR(void)
{
    #if (CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    CCP2_InterruptFlagClear();
      if(CCP2_InterruptHandler){
       CCP2_InterruptHandler();
    }
     else{ /* Nothing */}
    #endif
}

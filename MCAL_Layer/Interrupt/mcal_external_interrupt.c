#include "mcal_external_interrupt.h"

static InterruptHandler  INT0_InterruptHandler =NULL;
static InterruptHandler  INT1_InterruptHandler =NULL;
static InterruptHandler  INT2_InterruptHandler =NULL;

static InterruptHandler  RB4_InterruptHandler =NULL;
static InterruptHandler  RB5_InterruptHandler =NULL;
static InterruptHandler  RB6_InterruptHandler =NULL;
static InterruptHandler  RB7_InterruptHandler =NULL;

volatile  uint8 RB4_pin_init_value = 0;
volatile  uint8 RB5_pin_init_value = 0;
volatile  uint8 RB6_pin_init_value = 0;
volatile  uint8 RB7_pin_init_value = 0;

static Std_ReturnType Interrupt_INTx_Enable (const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable (const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init (const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init (const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init (const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag (const interrupt_INTx_t *int_obj);

static Std_ReturnType INT0_SetInterruptHandler (void (*InterruptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler (void (*InterruptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler (void (*InterruptHandler)(void));
static Std_ReturnType Interrupt_INTx_SetInterruptHandler (const interrupt_INTx_t *int_obj );

static Std_ReturnType Interrupt_RBx_Enable (const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Disable (const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Priority_Init (const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init (const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_SetInterruptHandler (const interrupt_RBx_t *int_obj );
static Std_ReturnType Interrupt_RBx_set_pin_init_value (const interrupt_RBx_t *int_obj );
static Std_ReturnType RB4_SetInterruptHandler (void (*InterruptHandler)(void));
static Std_ReturnType RB5_SetInterruptHandler (void (*InterruptHandler)(void));
static Std_ReturnType RB6_SetInterruptHandler (void (*InterruptHandler)(void));
static Std_ReturnType RB7_SetInterruptHandler (void (*InterruptHandler)(void));
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_Init (const interrupt_INTx_t *int_obj){
    Std_ReturnType ret=E_OK;
    if(int_obj==NULL){
        ret=E_NOT_OK;
    }
    else{
        /* Disable the External Interrupt */
        ret = Interrupt_INTx_Disable(int_obj);
        /* Clear Interrupt Flag */
        ret &= Interrupt_INTx_Clear_Flag(int_obj);
        /* Configure External Interrupt Edge */
        ret &= Interrupt_INTx_Edge_Init(int_obj);
        #if (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE)
        /* Configure External Interrupt Priority */
        ret &= Interrupt_INTx_Priority_Init(int_obj);
        #endif
        /* Configure External Interrupt I/O Pin */
        ret &= Interrupt_INTx_Pin_Init(int_obj);
        /* Configure Default Interrupt CallBack */
        ret &= Interrupt_INTx_SetInterruptHandler(int_obj);
        /* Enable The External Interrupt*/
        ret &= Interrupt_INTx_Enable(int_obj);
        }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_DeInit (const interrupt_INTx_t *int_obj){
    Std_ReturnType ret=E_OK;
    if(int_obj==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret = Interrupt_INTx_Disable(int_obj);
        }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_Init (const interrupt_RBx_t *int_obj){
    Std_ReturnType ret=E_OK;
    if(int_obj==NULL){
        ret=E_NOT_OK;
    }
    else{
         /* Disable the External Interrupt */
        ret=Interrupt_RBx_Disable(int_obj);
        /* Clear Interrupt Flag */
         EXT_RBx_InterruptFlagClear();
        #if (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE)
        /* Configure External Interrupt Priority */
        ret &= Interrupt_RBx_Priority_Init(int_obj);
        #endif
        /* Configure External Interrupt I/O Pin */
        ret &= Interrupt_RBx_Pin_Init(int_obj);
        /* Configure Default Interrupt CallBack */
        ret &= Interrupt_RBx_SetInterruptHandler(int_obj);
        /* Configure RBx pin init value */
        ret &= Interrupt_RBx_set_pin_init_value(int_obj);
        /* Enable The External Interrupt*/
        ret &= Interrupt_RBx_Enable(int_obj);
        }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_DeInit (const interrupt_RBx_t *int_obj){
    Std_ReturnType ret=E_OK;
    if(int_obj==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret = Interrupt_RBx_Disable(int_obj);
        }
    return ret;
}
/*******************ISR Functions*************************/
void INT0_ISR(void){
    /* The INT0 external interrupt occurred (must be cleared in software )*/
    EXT_INT0_InterruptFlagClear();
    /* Code */
    
    /* CallBack Function gets called every time this ISR executes*/
    if(INT0_InterruptHandler){INT0_InterruptHandler();}
}
void INT1_ISR(void){
    /* The INT1 external interrupt occurred (must be cleared in software )*/
    EXT_INT1_InterruptFlagClear();
    /* Code */
    
    /* CallBack Function gets called every time this ISR executes*/
    if(INT1_InterruptHandler){INT1_InterruptHandler();}
}
void INT2_ISR(void){
    /* The INT2 external interrupt occurred (must be cleared in software )*/
    EXT_INT2_InterruptFlagClear();
    /* Code */
    
    /* CallBack Function gets called every time this ISR executes*/
    if(INT2_InterruptHandler){INT2_InterruptHandler();}
}
void RB4_ISR(void){
    /* The RB4 external interrupt occurred (must be cleared in software )*/
    EXT_RBx_InterruptFlagClear();
    /* Code */
    
    /* CallBack Function gets called every time this ISR executes*/
    if(RB4_InterruptHandler){RB4_InterruptHandler();}
}
void RB5_ISR(void){
    /* The RB5 external interrupt occurred (must be cleared in software )*/
    EXT_RBx_InterruptFlagClear();
    /* Code */
    
    /* CallBack Function gets called every time this ISR executes*/
    if(RB5_InterruptHandler){RB5_InterruptHandler();}
}
void RB6_ISR(void){
    /* The RB6 external interrupt occurred (must be cleared in software )*/
    EXT_RBx_InterruptFlagClear();
    /* Code */
    
    /* CallBack Function gets called every time this ISR executes*/
    if(RB6_InterruptHandler){RB6_InterruptHandler();}
}
void RB7_ISR(void){
    /* The RB7 external interrupt occurred (must be cleared in software )*/
    EXT_RBx_InterruptFlagClear();
    /* Code */
    
    /* CallBack Function gets called every time this ISR executes*/
    if(RB7_InterruptHandler){RB7_InterruptHandler();}
}

/**************  INTx Static Functions       **********/
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Enable (const interrupt_INTx_t *int_obj){
    Std_ReturnType ret=E_OK;
    if(int_obj==NULL){
        ret=E_NOT_OK;
    }
    else{
        switch (int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 :
                 #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                    INTERRUPT_PriorityLevelsEnable();
                    INTERRUPT_GlobalInterruptHighEnable();
                #else
                    INTERRUPT_GlobalInterruptEnable(); 
                #endif
                EXT_INT0_InterruptEnable();
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 
                    INTERRUPT_PriorityLevelsEnable();
                    if (INTERRUPT_LOW_PRIORITY == int_obj->priority){ INTERRUPT_GlobalInterruptLowEnable(); }
                    else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority){ INTERRUPT_GlobalInterruptHighEnable(); }
                    else {ret=E_NOT_OK;}
                #else
                    INTERRUPT_GlobalInterruptEnable(); 
                #endif
                EXT_INT1_InterruptEnable();
                break;
            case INTERRUPT_EXTERNAL_INT2 :
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                    INTERRUPT_PriorityLevelsEnable();
                    if (INTERRUPT_LOW_PRIORITY == int_obj->priority){ INTERRUPT_GlobalInterruptLowEnable(); }
                    else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority){ INTERRUPT_GlobalInterruptHighEnable(); }
                    else {ret=E_NOT_OK;}
                #else
                    INTERRUPT_GlobalInterruptEnable(); 
                #endif
                EXT_INT2_InterruptEnable();
                break;
            default: ret=E_NOT_OK;
        }
        }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Disable (const interrupt_INTx_t *int_obj){
    Std_ReturnType ret=E_OK;
    if(int_obj==NULL){
        ret=E_NOT_OK;
    }
    else{
        switch (int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : EXT_INT0_InterruptDisable();break;
            case INTERRUPT_EXTERNAL_INT1 : EXT_INT1_InterruptDisable();break;
            case INTERRUPT_EXTERNAL_INT2 : EXT_INT2_InterruptDisable();break;
            default: ret=E_NOT_OK;
        }
        }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
#if (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE)
static Std_ReturnType Interrupt_INTx_Priority_Init (const interrupt_INTx_t *int_obj){
    Std_ReturnType ret=E_OK;
    if(int_obj==NULL){
        ret=E_NOT_OK;
    }
    else{
        switch (int_obj->source){
            case INTERRUPT_EXTERNAL_INT1 : 
                if (INTERRUPT_LOW_PRIORITY == int_obj->priority){ EXT_INT1_LowPrioritySet(); }
                else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority){ EXT_INT1_HighPrioritySet(); }
                else {ret=E_NOT_OK;}
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                if (INTERRUPT_LOW_PRIORITY == int_obj->priority){ EXT_INT2_LowPrioritySet(); }
                else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority){ EXT_INT2_HighPrioritySet(); }
                else {ret=E_NOT_OK;}
                break;
            default: ret=E_NOT_OK;
        }
        }
    return ret;
}
#endif
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Edge_Init (const interrupt_INTx_t *int_obj){
    Std_ReturnType ret=E_OK;
    if(int_obj==NULL){
        ret=E_NOT_OK;
    }
    else{
         switch (int_obj->source){
             case INTERRUPT_EXTERNAL_INT0 : 
                if (INTERRUPT_FALLING_EDGE == int_obj->edge){ EXT_INT0_FallingEdgeSet(); }
                else if (INTERRUPT_RISING_EDGE == int_obj->edge){ EXT_INT0_RisingEdgeSet(); }
                else {ret=E_NOT_OK;}
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                if (INTERRUPT_FALLING_EDGE == int_obj->edge){ EXT_INT1_FallingEdgeSet(); }
                else if (INTERRUPT_RISING_EDGE == int_obj->edge){ EXT_INT1_RisingEdgeSet(); }
                else {ret=E_NOT_OK;}
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                if (INTERRUPT_FALLING_EDGE == int_obj->edge){ EXT_INT2_FallingEdgeSet(); }
                else if (INTERRUPT_RISING_EDGE == int_obj->edge){ EXT_INT2_RisingEdgeSet(); }
                else {ret=E_NOT_OK;}
                break;
            default: ret=E_NOT_OK;
        }
        }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Pin_Init (const interrupt_INTx_t *int_obj){
    Std_ReturnType ret=E_OK;
    if(int_obj==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_direction_initialize(&(int_obj->mcu_pin));
        }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Clear_Flag (const interrupt_INTx_t *int_obj){
     Std_ReturnType ret=E_OK;
    if(int_obj==NULL){
        ret=E_NOT_OK;
    }
    else{
        switch (int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : EXT_INT0_InterruptFlagClear();break;
            case INTERRUPT_EXTERNAL_INT1 : EXT_INT1_InterruptFlagClear();break;
            case INTERRUPT_EXTERNAL_INT2 : EXT_INT2_InterruptFlagClear();break;
            default: ret=E_NOT_OK;
        }
        }
    return ret;
}

/**
 * 
 * @param InterruptHandler
 * @return 
 */
static Std_ReturnType INT0_SetInterruptHandler (void (*InterruptHandler)(void)){
    Std_ReturnType ret=E_OK;
    if(InterruptHandler==NULL){
        ret=E_NOT_OK;
    }
    else{
        INT0_InterruptHandler = InterruptHandler;
        }
    return ret;
}
/**
 * 
 * @param InterruptHandler
 * @return 
 */
static Std_ReturnType INT1_SetInterruptHandler (void (*InterruptHandler)(void)){
    Std_ReturnType ret=E_OK;
    if(InterruptHandler==NULL){
        ret=E_NOT_OK;
    }
    else{
          INT1_InterruptHandler = InterruptHandler;
        }
    return ret;
}
/**
 * 
 * @param InterruptHandler
 * @return 
 */
static Std_ReturnType INT2_SetInterruptHandler (void (*InterruptHandler)(void)){
    Std_ReturnType ret=E_OK;
    if(InterruptHandler==NULL){
        ret=E_NOT_OK;
    }
    else{
          INT2_InterruptHandler = InterruptHandler;
        }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_SetInterruptHandler (const interrupt_INTx_t *int_obj ){
    Std_ReturnType ret=E_OK;
    if(int_obj==NULL){
        ret=E_NOT_OK;
    }
    else{
        switch (int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : ret = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);break;
            case INTERRUPT_EXTERNAL_INT1 : ret = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);break;
            case INTERRUPT_EXTERNAL_INT2 : ret = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);break;
            default: ret=E_NOT_OK;
        }
        }
    return ret;
}
/******************RBx Static Functions*****************/
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_RBx_Enable (const interrupt_RBx_t *int_obj){
 Std_ReturnType ret=E_OK;
    if(int_obj==NULL){
        ret=E_NOT_OK;
    }
    else{
         #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 
                    INTERRUPT_PriorityLevelsEnable();
                    if (INTERRUPT_LOW_PRIORITY == int_obj->priority){ INTERRUPT_GlobalInterruptLowEnable(); }
                    else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority){ INTERRUPT_GlobalInterruptHighEnable(); }
                    else {ret=E_NOT_OK;}
                #else
                    INTERRUPT_GlobalInterruptEnable(); 
                #endif
                EXT_RBx_InterruptEnable();
        }
    return ret;   
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_RBx_Disable (const interrupt_RBx_t *int_obj){
 Std_ReturnType ret=E_OK;
    if(int_obj==NULL){
        ret=E_NOT_OK;
    }
    else{
                EXT_RBx_InterruptDisable();
        }
    return ret;   
}
/**
 * 
 * @param int_obj
 * @return 
 */
#if (INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE)
static Std_ReturnType Interrupt_RBx_Priority_Init (const interrupt_RBx_t *int_obj){
 Std_ReturnType ret=E_OK;
    if(int_obj==NULL){
        ret=E_NOT_OK;
    }
    else{
       if (INTERRUPT_LOW_PRIORITY == int_obj->priority){ EXT_RBx_LowPrioritySet(); }
       else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority){ EXT_RBx_HighPrioritySet(); }
       else {ret=E_NOT_OK;}
        }
    return ret;   
}
#endif
static Std_ReturnType Interrupt_RBx_Pin_Init (const interrupt_RBx_t *int_obj){
    Std_ReturnType ret=E_OK;
    if(int_obj==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_direction_initialize(&(int_obj->mcu_pin));
        }
    return ret;
}
static Std_ReturnType Interrupt_RBx_SetInterruptHandler (const interrupt_RBx_t *int_obj ){
    Std_ReturnType ret=E_OK;
    if(int_obj==NULL){
        ret=E_NOT_OK;
    }
    else{
        switch (int_obj->mcu_pin.pin){
            case PIN4 : ret = RB4_SetInterruptHandler(int_obj->EXT_InterruptHandler);break;
            case PIN5 : ret = RB5_SetInterruptHandler(int_obj->EXT_InterruptHandler);break;
            case PIN6 : ret = RB6_SetInterruptHandler(int_obj->EXT_InterruptHandler);break;
            case PIN7 : ret = RB7_SetInterruptHandler(int_obj->EXT_InterruptHandler);break;
            default: ret=E_NOT_OK;
        }
        }
    return ret;
}
/**
 * 
 * @param InterruptHandler
 * @return 
 */
static Std_ReturnType RB4_SetInterruptHandler (void (*InterruptHandler)(void)){
    Std_ReturnType ret=E_OK;
    if(InterruptHandler==NULL){
        ret=E_NOT_OK;
    }
    else{
        RB4_InterruptHandler = InterruptHandler;
        }
    return ret;
}
/**
 * 
 * @param InterruptHandler
 * @return 
 */
static Std_ReturnType RB5_SetInterruptHandler (void (*InterruptHandler)(void)){
    Std_ReturnType ret=E_OK;
    if(InterruptHandler==NULL){
        ret=E_NOT_OK;
    }
    else{
          RB5_InterruptHandler = InterruptHandler;
        }
    return ret;
}
/**
 * 
 * @param InterruptHandler
 * @return 
 */
static Std_ReturnType RB6_SetInterruptHandler (void (*InterruptHandler)(void)){
    Std_ReturnType ret=E_OK;
    if(InterruptHandler==NULL){
        ret=E_NOT_OK;
    }
    else{
          RB6_InterruptHandler = InterruptHandler;
        }
    return ret;
}
static Std_ReturnType RB7_SetInterruptHandler (void (*InterruptHandler)(void)){
    Std_ReturnType ret=E_OK;
    if(InterruptHandler==NULL){
        ret=E_NOT_OK;
    }
    else{
          RB7_InterruptHandler = InterruptHandler;
        }
    return ret;
}
static Std_ReturnType Interrupt_RBx_set_pin_init_value (const interrupt_RBx_t *int_obj ){
    Std_ReturnType ret=E_OK;
    if(int_obj==NULL){
        ret=E_NOT_OK;
    }
    else{
        switch (int_obj->mcu_pin.pin){
            case PIN4 : RB4_pin_init_value = int_obj->RBx_Pin_init_value;break;
            case PIN5 : RB5_pin_init_value = int_obj->RBx_Pin_init_value;break;
            case PIN6 : RB6_pin_init_value = int_obj->RBx_Pin_init_value;break;
            case PIN7 : RB7_pin_init_value = int_obj->RBx_Pin_init_value;break;
            default: ret=E_NOT_OK;
        }
        }
    return ret;
}
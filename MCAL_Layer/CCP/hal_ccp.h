/* 
 * File:   hal_ccp.h
 * Author: Mohamed Osama
 *
 * Created on January 3, 2024, 6:11 PM
 */

#ifndef HAL_CCP_H
#define	HAL_CCP_H

/* Section : Includes */
#include"../mcal_std_types.h"
#include"../GPIO/hal_gpio.h"
#include"../Interrupt/mcal_internal_interrupt.h"
#include"ccp_cfg.h"
#include"../my_pic18f4620.h"


/* Section : Macros Declaration */

/**
 * @defgroup CCP_Module_Modes 
 * Macros for configuring the CCP module mode select bits (CCPM3:CCPM0).
 */

/** @{ */

#define CCP_MODULE_DISABLE ((uint8)0x00)                // CCP Module Disabled
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH ((uint8)0x02)  // CCP Compare Mode, Toggle output on match
#define CCP_CAPTURE_MODE_1_FALLING_EDGE ((uint8)0x04)   // CCP Capture Mode, Every Falling Edge
#define CCP_CAPTURE_MODE_1_RISING_EDGE ((uint8)0x05)    // CCP Capture Mode, Every Rising Edge
#define CCP_CAPTURE_MODE_4_RISING_EDGE ((uint8)0x06)    // CCP Capture Mode, Every 4th Rising Edge
#define CCP_CAPTURE_MODE_16_RISING_EDGE ((uint8)0x07)   // CCP Capture Mode, Every 16th Rising Edge
#define CCP_COMPARE_MODE_SET_PIN_HIGH ((uint8)0x08)     // CCP Compare Mode, Initialize CCP pin low; on compare match, force CCP pin high
#define CCP_COMPARE_MODE_SET_PIN_LOW ((uint8)0x09)      // CCP Compare Mode, Initialize CCP pin high; on compare match, force CCP pin low
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT ((uint8)0x0A) // CCP Compare Mode, Generate software interrupt on compare match
#define CCP_COMPARE_MODE_GEN_EVENT ((uint8)0x0B)        // CCP Compare Mode, Trigger special event; reset timer; CCP match starts A/D conversion
#define CCP_PWM_MODE ((uint8)0x0C)                      // CCP PWM Mode

/** @} */

/* CCP Capture Mode State */
#define CCP_CAPTURE_NOT_READY 0x00
#define CCP_CAPTURE_READY 0x01

/* CCP Compare Mode State */
#define CCP_COMPARE_NOT_READY 0x00
#define CCP_COMPARE_READY 0x01

/* CCP Interrupt Flag */
#define CCP1_INT_FLAG PIR1_bits.CCP1IF
#define CCP2_INT_FLAG PIR2_bits.CCP2IF

/* Timer2 Input Clock Pre-Scaler */
#define CCP_TIMER2_PRESCALER_DIV_BY_1        1U
#define CCP_TIMER2_PRESCALER_DIV_BY_4        4U
#define CCP_TIMER2_PRESCALER_DIV_BY_16       16U


/* Section : Macro Functions Declaration */
#define CCP1_SET_MODE(_CONFIG)  (CCP1CON_bits.CCP1M = _CONFIG)
#define CCP2_SET_MODE(_CONFIG)  (CCP2CON_bits.CCP2M = _CONFIG)

#define CCP_CAPT_COMP_TIMER_SELECT(_CONFIG) do{\
                                                T3CON_bits.T3CCP1 = (uint8)(_CONFIG & 0x01); \
                                                T3CON_bits.T3CCP2 = (uint8)(_CONFIG >>  1 ); \
                                               }while(0)

/* Section : Data Types Declaration */
typedef enum {
    CCP_CAPTURE_MODE_SELECTED = 0 ,
    CCP_COMPARE_MODE_SELECTED ,
    CCP_PWM_MODE_SELECTED
}ccp;

typedef enum{
    CCP1_INST = 0 ,
    CCP2_INST        
}ccp_inst_t;

typedef enum{
    CCP1_CCP2_TIMER1 = 0 ,
    CCP1_TIMER1_CCP2_TIMER3 ,
    CCP1_CCP2_TIMER3 
}ccp_capt_comp_timer_t;
/*
  @Summary      Defines the values to convert from 16-bit to two 8-bit & vice versa
  @Description  Used to get two 8-bit values from 16-bit also two 8-bit value are combined to get 16-bit
 */
typedef union{
    struct {
        uint8 ccpr_low;
        uint8 ccpr_high;
    };
    struct {
      uint16 ccpr_16Bit;
    };
}CCP_REG_T;

typedef struct {
    ccp_capt_comp_timer_t ccp_capt_comp_timer;
    ccp_inst_t ccp_inst;
    ccp ccp_mode;         /* CCP Main Mode */
    uint8 ccp_mode_variant;  /* CCP Selected Mode Variant */
    pin_config_t ccp_pin;    /* CCP Pin Configuration */
#if ( CCP_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE )
    void(* CCP_Interrupt_Handler)(void); /* Callback used for all CCP Modes */
    interrupt_priority_cfg priority; /* Configure the CCP Mode Interrupt Priority */
#endif
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED))    
    uint32 PWM_Frequency ; /* CCP PWM Mode Frequency */
    uint8 Timer2_Prescaler_Value ;
#endif    
}ccp_t;


/* Section : Functions Declaration */

Std_ReturnType CCP_Init(const ccp_t * _ccp_obj);
Std_ReturnType CCP_DeInit(const ccp_t * _ccp_obj);
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED))
Std_ReturnType CCP_IsCapturedDataReady (const ccp_t * _ccp_obj, uint8 * _capture_status);
Std_ReturnType CCP_Capture_Mode_Read_Value (const ccp_t * _ccp_obj, uint32 * capture_value);
#endif
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED))
Std_ReturnType CCP_IsCompareComplete (const ccp_t * _ccp_obj, uint8 * _compare_status);
Std_ReturnType CCP_Compare_Mode_Set_Value (const ccp_t * _ccp_obj, uint16 compare_value);
#endif
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED))
Std_ReturnType CCP_PWM_Set_Duty(const ccp_t * _ccp_obj, const uint8 _duty);
Std_ReturnType CCP_PWM_Start(const ccp_t * _ccp_obj);
Std_ReturnType CCP_PWM_Stop(const ccp_t * _ccp_obj);
#endif


#endif	/* HAL_CCP_H */


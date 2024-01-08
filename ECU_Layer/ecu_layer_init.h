/* 
 * File:   ecu_layer_init.h
 * Author: Mohamed Osama
 *
 * Created on August 30, 2023, 12:59 AM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H

/* Section : Includes */
#include "7_Segment/ecu_seven_seg.h"
#include "DC_Motor/ecu_dc_motor.h"
#include "KeyPad/ecu_keypad.h"
#include "LED/ecu_led.h"
#include "Relay/ecu_relay.h"
#include "button/ecu_button.h"
#include "Chr_LCD/ecu_chr_lcd.h"
/* Section : Macros Declaration */


/* Section : Macro Functions Declaration */


/* Section : Data Types Declaration */
extern chr_lcd_4bit_t lcd1; 
extern led_t led1;
/* Section : Functions Declaration */
void ecu_layer_initialize(void);
#endif	/* ECU_LAYER_INIT_H */


#include "ecu_layer_init.h"
#include "Chr_LCD/ecu_chr_lcd.h"
chr_lcd_4bit_t lcd1 ={
  .lcd_rs.port=PORTD_INDEX,
  .lcd_rs.pin=PIN0,
  .lcd_rs.direction=OUTPUT,
  .lcd_rs.logic=LOW,
  .lcd_en.port=PORTD_INDEX,
  .lcd_en.pin=PIN1,
  .lcd_en.direction=OUTPUT,
  .lcd_en.logic=LOW,
  .lcd_data[0].port=PORTD_INDEX,
  .lcd_data[0].pin=PIN2,
  .lcd_data[0].direction=OUTPUT,
  .lcd_data[0].logic=LOW,
  .lcd_data[1].port=PORTD_INDEX,
  .lcd_data[1].pin=PIN3,
  .lcd_data[1].direction=OUTPUT,
  .lcd_data[1].logic=LOW,
  .lcd_data[2].port=PORTD_INDEX,
  .lcd_data[2].pin=PIN4,
  .lcd_data[2].direction=OUTPUT,
  .lcd_data[2].logic=LOW,
  .lcd_data[3].port=PORTD_INDEX,
  .lcd_data[3].pin=PIN5,
  .lcd_data[3].direction=OUTPUT,
  .lcd_data[3].logic=LOW
};
/*
dc_motor_t dc_motor_1 = {
    .dc_motor_pin[0].port = PORTD_INDEX,
    .dc_motor_pin[0].pin = PIN0,
    .dc_motor_pin[0].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[0].direction = OUTPUT,
    .dc_motor_pin[1].port = PORTD_INDEX,
    .dc_motor_pin[1].pin = PIN1,
    .dc_motor_pin[1].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[1].direction = OUTPUT
};*/
/*
dc_motor_t dc_motor_2 = {
    .dc_motor_pin[0].port = PORTD_INDEX,
    .dc_motor_pin[0].pin = PIN2,
    .dc_motor_pin[0].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[0].direction = OUTPUT,
    .dc_motor_pin[1].port = PORTD_INDEX,
    .dc_motor_pin[1].pin = PIN3,
    .dc_motor_pin[1].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[1].direction = OUTPUT
};*/
/*
chr_lcd_8bit_t lcd_2 ={
  .lcd_rs.port=PORTC_INDEX,
  .lcd_rs.pin=PIN6,
  .lcd_rs.direction=OUTPUT,
  .lcd_rs.logic=LOW,
  .lcd_en.port=PORTC_INDEX,
  .lcd_en.pin=PIN7,
  .lcd_en.direction=OUTPUT,
  .lcd_en.logic=LOW,
  .lcd_data[0].port=PORTD_INDEX,
  .lcd_data[0].pin=PIN0,
  .lcd_data[0].direction=OUTPUT,
  .lcd_data[0].logic=LOW,
  .lcd_data[1].port=PORTD_INDEX,
  .lcd_data[1].pin=PIN1,
  .lcd_data[1].direction=OUTPUT,
  .lcd_data[1].logic=LOW,
  .lcd_data[2].port=PORTD_INDEX,
  .lcd_data[2].pin=PIN2,
  .lcd_data[2].direction=OUTPUT,
  .lcd_data[2].logic=LOW,
  .lcd_data[3].port=PORTD_INDEX,
  .lcd_data[3].pin=PIN3,
  .lcd_data[3].direction=OUTPUT,
  .lcd_data[3].logic=LOW,
  .lcd_data[4].port=PORTD_INDEX,
  .lcd_data[4].pin=PIN4,
  .lcd_data[4].direction=OUTPUT,
  .lcd_data[4].logic=LOW,
  .lcd_data[5].port=PORTD_INDEX,
  .lcd_data[5].pin=PIN5,
  .lcd_data[5].direction=OUTPUT,
  .lcd_data[5].logic=LOW,
  .lcd_data[6].port=PORTD_INDEX,
  .lcd_data[6].pin=PIN6,
  .lcd_data[6].direction=OUTPUT,
  .lcd_data[6].logic=LOW,
  .lcd_data[7].port=PORTD_INDEX,
  .lcd_data[7].pin=PIN7,
  .lcd_data[7].direction=OUTPUT,
  .lcd_data[7].logic=LOW
};*/
/*
keypad_t keypad1={
    .keypad_row_pins[0].pin=PIN0,
    .keypad_row_pins[0].port=PORTC_INDEX,
    .keypad_row_pins[0].direction=OUTPUT,
    .keypad_row_pins[0].logic=LOW,
    .keypad_row_pins[1].pin=PIN1,
    .keypad_row_pins[1].port=PORTC_INDEX,
    .keypad_row_pins[1].direction=OUTPUT,
    .keypad_row_pins[1].logic=LOW,
    .keypad_row_pins[2].pin=PIN2,
    .keypad_row_pins[2].port=PORTC_INDEX,
    .keypad_row_pins[2].direction=OUTPUT,
    .keypad_row_pins[2].logic=LOW,
    .keypad_row_pins[3].pin=PIN3,
    .keypad_row_pins[3].port=PORTC_INDEX,
    .keypad_row_pins[3].direction=OUTPUT,
    .keypad_row_pins[3].logic=LOW,
    .keypad_columns_pins[0].pin=PIN4,
    .keypad_columns_pins[0].port=PORTC_INDEX,
    .keypad_columns_pins[0].direction=INPUT,
    .keypad_columns_pins[0].logic=LOW,
    .keypad_columns_pins[1].pin=PIN5,
    .keypad_columns_pins[1].port=PORTC_INDEX,
    .keypad_columns_pins[1].direction=INPUT,
    .keypad_columns_pins[1].logic=LOW,
    .keypad_columns_pins[2].pin=PIN6,
    .keypad_columns_pins[2].port=PORTC_INDEX,
    .keypad_columns_pins[2].direction=INPUT,
    .keypad_columns_pins[2].logic=LOW,
    .keypad_columns_pins[3].pin=PIN7,
    .keypad_columns_pins[3].port=PORTC_INDEX,
    .keypad_columns_pins[3].direction=INPUT,
    .keypad_columns_pins[3].logic=LOW
};*/

led_t led1 = {
    .port_name=PORTB_INDEX,
    .pin=PIN7,
    .led_status=LOW
};
/*
led_t led2 = {
    .port_name=PORTD_INDEX,
    .pin=PIN1,
    .led_status=LOW
};*/
/*
led_t led3 = {
    .port_name=PORTD_INDEX,
    .pin=PIN2,
    .led_status=LOW
};*/
/*
led_t led4 = {
    .port_name=PORTD_INDEX,
    .pin=PIN3,
    .led_status=LOW
};
*/
void ecu_layer_initialize(void){
     Std_ReturnType ret=E_NOT_OK;
     ret = lcd_4bit_initialize(&lcd1);
}

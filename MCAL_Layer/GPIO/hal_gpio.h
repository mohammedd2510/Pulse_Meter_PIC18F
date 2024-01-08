/* 
 * File:   hal_gpio.h
 * Author: Mohamed Osama
 *
 * Created on August 15, 2023, 1:08 PM
 */
#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* Section : Includes */
#include "../mcal_std_types.h"
#include "../device_config.h"
#include"../my_pic18f4620.h"
#include "hal_gpio_cfg.h"
/* Section : Macros Declaration */
#define BIT_MASK (uint8)0x01
#define PIN_MAX_SIZE 8
#define PORT_MAX_SIZE 5
#define PORT_MASK 0XFF



/* Section : Macro Functions Declaration */

#define SET_BIT(REG,BIT) (REG|=(BIT_MASK<<BIT))
#define CLR_BIT(REG,BIT) (REG&=~(BIT_MASK<<BIT))
#define TOGGLE_BIT(REG,BIT) (REG^=(BIT_MASK<<BIT))
#define GET_BIT(REG,BIT) ((REG>>BIT)&(BIT_MASK))

/* Section : Data Types Declaration */
typedef enum{
    LOW=0,
    HIGH  
}logic_t;

typedef enum{
    OUTPUT=0,
    INPUT
}direction_t;

typedef enum{
    PIN0=0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7   
}pin_index_t;

typedef enum{
    PORTA_INDEX=0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX 
}port_index_t;

typedef struct{
    uint8 port:3;       /* @ref port_index_t */
    uint8 pin:3;        /* @ref pin_index_t */
    uint8 direction:1;  /* @ref direction_t */
    uint8 logic:1;      /* @ref logic_t */
}pin_config_t;

/* Section : Functions Declaration */
Std_ReturnType gpio_pin_initialize(const pin_config_t *pin_config);
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t *pin_config);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *pin_config, direction_t* direction_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *pin_config, logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t *pin_config, logic_t* logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *pin_config);

Std_ReturnType gpio_port_direction_initialize(port_index_t port,uint8 direction);
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8* direction_status);
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic);
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8* logic);
Std_ReturnType gpio_port_toggle_logic(port_index_t port);
#endif	/* HAL_GPIO_H */


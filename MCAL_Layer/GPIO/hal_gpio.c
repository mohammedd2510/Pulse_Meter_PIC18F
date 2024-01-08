/* 
 * File:   hal_gpio.c
 * Author: Mohamed Osama
 *
 * Created on August 15, 2023, 1:08 PM
 */
#include "hal_gpio.h"
/* Reference to Data Direction Control Registers */
volatile uint8 *tris_registers [] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
/* Reference to Data Latch Registers */
volatile uint8 *lat_registers[]={&LATA,&LATB,&LATC,&LATD,&LATE};
/* Reference to Port Status Registers */
volatile uint8 *port_registers[] ={&PORTA,&PORTB,&PORTC ,&PORTD ,&PORTE};


/**
 * @brief Initialize the direction & logic of a specific pin 
 * @param pin_config pointer to the configurations @ref pin_config_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_initialize(const pin_config_t *pin_config){
    Std_ReturnType ret=E_OK;
    if((pin_config==NULL)||(pin_config->pin>PIN_MAX_SIZE-1)||(pin_config->port>PORT_MAX_SIZE-1)){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_direction_initialize(pin_config);
        ret=gpio_pin_write_logic(pin_config,pin_config->logic);
        }
    return ret;
}
#endif
/**
 * @brief Initialize the direction of a specific pin @ref direction_t
 * @param pin_config pointer to the configurations @ref pin_config_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t *pin_config){
    Std_ReturnType ret=E_OK;
    if((pin_config==NULL)||(pin_config->pin>PIN_MAX_SIZE-1)||(pin_config->port>PORT_MAX_SIZE-1)){
        ret=E_NOT_OK;
    }
    else{
        switch(pin_config->direction){
            case OUTPUT:
                CLR_BIT(*tris_registers[pin_config->port],pin_config->pin);
                break;
            case INPUT:
                SET_BIT(*tris_registers[pin_config->port],pin_config->pin);
                break;
            default: ret=E_NOT_OK;
        }
        
    }
    return ret;
}
#endif
/**
 * @brief get the direction status of a specific pin @ref direction_t
 * @param pin_config pointer to the configurations @ref pin_config_t
 * @param direction_status pointer to the direction of the pin status
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *pin_config, direction_t* direction_status){
      Std_ReturnType ret=E_OK;
    if((pin_config==NULL)||(direction_status==NULL)||(pin_config->pin>PIN_MAX_SIZE-1)||(pin_config->port>PORT_MAX_SIZE-1)){
        ret=E_NOT_OK;
    }
    else{
       *direction_status= GET_BIT(*(tris_registers[pin_config->port]),pin_config->pin);
    }
        
    return ret;
}
#endif
/**
 * @brief write logic on a specific pin @ref logic_t
 * @param pin_config pointer to the configurations @ref pin_config_t
 * @param logic contains the value of the logic of the pin
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_write_logic(const pin_config_t *pin_config, logic_t logic){
      Std_ReturnType ret=E_OK;
    if((pin_config==NULL)||(pin_config->pin>PIN_MAX_SIZE-1)||(pin_config->port>PORT_MAX_SIZE-1)){
        ret=E_NOT_OK;
    }
    else{
        switch(logic){
            case HIGH:
                SET_BIT(*lat_registers[pin_config->port],pin_config->pin);
                break;
            case LOW:
                CLR_BIT(*lat_registers[pin_config->port],pin_config->pin);
                break;
            default: ret=E_NOT_OK;
        }
    }
    return ret;
}
#endif
/**
 * @brief reads the logic of a specific pin @ref logic_t
 * @param pin_config pointer to the configurations @ref pin_config_t
 * @param logic pointer to the pin logic status 
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_read_logic(const pin_config_t *pin_config, logic_t* logic){
      Std_ReturnType ret=E_OK;
    if((pin_config==NULL)||(logic==NULL)||(pin_config->pin>PIN_MAX_SIZE-1)||(pin_config->port>PORT_MAX_SIZE-1)){
        ret=E_NOT_OK;
    }
    else{
        *logic=GET_BIT(*(port_registers[pin_config->port]),pin_config->pin);
        }
    return ret;
}
#endif
/**
 * brief toggle the logic of a specific pin
 * @param pin_config pointer to the configurations @ref pin_config_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *pin_config){
      Std_ReturnType ret=E_OK;
    if((pin_config==NULL)||(pin_config->pin>PIN_MAX_SIZE-1)||(pin_config->port>PORT_MAX_SIZE-1)){
        ret=E_NOT_OK;
    }
    else{
        TOGGLE_BIT(*(lat_registers[pin_config->port]),pin_config->pin);
        }
    return ret;
}
#endif
/**
 * brief initialize the direction of a specific port
 * @param port contains the port index @ref port_index_t
 * @param direction contains the direction of the port @ref direction_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_direction_initialize(port_index_t port,uint8 direction){
      Std_ReturnType ret=E_OK;
    if((port>PORT_MAX_SIZE-1)){
        ret=E_NOT_OK;
    }
    else{
        *tris_registers[port]=direction;
    }
    return ret;
}
#endif
/**
 * @brief get the direction status of a specific port
 * @param port contains the port index @ref port_index_t
 * @param direction_status pointer to the direction status of the port @ref direction_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8* direction_status){
      Std_ReturnType ret=E_OK;
    if((direction_status==NULL)||(port>PORT_MAX_SIZE-1)){
        ret=E_NOT_OK;
    }
    else{
        
        *direction_status=*tris_registers[port];
    }
    return ret;
}
#endif
/**
 * 
 * @param port contains the port index @ref port_index_t
 * @param logic contains the logic of the port @ref logic_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic){
      Std_ReturnType ret=E_OK;
    if((port>PORT_MAX_SIZE-1)){
        ret=E_NOT_OK;
    }
    else{
        *lat_registers[port]=logic;
        }
    return ret;
}
#endif
/**
 * @brief reads the logic of a specific port
 * @param port contains the port index @ref port_index_t
 * @param logic pointer to the logic status of the port @ref logic_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8* logic){
      Std_ReturnType ret=E_OK;
    if((logic==NULL)||(port>PORT_MAX_SIZE-1)){
        ret=E_NOT_OK;
    }
    else{
        *logic=*port_registers[port];
        }
        
    return ret;
}
#endif
/**
 * @brief toggle the logic of a specific port
 * @param port contains the port index @ref port_index_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_toggle_logic(port_index_t port){
      Std_ReturnType ret=E_OK;
    if(port>PORT_MAX_SIZE-1){
        ret=E_NOT_OK;
    }
    else{
        *lat_registers[port]^=PORT_MASK;
        }
        
    return ret;
}
#endif
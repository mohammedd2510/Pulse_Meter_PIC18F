#include "ecu_chr_lcd.h"

static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd, uint8 _data_command );
static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd);
static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd);
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd , uint8 row , uint8 column);
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd , uint8 row , uint8 column);
/**
 * 
 * @param lcd
 * @return 
 */
Std_ReturnType lcd_4bit_initialize (const chr_lcd_4bit_t *lcd){
     Std_ReturnType ret=E_OK;
     uint8 l_data_pins_counter=ZERO_INIT;
    if(lcd==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_initialize(&(lcd->lcd_rs));
        ret=gpio_pin_initialize(&(lcd->lcd_en));
        for(l_data_pins_counter=ZERO_INIT;l_data_pins_counter<4;l_data_pins_counter++){
             ret=gpio_pin_initialize(&(lcd->lcd_data[l_data_pins_counter]));
        }
        
        ret=lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2times);
        __delay_us(1000);
        ret=lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_THEN_4BIT_MODE);
        __delay_us(1000);
        ret=lcd_4bit_send_command(lcd,_LCD_4BIT_MODE_2_LINE);
        __delay_us(1000);
        ret=lcd_4bit_send_command(lcd,_LCD_CLEAR);
        __delay_us(1000);
        ret=lcd_4bit_send_command(lcd,_LCD_ENTRY_MODE_INC_SHIFT_OFF);
        __delay_us(1000);
        ret=lcd_4bit_send_command(lcd,_LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        __delay_us(1000);
        }
    return ret;
}

/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
Std_ReturnType lcd_4bit_send_command (const chr_lcd_4bit_t *lcd, uint8 command){
    Std_ReturnType ret=E_OK;
    if(lcd==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_write_logic(&(lcd->lcd_rs),LOW);
        ret=lcd_send_4bits(lcd, command >> 4);
        ret=lcd_4bit_send_enable_signal(lcd);
        ret=lcd_send_4bits(lcd, command);
        ret=lcd_4bit_send_enable_signal(lcd);
        }
    return ret;
}
/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
Std_ReturnType lcd_4bit_send_char_data (const chr_lcd_4bit_t *lcd, uint8 data){
    Std_ReturnType ret=E_OK;
    if(lcd==NULL){
        ret=E_NOT_OK;
    }
    else{
       ret=gpio_pin_write_logic(&(lcd->lcd_rs),HIGH);
        ret=lcd_send_4bits(lcd, data >> 4);
        ret=lcd_4bit_send_enable_signal(lcd);
        ret=lcd_send_4bits(lcd, data);
        ret=lcd_4bit_send_enable_signal(lcd);
        }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return 
 */
Std_ReturnType lcd_4bit_send_char_data_pos (const chr_lcd_4bit_t *lcd ,uint8 row ,uint8 column , uint8 data){
    Std_ReturnType ret=E_OK;
    if(lcd==NULL){
        ret=E_NOT_OK;
    }
    else{
        lcd_4bit_set_cursor(lcd,row,column);
        lcd_4bit_send_char_data(lcd,data);
        }
    return ret;
}
/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
Std_ReturnType lcd_4bit_send_string (const chr_lcd_4bit_t *lcd, uint8 *str){
    Std_ReturnType ret=E_OK;
    if(lcd==NULL){
        ret=E_NOT_OK;
    }
    else{
        while(*str){
            ret=lcd_4bit_send_char_data(lcd,*str++);
        }
        }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return 
 */
Std_ReturnType lcd_4bit_send_string_pos (const chr_lcd_4bit_t *lcd ,uint8 row ,uint8 column , uint8 *str){
    Std_ReturnType ret=E_OK;
    if(lcd==NULL){
        ret=E_NOT_OK;
    }
    else{
       lcd_4bit_set_cursor(lcd,row,column);
        while(*str){
            ret=lcd_4bit_send_char_data(lcd,*str++);
        }
        }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param _chr
 * @param mem_pos
 * @return 
 */
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd ,uint8 row ,uint8 column ,
                                         const uint8 _chr[],uint8 mem_pos){
     Std_ReturnType ret=E_OK;
    uint8 lcd_counter=ZERO_INIT;
    if(lcd==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=lcd_4bit_send_command(lcd,(_LCD_CGRAM_START+(8*mem_pos)));
        for(lcd_counter=ZERO_INIT;lcd_counter<8;lcd_counter++){
           ret= lcd_4bit_send_char_data(lcd,_chr[lcd_counter]);
        }
        ret=lcd_4bit_send_char_data_pos(lcd,row,column,mem_pos);
        }
    return ret;
    
}

/**
 * 
 * @param lcd
 * @return 
 */
Std_ReturnType lcd_8bit_initialize (const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret=E_OK;
     uint8 l_data_pins_counter=ZERO_INIT;
    if(lcd==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_initialize(&(lcd->lcd_rs));
        ret=gpio_pin_initialize(&(lcd->lcd_en));
        for(l_data_pins_counter=ZERO_INIT;l_data_pins_counter<8;l_data_pins_counter++){
             ret=gpio_pin_initialize(&(lcd->lcd_data[l_data_pins_counter]));
        }
        __delay_ms(20);
        ret=lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret=lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret=lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        ret=lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        ret=lcd_8bit_send_command(lcd,_LCD_CLEAR);
        ret=lcd_8bit_send_command(lcd,_LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret=lcd_8bit_send_command(lcd,_LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        
        
        }
    return ret;
}
/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
Std_ReturnType lcd_8bit_send_command (const chr_lcd_8bit_t *lcd, uint8 command){
    Std_ReturnType ret=E_OK;
     uint8 l_pins_counter=ZERO_INIT;
    if(lcd==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_write_logic(&(lcd->lcd_rs),LOW);
        for(l_pins_counter=ZERO_INIT;l_pins_counter<8;l_pins_counter++){
         ret=gpio_pin_write_logic(&(lcd->lcd_data[l_pins_counter]),( command >> l_pins_counter ) & (uint8)0x01);   
        }
        lcd_8bit_send_enable_signal(lcd);
        
        }
    return ret;
}
/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
Std_ReturnType lcd_8bit_send_char_data (const chr_lcd_8bit_t *lcd, uint8 data){
     Std_ReturnType ret=E_OK;
     uint8 l_pins_counter=ZERO_INIT;
    if(lcd==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_write_logic(&(lcd->lcd_rs),HIGH);
        for(l_pins_counter=ZERO_INIT;l_pins_counter<8;l_pins_counter++){
         ret=gpio_pin_write_logic(&(lcd->lcd_data[l_pins_counter]),( data >> l_pins_counter ) & (uint8)0x01);   
        }
        lcd_8bit_send_enable_signal(lcd);
        }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return 
 */
Std_ReturnType lcd_8bit_send_char_data_pos (const chr_lcd_8bit_t *lcd ,uint8 row ,uint8 column , uint8 data){
    Std_ReturnType ret=E_OK;
    if(lcd==NULL){
        ret=E_NOT_OK;
    }
    else{
        lcd_8bit_set_cursor(lcd,row,column);
        lcd_8bit_send_char_data(lcd,data);
        }
    return ret;
}
/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
Std_ReturnType lcd_8bit_send_string (const chr_lcd_8bit_t *lcd, uint8 *str){
    Std_ReturnType ret=E_OK;
    if(lcd==NULL){
        ret=E_NOT_OK;
    }
    else{
        while(*str){
            ret=lcd_8bit_send_char_data(lcd,*str++);
        }
        }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return 
 */
Std_ReturnType lcd_8bit_send_string_pos (const chr_lcd_8bit_t *lcd ,uint8 row ,uint8 column , uint8 *str){
    Std_ReturnType ret=E_OK;
    if(lcd==NULL){
        ret=E_NOT_OK;
    }
    else{
        lcd_8bit_set_cursor(lcd,row,column);
        while(*str){
            ret=lcd_8bit_send_char_data(lcd,*str++);
        }
        }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param _chr
 * @param mem_pos
 * @return 
 */
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd ,uint8 row ,uint8 column ,
                                         const uint8 _chr[],uint8 mem_pos){
    Std_ReturnType ret=E_OK;
    uint8 lcd_counter=ZERO_INIT;
    if(lcd==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=lcd_8bit_send_command(lcd,(_LCD_CGRAM_START+(8*mem_pos)));
        for(lcd_counter=ZERO_INIT;lcd_counter<8;lcd_counter++){
           ret= lcd_8bit_send_char_data(lcd,_chr[lcd_counter]);
        }
        ret=lcd_8bit_send_char_data_pos(lcd,row,column,mem_pos);
        }
    return ret;
    
}
/**
 * 
 * @param value
 * @param str
 */
Std_ReturnType convert_uint8_to_string(uint8 value , uint8 *str){
   Std_ReturnType ret=E_OK;
   uint8 Temp_str[4]={0};
   uint8 cnt =0;
    if(str==NULL){
        ret=E_NOT_OK;
    }
    else{
        memset(str,'\0',4);
        sprintf(Temp_str,"%i",value);
        while (Temp_str[cnt] != '\0'){
            str[cnt] = Temp_str [cnt];
            cnt++;
        }
        str[3] = '\0';
        }
    return ret;
}
/**
 * 
 * @param value
 * @param str
 */
Std_ReturnType convert_uint16_to_string(uint16 value , uint8 *str){
    Std_ReturnType ret=E_OK;
   uint8 Temp_str[6]={0};
   uint8 cnt =0;
    if(str==NULL){
        ret=E_NOT_OK;
    }
    else{
        memset(str,' ',6);
        sprintf(Temp_str,"%i",value);
        while (Temp_str[cnt] != '\0'){
            str[cnt] = Temp_str [cnt];
            cnt++;
        }
        str[5] = '\0';
        }
    return ret;
}
/**
 * 
 * @param value
 * @param str
 */
Std_ReturnType convert_uint32_to_string(uint32 value , uint8 *str){
   Std_ReturnType ret=E_OK;
   uint8 Temp_str[11]={0};
   uint8 cnt =0;
    if(str==NULL){
        ret=E_NOT_OK;
    }
    else{
        memset(str,'\0',11);
        sprintf(Temp_str,"%i",value);
        while (Temp_str[cnt] != '\0'){
            str[cnt] = Temp_str [cnt];
            cnt++;
        }
        str[10] = '\0';
        }
    return ret;
}
/**
 * 
 * @param lcd
 * @param _data_command
 * @return 
 */
static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd, uint8 _data_command ){
    Std_ReturnType ret=E_OK;
    if(lcd==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_write_logic(&(lcd->lcd_data[0]),( _data_command >> 0 ) & (uint8)0x01);
        ret=gpio_pin_write_logic(&(lcd->lcd_data[1]),( _data_command >> 1 ) & (uint8)0x01);
        ret=gpio_pin_write_logic(&(lcd->lcd_data[2]),( _data_command >> 2 ) & (uint8)0x01);
        ret=gpio_pin_write_logic(&(lcd->lcd_data[3]),( _data_command >> 3 ) & (uint8)0x01);
        }
    return ret;
}
static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret=E_OK;
    if(lcd==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_write_logic(&(lcd->lcd_en),HIGH);
        __delay_us(5);
        ret=gpio_pin_write_logic(&(lcd->lcd_en),LOW);
        }
    return ret;
}
static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret=E_OK;
    if(lcd==NULL){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_write_logic(&(lcd->lcd_en),HIGH);
        __delay_us(5);
        ret=gpio_pin_write_logic(&(lcd->lcd_en),LOW);
        }
    return ret;
}
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd , uint8 row , uint8 column){
    Std_ReturnType ret=E_OK;
    if(lcd==NULL){
        ret=E_NOT_OK;
    }
    else{
        column--;
        switch (row){
            case ROW1 : ret=lcd_8bit_send_command(lcd,0x80+column);break;
            case ROW2 : ret=lcd_8bit_send_command(lcd,0xC0+column);break; 
            case ROW3 : ret=lcd_8bit_send_command(lcd,0x94+column);break; 
            case ROW4 : ret=lcd_8bit_send_command(lcd,0xD4+column);break; 
            default:    ret=E_NOT_OK;break;
        }
        }
    return ret;
}
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd , uint8 row , uint8 column){
    Std_ReturnType ret=E_OK;
    if(lcd==NULL){
        ret=E_NOT_OK;
    }
    else{
        column--;
        switch (row){
            case ROW1 : ret=lcd_4bit_send_command(lcd,0x80+column);break;
            case ROW2 : ret=lcd_4bit_send_command(lcd,0xC0+column);break; 
            case ROW3 : ret=lcd_4bit_send_command(lcd,0x94+column);break; 
            case ROW4 : ret=lcd_4bit_send_command(lcd,0xD4+column);break; 
            default:    ret=E_NOT_OK;break;
        }
        }
    return ret;
}
/**
 * @file Pulse_Meter.c
 * @brief Implementation file for Pulse Meter functionality.
 * @author Mohamed Osama
 */

/***************Includes********************/

#include"Pulse_Meter.h"

/*******************************************/

/***************** Global Variables Declarations ****************/

volatile uint32 Cap1 = 0;  // 1st captured value using CCP Module
volatile uint32 Cap2 = 0;  // 2nd captured value using CCP Module
volatile uint32 Cap3 = 0;  // 3rd captured value using CCP Module
volatile uint8 ovf_cnt = 0;  // Overflow counter
volatile uint8 cap_flag = 0;  // Capture flag
volatile uint8 compare_flag = 0;  // Compare flag

/*********************************************************************/

/******************* Functions Defintions***************************/

/**
 * @brief Displays a welcome message on the LCD for the Pulse Meter project.
 * @param void
 * @retval None
 * 
 * This function initializes the LCD and prints a welcome message 
 * along* with the project creator's name 
 */
void Welcome_Message(void)
{
    lcd_4bit_send_string_pos(&lcd1, 1, 1, "     Pulse Meter ");
    __delay_ms(300);
    lcd_4bit_send_string_pos(&lcd1, 2, 1, "     For Accuracy");
    __delay_ms(300);
    lcd_4bit_send_string_pos(&lcd1, 3, 1, "Frequency: 1->1000Hz");
    __delay_ms(300);
    lcd_4bit_send_string_pos(&lcd1, 4, 1, "Duty Cycle: 6->93%");
    __delay_ms(2000);
    lcd_4bit_send_command(&lcd1, _LCD_CLEAR);
} 
/**
 * @brief Initializes the Pulse Meter system.
 * @param void
 * @retval None
 * 
 * This function initializes the microcontroller abstraction layer (MCAL)
 * and the electronic control unit (ECU) layer for Pulse Meter measurement.
 */
void Pulse_Meter_Init(void)
{
    mcal_layer_initialize();
    ecu_layer_initialize();
}

/**
 * @brief Calculates the pulse frequency and duty cycle.
 *
 * @details This function calculates the pulse frequency and duty cycle based on the global captured values.
 *          The pulse frequency is calculated using the crystal frequency, timer prescaler, and captured values.
 *          The duty cycle is calculated using the captured values.
 *
 * @param XTAL_FREQ_MHZ The crystal frequency in megahertz.
 * @param TimerPrescaler The timer prescaler value.
 * @param Pulse_Freq Pointer to store the calculated pulse frequency.
 * @param Pulse_Duty_Cycle Pointer to store the calculated pulse duty cycle.
 */
void Pulse_Meter_Calculate(uint32 XTAL_FREQ_MHZ, uint8 TimerPrescaler, uint32* Pulse_Freq, uint8* Pulse_Duty_Cycle)
{
    uint32 Freq = 0; // Variable to store the calculated pulse frequency
    uint8 Duty_Cycle = 0; // Variable to store the calculated pulse duty cycle

    if (cap_flag == 3) {
        // Calculate the pulse duty cycle
        Duty_Cycle = (Cap2 - Cap1) * 100.0 / (Cap3 - Cap1);
        
        // Calculate the pulse frequency
        Freq = ((double)(XTAL_FREQ_MHZ * 1000000.0)) / ((double)(TimerPrescaler * (Cap3 - Cap1) * 4.0));
        
        // Store the calculated values in the provided pointers
        *Pulse_Freq = Freq;
        *Pulse_Duty_Cycle = Duty_Cycle;
        
        // Reset the timer value
        Timer1_Write_Value(&timer1_obj, 0);
        
        // Reset the cap_flag variable
        cap_flag = 0;
    }
}

/**
 * @brief Displays the pulse frequency and duty cycle on an LCD.
 *
 * This function displays the pulse frequency and duty cycle on an LCD screen.
 *
 * @param Pulse_Freq The pulse frequency to display.
 * @param Pulse_Duty_Cycle The pulse duty cycle to display.
 *
 * @details
 * The function uses the provided pulse frequency and duty cycle values to update the LCD display.
 * The pulse frequency is displayed in Hertz (Hz), and the pulse duty cycle is displayed as a percentage (%).
 * The LCD display is assumed to be a 4-bit interface.
 *
 * @return None.
 */
void Pulse_Meter_Display(uint32 Pulse_Freq, uint8 Pulse_Duty_Cycle)
{
    uint8 Freq_Str[5] = {0};
    uint8 Duty_Cycle_Str[4] = {0};

    lcd_4bit_send_string_pos(&lcd1, 1, 1, " Frequency = ");
    convert_uint32_to_string(Pulse_Freq, Freq_Str);
    lcd_4bit_send_string(&lcd1, Freq_Str);
    lcd_4bit_send_string(&lcd1, "Hz   ");

    lcd_4bit_send_string_pos(&lcd1, 2, 1, " Duty Cycle = ");
    convert_uint8_to_string(Pulse_Duty_Cycle, Duty_Cycle_Str);
    lcd_4bit_send_string(&lcd1, Duty_Cycle_Str);
    lcd_4bit_send_string(&lcd1, "%   ");
}

/**
 * @brief Interrupt service routine for CCP1 capture event.
 * @param None
 * @retval None
 * 
 * This function handles the CCP1 capture event and performs necessary actions based on the capture flag.
 */
void CCP1_Callback_ISR(void){
   if (cap_flag == 0) 
            {
                ovf_cnt = 0;
                Cap1=0;
                cap_flag = 1;
                CCP_Capture_Mode_Read_Value(&ccp1_obj,&Cap1);
                CCP1_SET_MODE(CCP_MODULE_DISABLE);
                CCP1_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);
                
            }
                else if (cap_flag == 1) {
                Cap2 = 0;
                cap_flag = 2;
                CCP_Capture_Mode_Read_Value(&ccp1_obj,&Cap2);
                Cap2 += (ovf_cnt * 65536);
                CCP1_SET_MODE(CCP_MODULE_DISABLE);
                CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);
            }
            else if (cap_flag == 2) 
            {
                Cap3 = 0;
                CCP_Capture_Mode_Read_Value(&ccp1_obj,&Cap3);
                Cap3 += (ovf_cnt * 65536);
                cap_flag = 3;
            }
   
}
/**
 * @brief Interrupt service routine for Timer 3 overflow event.
 * @param None
 * @retval None
 * 
 * This function increments the overflow count to keep track of Timer 3 overflow events.
 */
void TMR1_Callback_ISR(void) {
    ovf_cnt++;
}
#if (FREQUENCY_GENERATED_BY == CCP2_COMPARE_MODE)
/**
 * @brief CCP2 interrupt callback function to generate a 50Hz signal with a 75% duty cycle using Compare Mode.
 *
 * This function is a callback for the CCP2 interrupt and is used to generate a 50Hz signal with a 75% duty cycle using Compare Mode.
 * It sets the appropriate compare values and toggles the CCP2 pin to generate the desired waveform.
 *
 * @details
 * The function is designed to be used as a callback for the CCP2 interrupt.
 * It assumes the presence of a timer object named timer3_obj and a CCP object named ccp2_obj.
 * The function first resets the timer value to 0 using the 'Timer3_Write_Value function.
 * It then checks the compare_flag variable to determine the current state.
 * If compare_flag is 0, it sets the compare value to 4700 and sets compare_flag  to 1.
 * If compare_flag is 1, it sets the compare value to 14800 and sets compare_flag to 0.
 * Finally, it sets the CCP2 pin to a high or low state based on the compare_flag using the 'CCP2_SET_MODE' macro.
 *
 * @return None.
 */
void CCP2_Callback_ISR(void)
{
    Timer3_Write_Value(&timer3_obj, 0);

    if (compare_flag == 0)
    {
        CCP_Compare_Mode_Set_Value(&ccp2_obj, 4700);
        compare_flag = 1;
        CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
    }
    else if (compare_flag == 1)
    {
        CCP_Compare_Mode_Set_Value(&ccp2_obj, 14800);
        compare_flag = 0;
        CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
    }
}
#endif
/**
 * @file Pulse_Meter.h
 * @brief Header file for Pulse Meter functionality.
 * @author Mohamed Osama
 */

#ifndef PULSE_METER_H
#define	PULSE_METER_H

/* Section : Includes */
#include"MCAL_Layer/mcal_layer_init.h"
#include"ECU_Layer/ecu_layer_init.h"

/* Section : Macros Declaration */



/* Section : Macro Functions Declaration */


/* Section : Data Types Declaration */


/* Section : Functions Declaration */

/**
 * @brief Displays a welcome message on the LCD for the Pulse Meter project.
 * @param void
 * @retval None
 * 
 * This function initializes the LCD and prints a welcome message 
 * along* with the project creator's name 
 */
void Welcome_Message(void); 
/**
 * @brief Initializes the Pulse Meter system.
 * @param void
 * @retval None
 * 
 * This function initializes the microcontroller abstraction layer (MCAL)
 * and the electronic control unit (ECU) layer for Pulse Meter measurement.
 */
void Pulse_Meter_Init(void);
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
void Pulse_Meter_Calculate(uint32 XTAL_FREQ_MHZ, uint8 TimerPrescaler, uint32* Pulse_Freq , uint8* Pulse_Duty_Cycle);

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
void Pulse_Meter_Display(uint32 Pulse_Freq , uint8 Pulse_Duty_Cycle);

/**
 * @brief Interrupt service routine for CCP1 capture event.
 * @param None
 * @retval None
 * 
 * This function handles the CCP1 capture event and performs necessary actions based on the capture flag.
 */
void CCP1_Callback_ISR(void);
/**
 * @brief Interrupt service routine for Timer 3 overflow event.
 * @param None
 * @retval None
 * 
 * This function increments the overflow count to keep track of Timer 3 overflow events.
 */
void TMR1_Callback_ISR(void);

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
void CCP2_Callback_ISR(void);

#endif	/* PULSE_METER_H */


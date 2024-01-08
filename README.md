# **   Pulse Meter Project Made by Mohamed Osama  **

## Hardware used :
 1. PIC18F4620
 2. 20x4 LCD
 
 ## Software used :
 ### MCAL LAYER :
 1. GPIO Driver
 2. Interrupt DRIVER
 3. Timer1 Driver
 4. Timer2 Driver
 5. Timer3 Driver
 6. CCP Module Driver
   
### HAL LAYER :
1. LCD Driver

 ## Features :
1. Uses The CCP1 Module in Capture Mode to Measure the Frequency and DutyCycle of Signals
2. uses The CCP2 Module in PWM or Compare mode based on precompile configs to generate test signals 
3. For Accurate Measures use 16Mhz crystal Oscillator and the Range of :
     1. Frequency : 1->1000Hz
     2. Duty Cycle : 6->93%
4. The PWM Mode Generates 1kHZ Signal with 6% Dutycycle 
5. The Compare Mode Generates 50Hz Signal with 75% DutyCycle
6. Shows The Calculated Frequency & DutyCycle on The LCD

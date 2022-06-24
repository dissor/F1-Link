/*!
 * @file        readme.txt
 *
 * @brief       This file is routine instruction
 *
 * @version     V1.0.0
 *
 * @date        2021-07-26
 *
 */
 
 
&par Example Description 
 
This example describes how to use  ADC1 to monitor the voltage of ADC1_Channel14 continuously.
If the voltage on ADC1_Channel14(PC4) is not in the thresholds which is set brefore, analog watchdog 
interrupt will generate and light LED2.

&par Directory contents 

  - ADC/AnalogWatchdog/src/apm32e10x_int.c     Interrupt handlers
  - ADC/AnalogWatchdog/src/main.c                      Main program


&par Hardware and Software environment

  - This example runs on APM32E103_MINI Devices.
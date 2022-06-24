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

The example shows how to configure the SysTick to generate a time base equal to
1 ms. A "Delay" function is implemented based on the SysTick end-of-count event
which delays exactly half a second, and the LED's on-off state changes every second.
  
&par Directory contents 

  - SysTick/TimeBase/src/apm32e10x_it.c     Interrupt handlers
  - SysTick/TimeBase/src/main.c                      Main program

&par Hardware and Software environment

  - This example runs on APM32E103_MINI Devices.
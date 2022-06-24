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

The example shows how to configure IWDT and feed dog to prevent a system reset.
After IWDT initialization, System enters into a infinite loop, feed dog before the counter
reach a given timeout value to prevent system reset and keep LED2 blinking regulary.
Pressing KEY1 to stop feed dog will trigger system reset when the counter reach a given 
timeout value. LED3 will be lighted when a system reset is triggered by IWDT.
  
&par Directory contents 

  - IWDT/Reset/src/apm32e10x_it.c     Interrupt handlers
  - IWDT/Reset/src/main.c                      Main program

&par Hardware and Software environment

  - This example runs on APM32E103_MINI Devices.
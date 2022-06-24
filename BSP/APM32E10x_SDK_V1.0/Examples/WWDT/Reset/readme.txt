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

This example aims to show how to use WWDT. 
If  is_OverTime = 0 , System would not reset for feeding dog timely. LED2 Toggle.
Pressing KEY1 to stop feed dog will trigger system reset when the counter reach a given 
timeout value. LED3 will be lighted when a system reset is triggered by IWDT.

&par Directory contents 

  - WWDT/Reset/src/apm32e10x_it.c     Interrupt handlers
  - WWDT/Reset/src/main.c                      Main program

&par Hardware and Software environment

  - This example runs on APM32E103 MINI Devices.
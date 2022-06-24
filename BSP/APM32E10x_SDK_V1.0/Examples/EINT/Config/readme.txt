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

This example shows how to configure external interrupt lines.
In this example, 2 EINT lines (KEY1¡¢KEY2) when using the APM32E103 MINI BOARD
are configured to generate an interrupt on each falling edge. In the interrupt 
routine a led connected to a specific GPIO pin is toggled.

In this example
    - EINT0  is mapped to PA0(KEY2)
    - EINT1  is mapped to PA1(KEY1)

After EINT configuration
  when falling edge is detected on EINT0 , LED2 toggles
  when falling edge is detected on EINT1 , LED3 toggles
  
&par Directory contents 

  - EINT/Config/src/apm32e10x_it.c     Interrupt handlers
  - EINT/Config/src/main.c                      Main program

&par Hardware and Software environment

  - This example runs on APM32E103 MINI Devices.

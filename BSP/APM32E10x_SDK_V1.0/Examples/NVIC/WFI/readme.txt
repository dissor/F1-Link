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

This example describes how to use WFI event to enter sleep mode and wake up
using external interrupt.
At startup, press KEY2(PA0) to occur Wait For Interrupt(WFI) event, and device
will enter sleep mode. The device will wake up if press KEY2 again.

 phenomenon :
  - program running: LED2, LED3 blink.
  - sleep mode: LED2, LED3 off.

&par Directory contents 

  - NVIC/WFI/src/apm32e10x_int.c     Interrupt handlers
  -NVIC/WFI/src/main.c                   Main program


&par Hardware and Software environment

  - This example runs on APM32E103 MINI Devices.

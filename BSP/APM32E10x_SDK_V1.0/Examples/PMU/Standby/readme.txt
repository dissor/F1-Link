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

This example shows how to enter STANDBY mode and wake up from this mode through
RTC alarm event's rising edge. There is a infinite loop that will keep LED2 blinking in mian
program which means program is running. Press KEY1, configure RTC alarm event and then
system enters STANDBY mode. After a rising edge is generated by RTC alarm event, If system 
recover to normal state, LED2 keep blinking and light LED3 which means system wake up
from STANDBY mode.
  
&par Directory contents 

  - PMU/Standby/src/apm32e10x_it.c     Interrupt handlers
  - PMU/Standby/src/main.c                      Main program

&par Hardware and Software environment

  - This example runs on APM32E103_MINI Devices.

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
 
This example describes how to config a communication the CAN in loopback mode. 
CAN transmit a message to self. Then compare the received message with transmitted
message. 
  - Polling transmit success: The LED2 turns, otherwise LED2 turns off.
  - Interrupt transmit success: The LED3 turns, otherwise LED3 turns off.

&par Directory contents 

  - CAN/LoopBack/src/apm32e10x_int.c     Interrupt handlers
  - CAN/LoopBack/src/main.c                      Main program


&par Hardware and Software environment

  - This example runs on APM32E103_MINI Devices.
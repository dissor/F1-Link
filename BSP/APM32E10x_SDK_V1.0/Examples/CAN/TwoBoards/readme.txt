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
 
This example describes how to config a communication the CAN. CAN transmit a message
from one board to another.

Transmit：
If press the KEY1，CAN1 transmit ，the USART1 Printf“CAN1 Transmit 0x55”，LED2 turns on.
If press the KEY2，CAN2 transmit ，the USART1 Printf“CAN1 Transmit 0xAA”，LED2 turns on.

Receive：
If CAN1 receive success, the USART1 Printf“CAN1 Receive 0x55” , LED2 turns on.
                                    else “CAN1 Receive Error ”, LED3 turns on.
If CAN2 receive success, the USART1 Printf“CAN2 Receive 0xAA” , LED2 turns on.
                                                          else “CAN2 Receive Error ”,  LED3 turns on.

&par Hardware Description

    USART1_TX(PA9)  
    USART1_RX(PA10)

  - USART1 configured as follow:
  - BaudRate = 115200 
  - Word Length = USART_WordLength_8b
  - Stop Bit = USART_StopBits_1
  - Parity = USART_Parity_No
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled

&par Directory contents 

  - CAN/TwoBoards/src/apm32e10x_int.c     Interrupt handlers
  - CAN/TwoBoards/src/main.c                      Main program

&par Hardware and Software environment

  - This example runs on APM32E103_MINI Devices.
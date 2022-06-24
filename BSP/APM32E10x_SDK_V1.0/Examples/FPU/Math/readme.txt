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

This example shows how to use FPU. There are some results about sin, cos and so no
which are calculated by FPU. The results will be displayed on serial assistant through USART1.

using USART1(TX:PA9、RX:PA10).
  - USART1 configured as follow:
  - BaudRate = 115200 
  - Word Length = USART_WordLength_8b
  - Stop Bit = USART_StopBits_1
  - Parity = USART_Parity_No
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled

&par Directory contents 

  - FPU/Math/src/apm32e10x_int.c     Interrupt handlers
  - FPU/Math/src/main.c                     Main program


&par Hardware and Software environment

  - This example runs on APM32E103_MINI Devices. 
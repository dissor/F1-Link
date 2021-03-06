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

This example shows how to use the EMMC firmware library and an associate driver
to perform read and write operations on SDRAM memory from APM32E103 Devices.
If data write correctly, USART1 will print data OK.

  - USART1 configured as follow:
  - BaudRate = 115200 
  - Word Length = USART_WordLength_8b
  - Stop Bit = USART_StopBits_1
  - Parity = USART_Parity_No
  - Hardware flow control disabled (RTS and CTS signals)
  - Transmit enabled

&par Directory contents 

  - EMMC/SDRAM/src/apm32e10x_int.c     Interrupt handlers
  - EMMC/SDRAM/src/main.c                     Main program


&par Hardware and Software environment

  - This example runs on APM32E103_MINI Devices. 
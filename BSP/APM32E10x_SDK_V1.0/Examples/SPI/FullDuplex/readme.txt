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

This example describes how to use SPI peripheral.
by making a board, the master/slave full duplex communication between the SPI and UART1.
If communication success, LED2 will turn on, LED3 will blink.

Connect UART1 and SPI pins as follows:
UART1 TX   (PA9)    to SPI MOSI (PA7)
UART1 RX   (PA10)  to SPI MISO (PA6)
UART1 CLK  (PA8)   to SPI SCK   (PA5)

&par Directory contents 

  - SPI/FullDuplex/src/apm32e10x_int.c     Interrupt handlers
  - SPI/FullDuplex/src/main.c                      Main program


&par Hardware and Software environment

  - This example runs on APM32E103_MINI Devices.
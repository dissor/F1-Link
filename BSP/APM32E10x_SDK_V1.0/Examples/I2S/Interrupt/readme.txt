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

This example describes how to use I2S peripheral.
by making a communication between the I2S2 and the I2S3.
If communication success, LED2 and LED3 will turn on.

Connect I2S2 and I2S3 pins as follows:
I2S2 WS   (PB12)   to  I2S3 WS  (PA15)
I2S2 CK    (PB13)   to  I2S3 CK   (PB3)
I2S2 SD    (PB15)   to  I2S3 SD   (PB5)

&par Directory contents 

  - I2S/Interrupt/src/apm32e10x_int.c     Interrupt handlers
  - I2S/Interrupt/src/main.c                      Main program


&par Hardware and Software environment

  - This example runs on APM32E103_MINI Devices.
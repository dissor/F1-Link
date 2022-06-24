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
 
This example describes how to write the backup registers. After initialization, 
System enters into a infinite loop. if datas in the backup registers equral to the 
datas write to the registers before, LED2 keeps blinking, otherwise, LED3 keeps 
bliinking. TAMPER pin is also enabled, if the pin changes from 0 to 1 or from 1 to 0,  
The TAMPER pin generates a Tamper detection event to reset all data backup registers.

&par Directory contents 

  - BAKPR/Tamper/src/apm32e10x_int.c     Interrupt handlers
  - BAKPR/Tamper/src/main.c                      Main program


&par Hardware and Software environment

  - This example runs on APM32E103_MINI Devices. 
/*!
 * @file        main.h
 *
 * @brief       Main program body
 *
 * @version     V1.0.0
 *
 * @date        2021-07-26
 *
 */
 
#ifndef __MAIN_H
#define __MAIN_H

#include "Board.h"
#include "stdio.h"
#include <stdarg.h>
#include "apm32e10x_i2c.h"

void APM_MINI_PB_I2C_Isr(void);
void  I2C_Isr(void);
extern volatile uint8_t SMbusAlertOccurred;
#endif


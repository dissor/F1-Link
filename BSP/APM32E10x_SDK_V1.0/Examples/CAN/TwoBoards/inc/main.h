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
#include "apm32e10x_can.h"

extern uint8_t intFlag;
void CAN1_RX0_ISR(void);
void CAN2_RX0_ISR(void);

#endif


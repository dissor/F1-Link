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
#include <string.h>
#include "apm32e10x_fmc.h"
#include "apm32e10x_spi.h"

extern const uint16_t I2S3_Buffer_Tx[32];
extern uint16_t I2S2_Buffer_Rx[32];
extern volatile uint32_t txCnt;
extern volatile uint32_t rxCnt;

#endif


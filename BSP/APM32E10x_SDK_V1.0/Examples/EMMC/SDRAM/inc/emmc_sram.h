/*!
 * @file        apm3210e_eval_fsmc_sram.h
 *
 * @brief       This file contains all the functions prototypes for the apm3210e_eval_fsmc_sram firmware driver   
 *
 * @version     V1.0.0
 *
 * @date        2020-4-15
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FSMC_SRAM_H
#define __FSMC_SRAM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "apm32e10x.h"
    

void SRAM_Init(void);
void SRAM_Write(uint16_t* pBuffer, uint32_t WriteAddr, uint32_t NumHalfwordToWrite);
void SRAM_Read(uint16_t* pBuffer, uint32_t ReadAddr, uint32_t NumHalfwordToRead);

#ifdef __cplusplus
}
#endif

#endif


/*!
 * @file        apm32e10x_dbgmcu.h
 *
 * @brief       This file contains all the functions prototypes for the DBUGMCU firmware library
 *
 * @version     V1.0.0
 *
 * @date        2021-07-26
 *
 */

#ifndef __APM32E10X_DBGMCU_H
#define __APM32E10X_DBGMCU_H

#include "apm32e10x.h"

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup DBGMCU_Driver DBGMCU Driver
  @{
*/

/** @addtogroup DBGMCU_Enumerations Enumerations
  @{
*/

enum
{
    DBGMCU_SLEEP                = ((uint32_t)0x00000001),
    DBGMCU_STOP                 = ((uint32_t)0x00000002),
    DBGMCU_STANDBY              = ((uint32_t)0x00000004),
    DBGMCU_IWDT_STOP            = ((uint32_t)0x00000100),
    DBGMCU_WWDT_STOP            = ((uint32_t)0x00000200),
    DBGMCU_TMR1_STOP            = ((uint32_t)0x00000400),
    DBGMCU_TMR2_STOP            = ((uint32_t)0x00000800),
    DBGMCU_TMR3_STOP            = ((uint32_t)0x00001000),
    DBGMCU_TMR4_STOP            = ((uint32_t)0x00002000),
    DBGMCU_CAN1_STOP            = ((uint32_t)0x00004000),
    DBGMCU_I2C1_SMBUS_TIMEOUT   = ((uint32_t)0x00008000),
    DBGMCU_I2C2_SMBUS_TIMEOUT   = ((uint32_t)0x00010000),
    DBGMCU_TMR8_STOP            = ((uint32_t)0x00020000),
    DBGMCU_TMR5_STOP            = ((uint32_t)0x00040000),
    DBGMCU_TMR6_STOP            = ((uint32_t)0x00080000),
    DBGMCU_TMR7_STOP            = ((uint32_t)0x00100000),
    DBGMCU_CAN2_STOP            = ((uint32_t)0x00200000),
    DBGMCU_TMR15_STOP           = ((uint32_t)0x00400000),
    DBGMCU_TMR16_STOP           = ((uint32_t)0x00800000),
    DBGMCU_TMR17_STOP           = ((uint32_t)0x01000000),
    DBGMCU_TMR12_STOP           = ((uint32_t)0x02000000),
    DBGMCU_TMR13_STOP           = ((uint32_t)0x04000000),
    DBGMCU_TMR14_STOP           = ((uint32_t)0x08000000),
    DBGMCU_TMR9_STOP            = ((uint32_t)0x10000000),
    DBGMCU_TMR10_STOP           = ((uint32_t)0x20000000),
    DBGMCU_TMR11_STOP           = ((uint32_t)0x40000000),
};

/**@} end of group DBGMCU_Enumerations*/


/** @addtogroup DBGMCU_Fuctions Fuctions
  @{
*/

uint32_t DBGMCU_ReadDEVID(void);
uint32_t DBGMCU_ReadREVID(void);
void DBGMCU_Enable(uint32_t periph);
void DBGMCU_Disable(uint32_t periph);

/**@} end of group DBGMCU_Fuctions*/
/**@} end of group DBGMCU_Driver */
/**@} end of group Peripherals_Library*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32E10X_DBGMCU_H */

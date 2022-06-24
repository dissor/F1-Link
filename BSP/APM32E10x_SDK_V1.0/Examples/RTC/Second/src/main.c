/*!
 * @file        main.c
 *
 * @brief       Main program body
 *
 * @version     V1.0.0
 *
 * @date        2021-07-26
 *
 */

#include "main.h"

void RTC_Init(void);

/*!
 * @brief       Main program   
 *
 * @param       None
 *
 * @retval      None
 *
 */
int main(void)
{
    APM_MINI_LEDInit(LED2);
    RTC_Init();
    
    while(1)
    {

    }
}

/*!
 * @brief       RTC init
 *
 * @param       None
 *
 * @retval      None
 *
 */
void RTC_Init(void)
{
    RCM_EnableAPB1PeriphClock((RCM_APB1_PERIPH_T)RCM_APB1_PERIPH_PMU);
    PMU_EnableBackupAccess();
    
    RCM_EnableLSI();
    while(RCM_ReadStatusFlag(RCM_FLAG_LSIRDY) == RESET);
    RCM_ConfigRTCCLK(RCM_RTCCLK_LSI);
    RCM_EnableRTCCLK();
    
    RTC_WaitForSynchor();
    RTC_WaitForLastTask();
    
    RTC_EnableInterrupt(RTC_INT_SEC);
    RTC_WaitForLastTask();
   
    RTC_ConfigPrescaler(32767);
    RTC_WaitForLastTask();
    
    NVIC_EnableIRQRequest(RTC_IRQn, 0, 0);
}


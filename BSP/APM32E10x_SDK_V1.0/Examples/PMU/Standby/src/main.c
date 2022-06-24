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
void SysTick_Init(void);


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
    RCM_EnableAPB1PeriphClock((RCM_APB1_PERIPH_T)(RCM_APB1_PERIPH_PMU | RCM_APB1_PERIPH_BAKR));
    
    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);  
    APM_MINI_PBInit(BUTTON_KEY1, BUTTON_MODE_EINT);
    
    APM_MINI_LEDOn(LED2);
    APM_MINI_LEDOff(LED3);
    
    PMU_EnableWakeUpPin();
    PMU_EnableBackupAccess();
    
    RTC_Init();
    
    SysTick_Init();
    
    while(1)
    {
    }
}

/*!
 * @brief       RTC Init 
 *
 * @param       None
 *
 * @retval      None
 *
 */
void RTC_Init(void)
{
    if(PMU_ReadStatusFlag(PMU_FLAG_SB) == SET)
    {
        APM_MINI_LEDOn(LED3);
        
        PMU_ClearStatusFlag(PMU_FLAG_SB);
        
        RTC_WaitForSynchor();
    }
    else
    {
        BAKPR_Reset();
        
        RCM_ConfigLSE(RCM_LSE_OPEN);
        while(RCM_ReadStatusFlag(RCM_FLAG_LSERDY) == RESET);
        RCM_ConfigRTCCLK(RCM_RTCCLK_LSE);
        RCM_EnableRTCCLK();
        
        RTC_WaitForSynchor();
        RTC_ConfigPrescaler(32767);
        RTC_WaitForLastTask();
    }
}

/*!
 * @brief       Systick Init 
 *
 * @param       None
 *
 * @retval      None
 *
 */
void SysTick_Init(void)
{
    SysTick_Config((SystemCoreClock / 32));
    SysTick_ConfigCLKSource(SYSTICK_CLK_SOURCE_HCLK_DIV8);
    
    NVIC_SetPriority(SysTick_IRQn, 0X04);
}

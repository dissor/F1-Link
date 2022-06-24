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

volatile uint32_t tick = 0;

void Delay(void);

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
    APM_MINI_LEDInit(LED3);
    APM_MINI_PBInit(BUTTON_KEY1, BUTTON_MODE_EINT);
    
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_WWDT);
    
    if(RCM_ReadStatusFlag(RCM_FLAG_WWDTRST) == SET)
    {
        APM_MINI_LEDOn(LED3);
        RCM_ClearStatusFlag();
    }
    else
    {
        APM_MINI_LEDOff(LED3);
    }
    
    SysTick_Config(SystemCoreClock / 1000);
    
    WWDT_ConfigTimebase(WWDT_TIME_BASE_8);
    WWDT_ConfigWindowData(80);
    WWDT_Enable(127);
    
    while(1)
    {
        APM_MINI_LEDToggle(LED2);
        
        Delay();
        
        WWDT_ConfigCounter(127);
        
    }
}

/*!
 * @brief       Delay
 *
 * @param       None
 *
 * @retval      None
 *
 */
void Delay(void)
{
    tick = 0;

    while(tick < 44);
}


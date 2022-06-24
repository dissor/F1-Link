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

volatile uint32_t TimingDelay = 0;

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

    SysTick_Config(SystemCoreClock / 1000);
    
    if(RCM_ReadStatusFlag(RCM_FLAG_IWDTRST) == SET)
    {
        APM_MINI_LEDOn(LED3);
        RCM_ClearStatusFlag();
    }
    else
    {
        APM_MINI_LEDOff(LED3);
    }
    
    IWDT_EnableWriteAccess();
    IWDT_ConfigDivider(IWDT_DIVIDER_32);
    IWDT_ConfigReload(300);
    IWDT_Enable();
    
    while(1)
    {
        APM_MINI_LEDToggle(LED2);
        
        Delay();
        
        IWDT_Refresh();
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
    TimingDelay = 0;
    while(TimingDelay < 200);
}

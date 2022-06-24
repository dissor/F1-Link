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

void Delay(void);
void SetSysClock(void);

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
    GPIO_Config_T GPIO_ConfigStruct;
    
    SetSysClock();
    RCM_EnableCSS();
    
    APM_MINI_LEDInit(LED2);  
    
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOA);
    GPIO_ConfigStruct.pin = GPIO_PIN_8;
    GPIO_ConfigStruct.mode = GPIO_MODE_AF_PP;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);
    RCM_ConfigMCO(RCM_MCOCLK_SYSCLK);
    
    while(1)
    {
        APM_MINI_LEDToggle(LED2);
        Delay();
    }
}

/*!
 * @brief       Configures the System clock frequency, HCLK, PCLK2 and PCLK1 
 *
 * @param       None
 *
 * @retval      None
 *
 */
void SetSysClock(void)
{
    RCM_Reset();
    
    RCM_ConfigHSE(RCM_HSE_OPEN);
    
    if(RCM_WaitHSEReady() == SUCCESS)
    {
        FMC_EnablePrefetchBuffer();
        FMC_ConfigLatency(FMC_LATENCY_2);
        
        RCM_ConfigAHB(RCM_AHB_DIV_1);
        RCM_ConfigAPB2(RCM_APB_DIV_1);
        RCM_ConfigAPB1(RCM_APB_DIV_2);
        
        RCM_ConfigPLL(RCM_PLLSEL_HSE, RCM_PLLMF_9);
        RCM_EnablePLL();
        while(RCM_ReadStatusFlag(RCM_FLAG_PLLRDY) == RESET);
        
        RCM_ConfigSYSCLK(RCM_SYSCLK_SEL_PLL);
        while(RCM_ReadSYSCLKSource() != RCM_SYSCLK_SEL_PLL);
    }
    else
    {
        while(1);
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
    volatile uint32_t delay = 0xffff8;
    
    while(delay--);
}

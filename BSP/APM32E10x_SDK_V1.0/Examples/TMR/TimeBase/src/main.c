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
    TMR_BaseConfig_T TMR_BaseConfigStruct;
    
    APM_MINI_LEDInit(LED2);
    
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR1);
    
    TMR_BaseConfigStruct.clockDivision = TMR_CLOCK_DIV_1;
    TMR_BaseConfigStruct.countMode = TMR_COUNTER_MODE_UP;
    TMR_BaseConfigStruct.division = 71;
    TMR_BaseConfigStruct.period = 999;
    TMR_BaseConfigStruct.repetitionCounter = 0;
    TMR_ConfigTimeBase(TMR1, &TMR_BaseConfigStruct);
    
    TMR_EnableInterrupt(TMR1, TMR_INT_UPDATE);
    NVIC_EnableIRQRequest(TMR1_UP_IRQn, 0, 0);
    
    TMR_Enable(TMR1);
    
    while(1)
    {
        APM_MINI_LEDToggle(LED2);
        
        Delay();
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
    
    while(tick < 500);
}


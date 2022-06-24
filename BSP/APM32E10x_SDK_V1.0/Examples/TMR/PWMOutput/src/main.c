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
    GPIO_Config_T GPIO_ConfigStruct;
    TMR_BaseConfig_T TMR_TimeBaseStruct;
    TMR_OCConfig_T OCcongigStruct;
    
    RCM_EnableAPB2PeriphClock((RCM_APB2_PERIPH_T)(RCM_APB2_PERIPH_GPIOA | RCM_APB2_PERIPH_TMR1 | RCM_APB2_PERIPH_GPIOB));

    GPIO_ConfigStruct.pin = GPIO_PIN_13;
    GPIO_ConfigStruct.mode = GPIO_MODE_AF_PP;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOB, &GPIO_ConfigStruct);
    
    GPIO_ConfigStruct.pin = GPIO_PIN_8;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);
    
    TMR_TimeBaseStruct.clockDivision = TMR_CLOCK_DIV_1;
    TMR_TimeBaseStruct.countMode = TMR_COUNTER_MODE_UP;
    TMR_TimeBaseStruct.division = 71;
    TMR_TimeBaseStruct.period = 999;
    TMR_ConfigTimeBase(TMR1, &TMR_TimeBaseStruct);
    
    OCcongigStruct.idleState = TMR_OC_IDLE_STATE_RESET;
    OCcongigStruct.mode = TMR_OC_MODE_PWM1;
    OCcongigStruct.nIdleState = TMR_OC_NIDLE_STATE_RESET;
    OCcongigStruct.nPolarity = TMR_OC_NPOLARITY_HIGH;
    OCcongigStruct.outputNState = TMR_OC_NSTATE_ENABLE;
    OCcongigStruct.outputState = TMR_OC_STATE_ENABLE;
    OCcongigStruct.polarity = TMR_OC_POLARITY_HIGH;
    OCcongigStruct.pulse = 300;
    TMR_ConfigOC1(TMR1, &OCcongigStruct);
    
    TMR_ConfigOC1Preload(TMR1, TMR_OC_PRELOAD_ENABLE);
    TMR_EnableAUTOReload(TMR1);
    TMR_Enable(TMR1);
    TMR_EnablePWMOutputs(TMR1);
    while(1)
    {

    }
}


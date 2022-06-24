#include "mylk_mco.h"
#include "apm32e10x_gpio.h"
#include "apm32e10x_rcm.h"

/** Configure pins as
     PA8   ------> RCC_MCO
*/
void MYLK_MCO_GPIO_Init(void)
{
    GPIO_Config_T GPIO_configStruct = {0};

    /* Enable GPIO clock */
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOA);

    /*Configure GPIO pin : PA8 */
    GPIO_configStruct.mode = GPIO_MODE_AF_PP;
    GPIO_configStruct.pin = GPIO_PIN_8;
    GPIO_configStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_configStruct);
    
    RCM_ConfigMCO(RCM_MCOCLK_PLLCLK_DIV_2);
}



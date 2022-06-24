#include "mylk_led.h"


/** Configure pins as
     PE5   ------> LED3
     PE6   ------> LED2
*/
void MYLK_LED_GPIO_Init(void)
{
    GPIO_Config_T GPIO_configStruct = {0};

    /* Enable GPIO clock */
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOE);

    /*Configure GPIO pin : PE5|PE6 */
    GPIO_configStruct.mode = GPIO_MODE_OUT_PP;
    GPIO_configStruct.pin = GPIO_PIN_5|GPIO_PIN_6;
    GPIO_configStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOE, &GPIO_configStruct);
    
    GPIOE->BC = GPIO_PIN_5|GPIO_PIN_6;
}


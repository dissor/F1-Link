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

void EXTI0_Config(void);
void EXTI9_5_Config(void);


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
    
    APM_MINI_PBInit(BUTTON_KEY2, BUTTON_MODE_EINT);
    APM_MINI_PBInit(BUTTON_KEY1, BUTTON_MODE_EINT);

    
    while (1)
    {

    }
}



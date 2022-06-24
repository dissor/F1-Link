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

/** used to indicate interrupt status*/
uint8_t intStatus = 0;

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
{
    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);
    APM_MINI_LEDOff(LED2);
    APM_MINI_LEDOff(LED3);
    
    APM_MINI_PBInit(BUTTON_KEY2, BUTTON_MODE_EINT);
    
    while(1)
    {
        if (intStatus == 1)
        {
            APM_MINI_LEDOff(LED2);
            APM_MINI_LEDOff(LED3);

            /** Wait fot interrupt*/
            __WFI();
            
            intStatus = 0;
        }

        APM_MINI_LEDToggle(LED2);
        APM_MINI_LEDToggle(LED3);
        
        Delay();
    }
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
    volatile uint32_t delay = 0x5FFFF;
    
    while(delay--);
}

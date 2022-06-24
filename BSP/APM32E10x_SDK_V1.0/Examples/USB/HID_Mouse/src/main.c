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
    NVIC_ConfigPriorityGroup(NVIC_PRIORITY_GROUP_2);
    
    HidMouse_Init();
    
    while(1)
    {
        HidMouse_Proc();
    }
}


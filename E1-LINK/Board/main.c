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
#include <stdio.h>

volatile uint32_t tick = 0;

void Delay(void);
/*!
 * @brief       Main program
 *
 * @param       None
 *
 * @retval      None
 *
 * @note       
 */
int main(void)
{
    while(1)
    {
      printf("hello kkkkkk\r\n");
      
      Delay();
    }
}

void Delay(void)
{
    tick = 0;
    
    while(tick < 500);
}


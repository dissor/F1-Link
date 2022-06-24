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

#include "apm32e10x.h"
#include "apm32e10x_emmc.h"
#include "apm32e10x_rcm.h"
#include "apm32e10x_gpio.h"
#include "apm32e10x_misc.h"
#include "Board.h"
#include "main.h"
#include "emmc_sram.h"
#include <stdio.h>

/** printf function configs port */
#define DEBUG_USART  USART1

#define BUFFER_SIZE        0x400
#define WRITE_READ_ADDR    0x00

uint16_t TxBuffer[BUFFER_SIZE];
uint16_t RxBuffer[BUFFER_SIZE];

void SystemCoreClockConfig(uint32_t pllMf, uint32_t latency);
void BufferInit(uint16_t *pBuffer, uint16_t BufferLenght,uint32_t value, uint32_t Offset);

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
    uint8_t status = 0;
    USART_Config_T USART_ConfigStruct;
    
    /** Sets System clock frequency */
    SystemCoreClockConfig(6, 1);//!< 6*8 = 48Mhz
    
    /** Configures COM port. */
    USART_ConfigStruct.baudRate = 115200;
    USART_ConfigStruct.hardwareFlow = USART_HARDWARE_FLOW_NONE;
    USART_ConfigStruct.mode = USART_MODE_TX;
    USART_ConfigStruct.parity = USART_PARITY_NONE;
    USART_ConfigStruct.stopBits = USART_STOP_BIT_1;
    USART_ConfigStruct.wordLength = USART_WORD_LEN_8B;
    APM_MINI_COMInit(COM1, &USART_ConfigStruct);
    
    SRAM_Init();
    
    BufferInit(TxBuffer, BUFFER_SIZE, 0, 1);
    
    SRAM_Write(TxBuffer, WRITE_READ_ADDR, BUFFER_SIZE);
    
    SRAM_Read(RxBuffer, WRITE_READ_ADDR, BUFFER_SIZE);

    for (uint16_t cnt = 0x00; cnt < BUFFER_SIZE; cnt++)
    {
        if (RxBuffer[cnt] != TxBuffer[cnt])
        {
            status = 1;
            /** data verify Fail */
            printf("data error\r\n");
        }
    }
   
    if (!status)
    {
        /** data verify OK */
        printf("data OK\r\n");
    }
    
    while (1)
    {
    }
}

/*!
 * @brief       Fill the global buffer   
 *
 * @param       pBuffer:        pointer on the Buffer to fill
 *
 * @param       BufferSize:     size of the buffer to fill
 *
 * @param       value:          value of the buffer to fill
 *
 * @param       Offset:         step value to fill on the Buffer
 *
 * @retval      None
 *
 */
void BufferInit(uint16_t *pBuffer, uint16_t BufferLenght, uint32_t value, uint32_t Offset)
{
    uint16_t IndexTmp = 0;

    /* Put in global buffer same values */
    for (IndexTmp = 0; IndexTmp < BufferLenght; IndexTmp++ )
    {
        value = IndexTmp * Offset;
        
        pBuffer[IndexTmp] = value;
    }
}

/*!
 * @brief       Sets System clock frequency
 *
 * @param       pllMf  : PLL multiplication factor
 *                       This parameter can be RCM_PLLMF_x where x can be a value from 2 to 16.
 *
 * @param       latency: the FMC Latency value.
 *
 * @retval      None
 *
 * @note
 */
void SystemCoreClockConfig(uint32_t pllMf, uint32_t latency)
{
    __IO uint32_t i;

    if (!(RCM->CTRL_B.HSERDYFLG))
    {
        RCM->CTRL_B.HSEEN= BIT_SET;

        for (i = 0; i < HSE_STARTUP_TIMEOUT; i++)
        {
            if (RCM->CTRL_B.HSERDYFLG)
            {
                break;
            }
        }
    }

    if (RCM->CTRL_B.HSERDYFLG)
    {
        /** HSelect HSE as system clock source */
        RCM->CFG_B.SCLKSW = 0x01;

        /** Enable Prefetch Buffer */
        FMC->CTRL1_B.PBEN = BIT_SET;
        /* Flash latency wait state */
        FMC->CTRL1_B.WS = latency;

        /** HCLK = SYSCLK */
        RCM->CFG_B.AHBPSC= 0X00;
        /** PCLK2 = HCLK */
        RCM->CFG_B.APB2PSC= 0;
        /** PCLK1 = HCLK / 2 */
        RCM->CFG_B.APB1PSC = 4;

        /** Disable PLL */
        RCM->CTRL_B.PLLEN = 0;

        /** PLL: HSE * PLLm */
        RCM->CFG_B.PLLSRCSEL = 1;
        RCM->CFG_B.PLLMULCFG = (pllMf - 2);

        /** Enable PLL */
        RCM->CTRL_B.PLLEN = 1;

        /** Wait PLL Ready */
        while (RCM->CTRL_B.PLLRDYFLG == BIT_RESET);

        /** Select PLL as system clock source */
        RCM->CFG_B.SCLKSW = 2;

        /** Wait till PLL is used as system clock source */
        while (RCM->CFG_B.SCLKSWSTS!= 0x02);
    }
}

/*!
 * @brief       delay  
 *
 * @param       None
 *
 * @retval      None
 *
 */
void Delay(uint32_t cnt)
{
    while(cnt--)
    {
        __NOP();
    }
}

/*!
* @brief       Redirect C Library function printf to serial port.
*              After Redirection, you can use printf function.
*
* @param       ch:  The characters that need to be send.
*
* @param       *f:  pointer to a FILE that can recording all information
*              needed to control a stream
*
* @retval      The characters that need to be send.
*
* @note
*/
int fputc(int ch, FILE* f)
{
    /** send a byte of data to the serial port */
    USART_TxData(DEBUG_USART, (uint8_t)ch);

    /** wait for the data to be send  */
    while (USART_ReadStatusFlag(DEBUG_USART, USART_FLAG_TXBE) == RESET);

    return (ch);
}

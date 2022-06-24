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

#define BUFFER_SIZE    114

void USART1_Init(void);
void Uartx_Printf(USART_T* USARTx, char* fmt, ...);

static const uint32_t DataBuffer[BUFFER_SIZE] =
{
    0x00001021, 0x20423063, 0x408450a5, 0x60c670e7, 0x9129a14a, 0xb16bc18c,
    0xd1ade1ce, 0xf1ef1231, 0x32732252, 0x52b54294, 0x72f762d6, 0x93398318,
    0xa35ad3bd, 0xc39cf3ff, 0xe3de2462, 0x34430420, 0x64e674c7, 0x44a45485,
    0xa56ab54b, 0x85289509, 0xf5cfc5ac, 0xd58d3653, 0x26721611, 0x063076d7,
    0x569546b4, 0xb75ba77a, 0x97198738, 0xf7dfe7fe, 0xc7bc48c4, 0x58e56886,
    0x78a70840, 0x18612802, 0xc9ccd9ed, 0xe98ef9af, 0x89489969, 0xa90ab92b,
    0x4ad47ab7, 0x6a961a71, 0x0a503a33, 0x2a12dbfd, 0xfbbfeb9e, 0x9b798b58,
    0xbb3bab1a, 0x6ca67c87, 0x5cc52c22, 0x3c030c60, 0x1c41edae, 0xfd8fcdec,
    0xad2abd0b, 0x8d689d49, 0x7e976eb6, 0x5ed54ef4, 0x2e321e51, 0x0e70ff9f,
    0xefbedfdd, 0xcffcbf1b, 0x9f598f78, 0x918881a9, 0xb1caa1eb, 0xd10cc12d,
    0xe16f1080, 0x00a130c2, 0x20e35004, 0x40257046, 0x83b99398, 0xa3fbb3da,
    0xc33dd31c, 0xe37ff35e, 0x129022f3, 0x32d24235, 0x52146277, 0x7256b5ea,
    0x95a88589, 0xf56ee54f, 0xd52cc50d, 0x34e224c3, 0x04817466, 0x64475424,
    0x4405a7db, 0xb7fa8799, 0xe75ff77e, 0xc71dd73c, 0x26d336f2, 0x069116b0,
    0x76764615, 0x5634d94c, 0xc96df90e, 0xe92f99c8, 0xb98aa9ab, 0x58444865,
    0x78066827, 0x18c008e1, 0x28a3cb7d, 0xdb5ceb3f, 0xfb1e8bf9, 0x9bd8abbb,
    0x4a755a54, 0x6a377a16, 0x0af11ad0, 0x2ab33a92, 0xed0fdd6c, 0xcd4dbdaa,
    0xad8b9de8, 0x8dc97c26, 0x5c644c45, 0x3ca22c83, 0x1ce00cc1, 0xef1fff3e,
    0xdf7caf9b, 0xbfba8fd9, 0x9ff86e17, 0x7e364e55, 0x2e933eb2, 0x0ed11ef0
};

volatile uint32_t CRCValue = 0;

void Delay(volatile uint32_t nCount);

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
    USART1_Init();
    /* Enable CRC clock */
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_CRC);
    
    /* Compute the CRC of "DataBuffer" */
    CRCValue = CRC_CalculateBlockCRC((uint32_t *)DataBuffer, BUFFER_SIZE);
    Uartx_Printf(USART1, "CRC Calculation Value = 0x%X\r\n", CRCValue);
    
    while (1)
    {
    }
}

void USART1_Init(void)
{
    GPIO_Config_T GPIO_ConfigStruct;
    USART_Config_T USART_ConfigStruct;

    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_FPU);
    RCM->CFG |= BIT27;

    RCM_EnableAPB2PeriphClock((RCM_APB2_PERIPH_T)(RCM_APB2_PERIPH_GPIOA | RCM_APB2_PERIPH_USART1));

    GPIO_ConfigStruct.mode = GPIO_MODE_AF_PP;
    GPIO_ConfigStruct.pin = GPIO_PIN_9;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);

    USART_ConfigStruct.baudRate = 115200;
    USART_ConfigStruct.hardwareFlow = USART_HARDWARE_FLOW_NONE;
    USART_ConfigStruct.mode = USART_MODE_TX;
    USART_ConfigStruct.parity = USART_PARITY_NONE;
    USART_ConfigStruct.stopBits = USART_STOP_BIT_1;
    USART_ConfigStruct.wordLength = USART_WORD_LEN_8B;
    USART_Config(USART1, &USART_ConfigStruct);

    USART_Enable(USART1);
}

/*!
 * @brief   This function used USARTx Send Byte
 *
 * @param   USARTx: USART1 or USART2
 *
 * @param   data: Send data
 *
 * @retval  None
 *
 */
void Uartx_SendByte(USART_T* USARTx, int data)
{
    if (data == '\n')
    {
        while (!(USARTx->STS & (1 << 6)));

        USARTx->DATA = '\r';
    }

    while (!(USARTx->STS & (0x01 << 6)));

    USARTx->DATA = data;
}

/*!
 * @brief   This function used USARTx Send String
 *
 * @param   USARTx: USART1 or USART2
 *
 * @param   pt: Send data
 *
 * @retval  None
 *
 */
void Uartx_SendString(USART_T* USARTx, char* pt)
{
    while (*pt)
    {
        Uartx_SendByte(USARTx, *pt++);
    }
}

/*!
 * @brief   This function used USARTx Send fmt
 *
 * @param   USARTx: USART1 or USART2
 *
 * @param   fmt: Send data
 *
 * @retval  None
 *
 */
void Uartx_Printf(USART_T* USARTx, char* fmt, ...)
{
    __va_list ap;
    char string[256];

    va_start(ap, fmt);
    vsprintf(string, fmt, ap);
    Uartx_SendString(USARTx, string);
    va_end(ap);
}

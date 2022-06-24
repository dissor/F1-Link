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

enum 
{
    FAILED,
    PASSED
};

volatile uint32_t CurrDataCounterBegin = 0;
volatile uint32_t CurrDataCounterEnd = 1;

#define BUF_SIZE  32
const uint32_t SRC_Const_Buffer[BUF_SIZE]= 
{
    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80
};
uint32_t DST_Buffer[BUF_SIZE];

void RCM_Configuration(void);
void NVIC_Configuration(void);
uint8_t Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength);

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
    DMA_Config_T    DMA_ConfigStruct;
    
    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);
    APM_MINI_LEDOff(LED2);
    APM_MINI_LEDOff(LED3);
    
    RCM_Configuration();
    NVIC_Configuration();
    
    DMA_Reset(DMA1_Channel6);
    
    DMA_ConfigStruct.peripheralBaseAddr = (uint32_t)SRC_Const_Buffer;
    DMA_ConfigStruct.memoryBaseAddr = (uint32_t)DST_Buffer;
    DMA_ConfigStruct.dir = DMA_DIR_PERIPHERAL_SRC;
    DMA_ConfigStruct.bufferSize = BUF_SIZE;
    DMA_ConfigStruct.peripheralInc = DMA_PERIPHERAL_INC_ENABLE;
    DMA_ConfigStruct.memoryInc = DMA_MEMORY_INC_ENABLE;
    DMA_ConfigStruct.peripheralDataSize = DMA_PERIPHERAL_DATA_SIZE_WOED;
    DMA_ConfigStruct.memoryDataSize = DMA_MEMORY_DATA_SIZE_WOED;
    DMA_ConfigStruct.loopMode = DMA_MODE_NORMAL;
    DMA_ConfigStruct.priority = DMA_PRIORITY_HIGH;
    DMA_ConfigStruct.M2M = DMA_M2MEN_ENABLE;
    
    DMA_Config(DMA1_Channel6, &DMA_ConfigStruct);
    
    DMA_EnableInterrupt(DMA1_Channel6, DMA_INT_TC);
    
    CurrDataCounterBegin = DMA_ReadDataNumber(DMA1_Channel6);
    
    DMA_Enable(DMA1_Channel6);
    
    while (CurrDataCounterEnd);
    
    if(Buffercmp(SRC_Const_Buffer, DST_Buffer, BUF_SIZE))
    {
        APM_MINI_LEDOn(LED2);
    }
    else
    {
        APM_MINI_LEDOn(LED3);
    }
    
    while (1)
    {

    }
}

/*!
 * @brief       Configures the different system clocks  
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RCM_Configuration(void)
{   
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_DMA1);
}
/*!
 * @brief       Configure the nested vectored interrupt controller
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void NVIC_Configuration(void)
{
    NVIC_EnableIRQRequest(DMA1_Channel6_IRQn, 0, 0);
}

/*!
 * @brief       Compares two buffers
 *
 * @param       pBuffer
 *
 * @param       pBuffer

 * @retval      PASSED: pBuffer identical to pBuffer1. FAILED: pBuffer differs from pBuffer1
 *
 * @note
 */
uint8_t Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength)
{
    while(BufferLength--)
    {
        if(*pBuffer != *pBuffer1)
        {
            return FAILED;
        }

        pBuffer++;
        pBuffer1++;
    }

    return PASSED;  
}

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

CAN_TX_MESSAGE_T   TxMessage;
CAN_RX_MESSAGE_T   RxMessage;

void USART1_Init(void);
void Uartx_Printf(USART_T* USARTx, char* fmt, ...);
void NVIC_Configuration(void);
void CAN_GPIO_Init(void);
void CAN_Config_Init(void);
void CAN_Transmit_Init(void);

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
    
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_CAN1);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_CAN2);
    NVIC_Configuration();

    /* Configures LED 2,3 */
    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);

    /* Turns selected LED Off */
    APM_MINI_LEDOff(LED2);
    APM_MINI_LEDOff(LED3);

    APM_MINI_PBInit(BUTTON_KEY1,BUTTON_MODE_GPIO);
    APM_MINI_PBInit(BUTTON_KEY2,BUTTON_MODE_GPIO);


    CAN_GPIO_Init();
    
    CAN_Config_Init();
    
    CAN_Transmit_Init();
    
    CAN_EnableInterrupt(CAN1,CAN_INT_F0MP);
    
    CAN_EnableInterrupt(CAN2,CAN_INT_F0MP);


    while(1)
    {
        
        if (APM_MINI_PBGetState(BUTTON_KEY1) == RESET)
        {
            /* Turn on led LD2 */
            APM_MINI_LEDOn(LED2);
            TxMessage.data[0]  = 0x55;
            CAN_TxMessage(CAN1,&TxMessage);
            Uartx_Printf(USART1,"CAN1 Transmit 0x55 !\r\n");
            while(APM_MINI_PBGetState(BUTTON_KEY1)== RESET);
        }
        
        if (APM_MINI_PBGetState(BUTTON_KEY2) == RESET)
        {
            /* Turn on led LD2 */
            APM_MINI_LEDOn(LED2);
            TxMessage.data[0]  = 0xAA;
            CAN_TxMessage(CAN2,&TxMessage);
            Uartx_Printf(USART1,"CAN2 Transmit 0xAA !\r\n");
            while(APM_MINI_PBGetState(BUTTON_KEY2)== RESET);
        }
    }
}

/*!
 * @brief       GPIO Init
 *
 * @param       None
 *
 * @retval      None
 *
 */
void CAN_GPIO_Init(void)
{
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_AFIO);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOB);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOD);
    
    GPIO_Config_T configStruct;
    
//    configStruct.pin   = GPIO_PIN_13;    // CAN2 Tx
//    configStruct.mode  = GPIO_MODE_AF_PP;
//    configStruct.speed = GPIO_SPEED_50MHz;
//    GPIO_Config(GPIOB, &configStruct);

//    configStruct.pin  = GPIO_PIN_12;     // CAN2 Rx
//    configStruct.mode = GPIO_MODE_IN_PU;
//    GPIO_Config(GPIOB, &configStruct);

//    GPIO_ConfigPinRemap(GPIO_REMAP1_CAN1);
//    configStruct.pin   = GPIO_PIN_9;     // CAN1 Tx remap 1
//    configStruct.mode  = GPIO_MODE_AF_PP;
//    configStruct.speed = GPIO_SPEED_50MHz;
//    GPIO_Config(GPIOB, &configStruct);
// 
//    configStruct.pin = GPIO_PIN_8;       // CAN1 Rx remap 1
//    configStruct.mode = GPIO_MODE_IN_PU;
//    GPIO_Config(GPIOB, &configStruct);
    
    GPIO_ConfigPinRemap(GPIO_REMAP2_CAN1);
    configStruct.pin   = GPIO_PIN_1;       // CAN1 Tx remap 2
    configStruct.mode  = GPIO_MODE_AF_PP;
    configStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOD, &configStruct);

    configStruct.pin = GPIO_PIN_0;         // CAN1 Rx remap 2
    configStruct.mode = GPIO_MODE_IN_PU; 
    GPIO_Config(GPIOD, &configStruct);
    
/** If user GPIO_REMAP_CAN2, The GPIO_ConfigPinRemap must user at the end. */
    GPIO_ConfigPinRemap(GPIO_REMAP_CAN2);  
    configStruct.pin   = GPIO_PIN_6;       // CAN2 Tx remap 1
    configStruct.mode  = GPIO_MODE_AF_PP;  
    configStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOB, &configStruct);

    configStruct.pin  = GPIO_PIN_5;        // CAN2 Rx remap 1
    configStruct.mode = GPIO_MODE_IN_PU;  
    GPIO_Config(GPIOB, &configStruct);
}

/*!
 * @brief       CAN Init
 *
 * @param       None
 *
 * @retval      None
 *
 */
void CAN_Config_Init(void)
{
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_CAN1);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_CAN2);
    CAN_Config_T canConfig;
    CAN_FILTER_CONFIG_T FilterStruct;
    
    CAN_Reset(CAN1);
    CAN_Reset(CAN2);
    
    CAN_ConfigStructInit(&canConfig);
    
    /* CAN1 and CAN2  init */
    canConfig.timeTrigComMode  = DISABLE;
    canConfig.autoBusOffManage = DISABLE;
    canConfig.autoWakeUpMode   = DISABLE;
    canConfig.nonAutoRetran    = DISABLE;
    canConfig.rxFIFOLockMode   = DISABLE;
    canConfig.txFIFOPriority   = ENABLE;
    canConfig.mode             = CAN_MODE_NORMAL;
    canConfig.syncJumpWidth    = CAN_SJW_1;  
    canConfig.timeSegment1     = CAN_TIME_SEGMENT1_3;
    canConfig.timeSegment2     = CAN_TIME_SEGMENT2_2;
    canConfig.prescaler = 6; 
    
    CAN_Config(CAN1,&canConfig);
    CAN_Config(CAN2,&canConfig);
    
    FilterStruct.filterNumber = 1;
    FilterStruct.filterMode = CAN_FILTER_MODE_IDMASK;
    FilterStruct.filterScale = CAN_FILTER_SCALE_32BIT;
    FilterStruct.filterIdHigh = 0x6420;
    FilterStruct.filterIdLow  = 0x0000;
    FilterStruct.filterMaskIdHigh = 0x0000;
    FilterStruct.filterMaskIdLow  = 0x0000;
    FilterStruct.filterFIFO = CAN_FILTER_FIFO_0;
    FilterStruct.filterActivation =  ENABLE;
    
    CAN_ConfigFilter(CAN1,&FilterStruct);
    CAN_ConfigFilter(CAN2,&FilterStruct);
}

/*!
 * @brief       CAN Transmit Init
 *
 * @param       None
 *
 * @retval      None
 *
 */
void CAN_Transmit_Init(void)
{
    TxMessage.stdID = 0x321;
    TxMessage.extID = 0x01;
    TxMessage.remoteTxReq   = CAN_RTXR_DATA;
    TxMessage.typeID   = CAN_TYPEID_STD;
    TxMessage.dataLengthCode   = 1;
}

/*!
 * @brief       CAN1 Rx interrupt 
 *
 * @param       None
 *
 * @retval      None
 *
 */
void CAN1_RX0_ISR(void)
{
    CAN_RxMessage(CAN1, CAN_RX_FIFO_0, &RxMessage);

    if ((RxMessage.stdID == 0x321)&&(RxMessage.typeID == CAN_TYPEID_STD)&&(RxMessage.dataLengthCode == 1)&&(RxMessage.data[0] == 0x55))
    {
      APM_MINI_LEDOn(LED2);
      Uartx_Printf(USART1,"CAN1 Receive 0x55 !\r\n");
    }
    else
    {
      APM_MINI_LEDOn(LED3);
      Uartx_Printf(USART1,"CAN1 Receive Error !\r\n");
    }
}

/*!
 * @brief       CAN2 Rx interrupt 
 *
 * @param       None
 *
 * @retval      None
 *
 */
void CAN2_RX0_ISR(void)
{
    CAN_RxMessage(CAN2, CAN_RX_FIFO_0, &RxMessage);

    if ((RxMessage.stdID == 0x321)&&(RxMessage.typeID == CAN_TYPEID_STD)&&(RxMessage.dataLengthCode == 1)&&(RxMessage.data[0] == 0xAA))
    {
      APM_MINI_LEDOn(LED2);
      Uartx_Printf(USART1,"CAN2 Receive 0xAA !\r\n");
    }
    else
    {
      APM_MINI_LEDOn(LED3);
      Uartx_Printf(USART1,"CAN2 Receive Error !\r\n");
    }
}

/*!
 * @brief       Configures NVIC 
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void NVIC_Configuration(void)
{
    NVIC_EnableIRQRequest(USBD1_LP_CAN1_RX0_IRQn, 0, 0);
    NVIC_EnableIRQRequest(USBD2_LP_CAN2_RX0_IRQn, 1, 0);
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

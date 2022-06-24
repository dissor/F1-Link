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

float a, b, s, x, y, z, ans[100], X[100] = {0, 0, 0,};
float PI = 3.14159;

uint8_t databuff;
uint32_t m = 0;

volatile uint8_t MemoryProgramStatus = PASSED;

void Uartx_Printf(USART_T* USARTx, char* fmt, ...);

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

    Uartx_Printf(USART1, "SIN:");

    for (s = 0; s < 100; s++)
    {
        ans[databuff] = 0x00;
        databuff++;
    }

    databuff = 0;

    for (s = -PI; s < 0; s = s + 0.1)
    {
        ans[databuff] = sc_math_sin(s);
        databuff++;
    }

    ans[databuff] = sc_math_sin(0);
    databuff++;

    for (s = PI; s > 0; s = s - 0.1)
    {
        ans[databuff] = sc_math_sin(s);
        databuff++;
    }

    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        Uartx_Printf(USART1, "%5.11f\n", ans[databuff]);
        databuff++;
    }

    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "COS:\n");

    for (s = 0; s < 100; s++)
    {
        ans[databuff] = 0x00;
        databuff++;
    }

    databuff = 0;

    for (s = -PI; s < 0; s = s + 0.1)
    {
        ans[databuff] = sc_math_cos(s);
        databuff++;
    }

    ans[databuff] = sc_math_cos(0);
    databuff++;

    for (s = PI; s > 0; s = s - 0.1)
    {
        ans[databuff] = sc_math_cos(s);
        databuff++;
    }

    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        Uartx_Printf(USART1, "%5.11f\n", ans[databuff]);
        databuff++;
    }

    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "TAN:\n");

    for (s = 0; s < 100; s++)
    {
        ans[databuff] = 0x00;
        databuff++;
    }

    databuff = 0;

    for (s = -PI; s < 0; s = s + 0.1)
    {
        ans[databuff] = sc_math_tan(s);
        databuff++;
    }

    ans[databuff] = sc_math_tan(0);
    databuff++;

    for (s = PI; s > 0; s = s - 0.1)
    {
        ans[databuff] = sc_math_tan(s);
        databuff++;
    }

    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        Uartx_Printf(USART1, "%5.11f\n", ans[databuff]);
        databuff++;
    }

    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "ATAN:\n");

    for (s = 0; s < 100; s++)
    {
        ans[databuff] = 0x00;
        databuff++;
    }

    databuff = 0;

    for (s = -PI; s < 0; s = s + 0.1)
    {
        ans[databuff] = sc_math_atan(s);
        databuff++;
    }

    ans[databuff] = sc_math_atan(0);
    databuff++;

    for (s = PI; s > 0; s = s - 0.1)
    {
        ans[databuff] = sc_math_atan(s);
        databuff++;
    }

    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        Uartx_Printf(USART1, "%5.11f\n", ans[databuff]);
        databuff++;
    }

    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "ASIN:\n");

    for (s = 0; s < 100; s++)
    {
        ans[databuff] = 0x00;
        databuff++;
    }

    databuff = 0;

    for (s = -1; s <= 1; s = s + 0.1)
    {
        ans[databuff] = sc_math_asin(s);
        databuff++;
    }

    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        Uartx_Printf(USART1, "%5.11f\n", ans[databuff]);
        databuff++;
    }

    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "ACOS:\n");

    for (s = 0; s < 100; s++)
    {
        ans[databuff] = 0x00;
        databuff++;
    }

    databuff = 0;

    for (s = -1; s <= 1; s = s + 0.1)
    {
        ans[databuff] = sc_math_acos(s);
        databuff++;
    }

    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        Uartx_Printf(USART1, "%5.11f\n", ans[databuff]);
        databuff++;
    }

    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "ATAN2:\n");

    for (s = 0; s < 100; s++)
    {
        ans[databuff] = 0x00;
        databuff++;
    }

    databuff = 0;


    for (s = -PI; s < 0; s = s + 0.1)
    {
        a = s;
        b = s + 0.1;
        ans[databuff] = sc_math_atan2(b, a);
        databuff++;
    }

    a = s;
    b = s + 0.1;
    ans[databuff] = sc_math_atan2(0, 0);
    databuff++;


    for (s = PI; s > 0; s = s - 0.1)
    {
        a = s;
        b = s - 0.1;
        ans[databuff] = sc_math_atan2(b, a);
        databuff++;
    }

    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        Uartx_Printf(USART1, "%5.11f\n", ans[databuff]);
        databuff++;
    }

    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "invsqrt:\n");
    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        ans[databuff] = sc_math_invsqrt(databuff);
        databuff++;
    }

    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        Uartx_Printf(USART1, "%5.11f\n", ans[databuff]);
        databuff++;
    }

    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "mac:\n");

    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        x = s;
        y = s + 1;
        z = s + 2;
        ans[databuff] = sc_math_mac(x, y, z);
        databuff++;
    }

    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        Uartx_Printf(USART1, "%f\n", ans[databuff]);
        databuff++;
    }

    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "sum_N:\n");
    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        X[databuff] = s;
        databuff++;
    }

    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        ans[databuff] = sc_math_sum_N(X, databuff);
        databuff++;
    }

    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        Uartx_Printf(USART1, "%5.11f\n", ans[databuff]);
        databuff++;
    }

    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "sub_N:\n");

    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        X[databuff] = 100 - s;
        databuff++;
    }

    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        ans[databuff] = sc_math_sub_N(X, databuff);
        databuff++;
    }

    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        Uartx_Printf(USART1, "%5.11f\n", ans[databuff]);
        databuff++;
    }

    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "prdct:\n");

    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        X[databuff] = s + 1;
        databuff++;
    }

    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        ans[databuff] = sc_math_prdct(X, databuff);
        databuff++;
    }

    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        Uartx_Printf(USART1, "%5.11f\n", ans[databuff]);
        databuff++;
    }

    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "\n");
    Uartx_Printf(USART1, "sumsq:\n");
    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        X[databuff] = 100 - s;
        databuff++;
    }

    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        ans[databuff] = sc_math_sumsq(X, databuff);
        databuff++;
    }

    databuff = 0;

    for (s = 0; s < 100; s++)
    {
        Uartx_Printf(USART1, "%5.11f\n", ans[databuff]);
        databuff++;
    }
    
    while (1)
    {
    }
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

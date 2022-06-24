/*!
 * @file        apm32e10x_it.c
 *
 * @brief       Main Interrupt Service Routines
 *
 * @version     V1.0.0
 *
 * @date        2021-07-26
 *
 */

#include "main.h"
#include "apm32e10x_it.h"

/*!
 * @brief   This function handles NMI exception   
 *
 * @param   None
 *
 * @retval  None
 *
 */     
void NMI_Handler(void)
{
}

/*!
 * @brief   This function handles Hard Fault exception  
 *
 * @param   None
 *
 * @retval  None
 *
 */ 
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/*!
 * @brief   This function handles Memory Manage exception  
 *
 * @param   None
 *
 * @retval  None
 *
 */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

/*!
 * @brief   This function handles Bus Fault exception  
 *
 * @param   None
 *
 * @retval  None
 *
 */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}
/*!
 * @brief   This function handles Usage Fault exception 
 *
 * @param   None
 *
 * @retval  None
 *
 */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

/*!
 * @brief   This function handles SVCall exception 
 *
 * @param   None
 *
 * @retval  None
 *
 */
void SVC_Handler(void)
{
}

/*!
 * @brief   This function handles Debug Monitor exception 
 *
 * @param   None
 *
 * @retval  None
 *
 */
void DebugMon_Handler(void)
{
}

/*!
 * @brief   This function handles PendSV_Handler exception 
 *
 * @param   None
 *
 * @retval  None
 *
 */

void PendSV_Handler(void)
{
}

/*!
 * @brief   This function handles SysTick Handler 
 *
 * @param   None
 *
 * @retval  None
 *
 */
void SysTick_Handler(void)
{
}

/*!
 * @brief   This function handles SPI3 Handler 
 *
 * @param   None
 *
 * @retval  None
 *
 */
void SPI3_IRQHandler(void)
{
    /* Check the interrupt source */
    if (SPI_I2S_ReadIntFlag(SPI3, SPI_I2S_INT_TXBE) == SET) 
    {
        /* Send a data from I2S3 */
        SPI_I2S_TxData(SPI3, I2S3_Buffer_Tx[txCnt++]);
    }

    /* Check the end of buffer transfer */
    if (rxCnt == 32)
    {
        /* Disable the I2S3 TXE interrupt to end the communication */
        SPI_I2S_DisableInterrupt(SPI3, SPI_I2S_INT_TXBE); 
    }
}

/*!
 * @brief   This function handles SPI2 Handler 
 *
 * @param   None
 *
 * @retval  None
 *
 */
void SPI2_IRQHandler(void)
{
    /* Check the interrupt source */
    if (SPI_I2S_ReadIntFlag(SPI2, SPI_I2S_INT_RXBNE) == SET)
    {
        /* Store the I2S2 received data in the relative data table */
        I2S2_Buffer_Rx[rxCnt++] = SPI_I2S_RxData(SPI2);
    }
}

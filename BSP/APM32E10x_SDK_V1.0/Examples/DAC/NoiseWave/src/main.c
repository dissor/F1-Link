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

void RCM_Configuration(void);
void GPIO_Configuration(void);

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
    DAC_ConfigStruct_T DAC_ConfigStruct;
    
    RCM_Configuration();
    GPIO_Configuration();
    
    DAC_ConfigStruct.trigger = DAC_TRIGGER_SOFT;
    DAC_ConfigStruct.waveGeneration = DAC_WAVE_GENERATION_NOISE;
    DAC_ConfigStruct.maskAmplitudeSelect = DAC_LFSR_MASK_BIT11_6;
    DAC_ConfigStruct.outputBuffer = DAC_OUTPUT_BUFFER_ENBALE;
    DAC_Config((uint32_t)DAC_CHANNEL_1, &DAC_ConfigStruct);
    
    DAC_Enable(DAC_CHANNEL_1);
    
    DAC_ConfigChannel1Data(DAC_ALIGN_12BIT_L, 0XFFF0);
    
    while (1)
    {
        DAC_EnableSoftwareTrigger(DAC_CHANNEL_1);
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
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOA);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_DAC);
}
/*!
 * @brief       Configures the different GPIO ports 
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void GPIO_Configuration(void)
{
    GPIO_Config_T GPIO_ConfigStruct;
    
    GPIO_ConfigStruct.pin = GPIO_PIN_4;
    GPIO_ConfigStruct.mode = GPIO_MODE_ANALOG;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);
}

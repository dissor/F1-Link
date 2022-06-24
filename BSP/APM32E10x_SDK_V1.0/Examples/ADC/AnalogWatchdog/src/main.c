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
 * @brief   
 *
 * @param
 *
 * @retval
 *
 * @note
 */
void RCM_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);

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
    ADC_Config_T ADC_configStruct;
    
    /* System clocks configuration ---------------------------------------------*/
    RCM_Configuration();

    /* NVIC configuration ------------------------------------------------------*/
    NVIC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    /* Configure LED GPIO Pin ------------------------------------------------- */
    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDOff(LED2);

    /* ADC1 Configuration ------------------------------------------------------*/
    ADC_configStruct.mode = ADC_MODE_INDEPENDENT;
    ADC_configStruct.scanConvMode = DISABLE; 
    ADC_configStruct.continuosConvMode = ENABLE;
    ADC_configStruct.externalTrigConv = ADC_EXT_TRIG_CONV_None; 
    ADC_configStruct.dataAlign = ADC_DATA_ALIGN_RIGHT; 
    ADC_configStruct.nbrOfChannel = 1;
    ADC_Config(ADC1, &ADC_configStruct);

    /* ADC1 regular channel14 configuration */ 
    ADC_ConfigRegularChannel(ADC1, ADC_CHANNEL_14, 1, ADC_SAMPLE_TIME_13_5);

    /* Configure high and low analog watchdog thresholds */
    ADC_ConfigAnalogWatchdogThresholds(ADC1, 0x0B00, 0x0300);
    /* Configure channel14 as the single analog watchdog guarded channel */
    ADC_ConfigAnalogWatchdogSingleChannel(ADC1, ADC_CHANNEL_14);
    /* Enable analog watchdog on one regular channel */
    ADC_EnableAnalogWatchdog(ADC1, ADC_ANALOG_WATCHDOG_SINGLE_REG); 

    /* Enable AWD interrupt */
    ADC_EnableInterrupt(ADC1, ADC_INT_AWD);
    /* Enable ADC1 */
    ADC_Enable(ADC1);

    /* Enable ADC1 reset calibration register */   
    ADC_ResetCalibration(ADC1);
    /* Check the end of ADC1 reset calibration register */
    while(ADC_ReadResetCalibrationStatus(ADC1));

    /* Start ADC1 calibration */
    ADC_StartCalibration(ADC1);
    /* Check the end of ADC1 calibration */
    while(ADC_ReadCalibrationStartFlag(ADC1));

    /* Start ADC1 Software Conversion */ 
    ADC_EnableSoftwareStartConv(ADC1);

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
    /* ADCCLK = PCLK2/4 */
    RCM_ConfigADCCLK(RCM_PCLK2_DIV_4); 

    /* Enable peripheral clocks --------------------------------------------------*/
    /* Enable ADC1 and GPIO_LED clock */
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_ADC1);
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
void GPIO_Configuration(void)
{
    GPIO_Config_T configStruct;
    
    configStruct.pin = GPIO_PIN_4;
    configStruct.mode = GPIO_MODE_ANALOG;
    GPIO_Config(GPIOC, &configStruct);
}

/*!
 * @brief       Configures NVIC and Vector Table base location  
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void NVIC_Configuration(void)
{
    NVIC_EnableIRQRequest(ADC1_2_IRQn, 0, 0);
}

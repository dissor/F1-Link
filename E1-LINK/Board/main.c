#include "tx_api.h"
#include <stdio.h>
#include <stdarg.h>
#include "main.h"
//#include "adc.h"
//#include "dma.h"
//#include "rtc.h"
//#include "usart.h"
//#include "usb_device.h"
//#include "gpio.h"

#define DEMO_STACK_SIZE 1024
#define DEMO_BYTE_POOL_SIZE 2048

TX_THREAD thread_0;
TX_BYTE_POOL byte_pool_0;
UCHAR memory_area[DEMO_BYTE_POOL_SIZE];

//#define AVMAX 10
//struct
//{
//  uint16_t temp;
//  uint16_t vref;
//} AdcValue[AVMAX];
//UINT status;
//RTC_DateTypeDef sdatestructure;
//RTC_TimeTypeDef stimestructure;

//extern void SystemClock_Config(void);

// log print function
static TX_MUTEX logMut;

uint32_t LOG_Init(void)
{
	return tx_mutex_create(&logMut, "logMut", TX_NO_INHERIT);
}

int32_t LOG(const char *sFormat, ...)
{
  int32_t r;
  va_list ParamList;

  va_start(ParamList, sFormat);
  tx_mutex_get(&logMut, TX_WAIT_FOREVER);
  r = vprintf(sFormat, ParamList);
  tx_mutex_put(&logMut);
  va_end(ParamList);

  return r;
}

int main()
{
//  HAL_Init();
//  SystemClock_Config();
//  HAL_SuspendTick();
  tx_kernel_enter();
}

void thread_0_entry(ULONG thread_input);

/* Define what the initial system looks like.  */

void tx_application_define(void *first_unused_memory)
{

  CHAR *pointer = TX_NULL;

	LOG_Init();

  /* Create a byte memory pool from which to allocate the thread stacks.  */
  tx_byte_pool_create(&byte_pool_0, "byte pool 0", memory_area, DEMO_BYTE_POOL_SIZE);

  /* Put system definition stuff in here, e.g. thread creates and other assorted
     create information.  */

  /* Allocate the stack for thread 0.  */
  tx_byte_allocate(&byte_pool_0, (VOID **)&pointer, DEMO_STACK_SIZE, TX_NO_WAIT);

  /* Create the main thread.  */
  tx_thread_create(&thread_0, "thread 0", thread_0_entry, 0,
                   pointer, DEMO_STACK_SIZE,
                   1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);
}

/* Define the test threads.  */

void thread_0_entry(ULONG thread_input)
{
//  HAL_ResumeTick();
//  MX_GPIO_Init();
//  MX_DMA_Init();
//  MX_USART1_UART_Init();
//  MX_USB_DEVICE_Init();
//  MX_RTC_Init();
//  MX_ADC1_Init();
//  HAL_ADCEx_Calibration_Start(&hadc1);
//  HAL_ADC_Start_DMA(&hadc1, (uint32_t *)&AdcValue, sizeof(AdcValue) / sizeof(uint16_t));

  /* This thread simply sits in while-forever-sleep loop.  */
  while (1)
  {
//    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BIN);
//    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BIN);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//    LOG("%02d/%02d/%02d\r\n", 2000 + sdatestructure.Year, sdatestructure.Month, sdatestructure.Date);
//    LOG("%02d:%02d:%02d\r\n", stimestructure.Hours, stimestructure.Minutes, stimestructure.Seconds);

//    int32_t temp = 0.0, vref = 0.0;
//    for (uint8_t i = 0; i < AVMAX; i++)
//    {
//      temp += AdcValue[i].temp;
//      vref += AdcValue[i].vref;
//    }
//    temp /= AVMAX;
//    vref /= AVMAX;

//    LOG("MCU Temperature : %.5f\r\n", ((temp * 3300.0 / 4096 - 1410) / 4.2 + 25));
//    LOG("Vrefint value = %1.3fV \r\n", vref * 3.3f / 4096);

//    HAL_GPIO_TogglePin(LED_TSF_GPIO_Port, LED_TSF_Pin);
    printf("hello threadx\r\n");

    /* Sleep for 10 ticks.  */
    tx_thread_sleep(1000);
  }
}

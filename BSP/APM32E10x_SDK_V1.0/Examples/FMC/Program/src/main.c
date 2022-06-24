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

#if defined (APM32E10X_HD)
#define FLASH_PAGE_SIZE    ((uint16_t)0x800)
#else
#define FLASH_PAGE_SIZE    ((uint16_t)0x400)
#endif

#define BANK1_WRITE_START_ADDR  ((uint32_t)0x08008000)
#define BANK1_WRITE_END_ADDR    ((uint32_t)0x0800C000)

uint32_t EraseCounter = 0x00, Address = 0x00;
uint32_t Data = 0x3210ABCD;
uint32_t NbrOfPage = 0x00;
volatile FMC_STATUS_T FLASHStatus = FMC_STATUS_COMPLETE;
volatile uint8_t MemoryProgramStatus = PASSED;
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
    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);
    APM_MINI_LEDOff(LED2);
    APM_MINI_LEDOff(LED3);

    FMC_Unlock();
    
    NbrOfPage = (BANK1_WRITE_END_ADDR - BANK1_WRITE_START_ADDR) / FLASH_PAGE_SIZE;
    FMC_ClearStatusFlag((FMC_FLAG_T)(FMC_FLAG_OC | FMC_FLAG_PE | FMC_FLAG_WPE));
    for(EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FMC_STATUS_COMPLETE); EraseCounter++)
    {
        FLASHStatus = FMC_ErasePage(BANK1_WRITE_START_ADDR + (FLASH_PAGE_SIZE * EraseCounter));
    } 

    Address = BANK1_WRITE_START_ADDR;
    while((Address < BANK1_WRITE_END_ADDR) && (FLASHStatus == FMC_STATUS_COMPLETE))
    {
        FLASHStatus = FMC_ProgramWord(Address, Data);
        Address = Address + 4;
    }

    FMC_Lock();
    
    Address = BANK1_WRITE_START_ADDR;

    while((Address < BANK1_WRITE_END_ADDR) && (MemoryProgramStatus != FAILED))
    {
        if((*(__IO uint32_t*) Address) != Data)
        {
            MemoryProgramStatus = FAILED;
        }
        Address += 4;
    } 
    if(MemoryProgramStatus == FAILED)
    {
            APM_MINI_LEDOn(LED3);
    }
    else
    {
            APM_MINI_LEDOn(LED2);
    }

    while (1)
    {

    }
}

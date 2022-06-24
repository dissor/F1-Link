#include "mylk_TimeBase.h"

static __IO uint32_t uwTick;


/**
  * @brief  This function configures the TIM6 as a time base source.
  *         The time source is configured  to have 1ms time base with a dedicated
  *         Tick interrupt priority.
  * @retval None
  */
void TimeBase_InitTick(void)
{
  TMR_BaseConfig_T TMR_BaseConfigStruct;

  RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR6);

  TMR_BaseConfigStruct.clockDivision = TMR_CLOCK_DIV_1;
  TMR_BaseConfigStruct.countMode = TMR_COUNTER_MODE_UP;
  TMR_BaseConfigStruct.division = 120 - 1;
  TMR_BaseConfigStruct.period = 1000 - 1;
  TMR_BaseConfigStruct.repetitionCounter = 0;
  TMR_ConfigTimeBase(TMR6, &TMR_BaseConfigStruct);

  TMR_EnableInterrupt(TMR6, TMR_INT_UPDATE);
  NVIC_EnableIRQRequest(TMR6_IRQn, 0, 0);

  TMR_Enable(TMR6);
}


/**
  * @brief This function is called to increment  a global variable "uwTick"
  *        used as application time base.
  * @note In the default implementation, this variable is incremented each 1ms
  *       in SysTick ISR.
  * @retval None
  */
static void MYLK_IncTick(void)
{
  uwTick++;
}

/**
  * @brief Provides a tick value in millisecond.
  * @note  This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @retval tick value
  */
uint32_t MYLK_GetTick(void)
{
  return uwTick;
}

/**
  * @brief This function provides minimum delay (in milliseconds) based
  *        on variable incremented.
  * @note In the default implementation , SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals where uwTick
  *       is incremented.
  * @param Delay specifies the delay time length, in milliseconds.
  * @retval None
  */
void MYLK_Delay(uint32_t Delay)
{
  uint32_t tickstart = MYLK_GetTick();

  while((MYLK_GetTick() - tickstart) < Delay)
  {
  }
}

/**
  * @brief  Suspend Tick increment.
  * @note   Disable the tick increment by disabling TIM2 update interrupt.
  * @param  None
  * @retval None
  */
void MYLK_SuspendTick(void)
{
  /* Disable TIM6 update Interrupt */
}


/*!
 * @brief   This function handles TMR6 Handler
 *
 * @param   None
 *
 * @retval  None
 *
 */
void TMR6_IRQHandler(void)
{
  if(TMR_ReadIntFlag(TMR6, TMR_INT_UPDATE) == SET)
  {
    TMR_ClearIntFlag(TMR6, TMR_INT_UPDATE);
    MYLK_IncTick();
  }
}

/**
  * @brief  Resume Tick increment.
  * @note   Enable the tick increment by Enabling TIM2 update interrupt.
  * @param  None
  * @retval None
  */
void MYLK_ResumeTick(void)
{
  /* Enable TIM6 Update interrupt */
}




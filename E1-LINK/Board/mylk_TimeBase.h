#ifndef __MYLK_TIME_BASE_H__
#define __MYLK_TIME_BASE_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

void TimeBase_InitTick(void);
uint32_t MYLK_GetTick(void);
void MYLK_SuspendTick(void);
void MYLK_ResumeTick(void);
void MYLK_Delay(uint32_t Delay);

#ifdef __cplusplus
}
#endif

#endif


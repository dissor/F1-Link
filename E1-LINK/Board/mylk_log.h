#ifndef __MYLK_LOG_H__
#define __MYLK_LOG_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdio.h>

uint32_t LOG_Init(void);
int32_t LOG(const char *sFormat, ...);
void dump_hex(const uint8_t *buf, uint32_t size, uint32_t number);

#ifdef __cplusplus
}
#endif

#endif


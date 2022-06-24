#include "mylk_log.h"
#include "tx_api.h"
#include <stdarg.h>


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


/**
 * dump_hex
 *
 * @brief dump data in hex format
 *
 * @param buf: User buffer
 * @param size: Dump data size
 * @param number: The number of outputs per line
 *
 * @return void
*/
#define dump_print LOG
#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')
void dump_hex(const uint8_t *buf, uint32_t size, uint32_t number)
{
  int i, j;

  for (i = 0; i < size; i += number)
  {
    dump_print("%08X: ", i);

    for (j = 0; j < number; j++)
    {
      if (j % 8 == 0)
      {
        dump_print(" ");
      }

      if (i + j < size)
        dump_print("%02X ", buf[i + j]);
      else
        dump_print("   ");
    }

    dump_print(" ");

    for (j = 0; j < number; j++)
    {
      if (i + j < size)
      {
        dump_print("%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
      }
    }

    dump_print("\n");
  }
}



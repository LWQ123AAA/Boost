#ifndef _PUBLIC_H_
#define _PUBLIC_H_
#include "stdint.h"
#include "py32f0xx_hal.h"


#define _5MS_FLAG_COUNT 40       //5ms标志位的计数值，滴答时钟125us*40 = 5ms

typedef enum
{
  STOP,
  RUN
}PWMsTypeDef;

extern uint8_t timer_5ms_count;
extern uint8_t timer_5ms_flag;

void Error_Handler(void);

#endif


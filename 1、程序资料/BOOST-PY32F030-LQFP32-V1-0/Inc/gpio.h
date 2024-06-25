#ifndef _GPIO_H_
#define _GPIO_H_

#include "public.h"

typedef enum
{
  MODE_OUTPUT_PP,   //�������
  MODE_INPUT_UP,   //��������
  MODE_INPUT_DOWN,  //��������
  MODE_INPUT_NOUPDOWN,  //���迹����
  MODE_OUTPUT_T3CH1,  //PWM���
  MODE_EXTI,
} Mode_TypeDef;



void GPIO_INITIAL( GPIO_TypeDef *GPIOx,uint32_t GPIO_Pin,Mode_TypeDef MODE);


#endif


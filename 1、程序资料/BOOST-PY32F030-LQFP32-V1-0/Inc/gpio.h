#ifndef _GPIO_H_
#define _GPIO_H_

#include "public.h"

typedef enum
{
  MODE_OUTPUT_PP,   //推挽输出
  MODE_INPUT_UP,   //上拉输入
  MODE_INPUT_DOWN,  //下拉输入
  MODE_INPUT_NOUPDOWN,  //高阻抗输入
  MODE_OUTPUT_T3CH1,  //PWM输出
  MODE_EXTI,
} Mode_TypeDef;



void GPIO_INITIAL( GPIO_TypeDef *GPIOx,uint32_t GPIO_Pin,Mode_TypeDef MODE);


#endif


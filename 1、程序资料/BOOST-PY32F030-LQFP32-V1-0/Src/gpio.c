#include "gpio.h"

void GPIO_INITIAL( GPIO_TypeDef *GPIOx,uint32_t GPIO_Pin,Mode_TypeDef MODE)
{
  GPIO_InitTypeDef gpioinitstruct;
  
  /*≥ı ºªØ ±÷”*/
  switch((uint32_t)GPIOx)
  {
    case (uint32_t)GPIOA : 
      __HAL_RCC_GPIOA_CLK_ENABLE();break;
    case (uint32_t)GPIOB : 
      __HAL_RCC_GPIOB_CLK_ENABLE();break;
    case (uint32_t)GPIOF : 
      __HAL_RCC_GPIOF_CLK_ENABLE();break;
    default:Error_Handler();
  }
  
  gpioinitstruct.Pin = GPIO_Pin;
  gpioinitstruct.Pull = GPIO_NOPULL;
  gpioinitstruct.Speed = GPIO_SPEED_FREQ_HIGH;
 
  switch(MODE)
  {
    case MODE_INPUT_DOWN:gpioinitstruct.Mode = GPIO_MODE_INPUT;
         gpioinitstruct.Pull = GPIO_PULLDOWN;
         break;
    case MODE_OUTPUT_PP:gpioinitstruct.Mode = GPIO_MODE_OUTPUT_PP;
         break;
    case MODE_INPUT_UP:gpioinitstruct.Mode = GPIO_MODE_INPUT;
         gpioinitstruct.Pull = GPIO_PULLUP;
         break;
    case MODE_INPUT_NOUPDOWN:gpioinitstruct.Mode = GPIO_MODE_INPUT;
         break;
    case MODE_OUTPUT_T1CH2:gpioinitstruct.Mode = GPIO_MODE_AF_PP;
         gpioinitstruct.Pull = GPIO_PULLDOWN;
         gpioinitstruct.Alternate = GPIO_AF1_TIM1;
         break;
    default: break;
  }
  
  HAL_GPIO_Init(GPIOx,&gpioinitstruct);
}



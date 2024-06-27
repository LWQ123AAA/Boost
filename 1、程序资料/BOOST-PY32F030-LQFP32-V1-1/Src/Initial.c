#include "initial.h"
/**
  * @brief  系统时钟配置函数
  * @param  无
  * @retval 无
  */
void SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* 振荡器配置 */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI; /* 选择振荡器HSE,HSI,LSI */
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                          /* 开启HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                          /* HSI 1分频 */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_24MHz;  /* 配置HSI时钟24MHz */
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;                         /* 关闭HSE */
  /*RCC_OscInitStruct.HSEFreq = RCC_HSE_16_32MHz;*/
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;                         /* 关闭LSI */

  /* 配置振荡器 */
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* 时钟源配置 */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1; /* 选择配置时钟 HCLK,SYSCLK,PCLK1 */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI; /* 选择HSI作为系统时钟 */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;     /* AHB时钟 1分频 */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;      /* APB时钟 1分频 */
  /* 配置时钟源 */
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

void Systick_Initial(void)
{
    /**Configure the Systick interrupt time */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/SYSTICK_F);
    /**Configure the Systick */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);//选择SYSTICK时钟源，
  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);//设定优先级
}


TIM_HandleTypeDef    TIM3Handle;
TIM_OC_InitTypeDef  TIM3Config;

void Timer3_Initial(void)
{
  __HAL_RCC_TIM3_CLK_ENABLE();
  
  TIM3Handle.Instance = TIM3;                                                  /* 选择TIM3 */
  TIM3Handle.Init.Period            = 100;                                      /* 自动重装载值 pd  Ft = 24M/200 = 120Khz*/
  TIM3Handle.Init.Prescaler         = 1 - 1;                                 /* 预分频1*/
  TIM3Handle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                  /* 时钟不分频 */
  TIM3Handle.Init.CounterMode       = TIM_COUNTERMODE_UP;                      /* 向上计数 */
  TIM3Handle.Init.RepetitionCounter = 1 - 1;                                   /* 不重复计数 */
  TIM3Handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;          /* 自动重装载寄存器没有缓冲 */
  /* 基础时钟初始化 */
  if (HAL_TIM_PWM_Init(&TIM3Handle) != HAL_OK)
  {
    Error_Handler();
  }
  
  TIM3Config.OCMode       = TIM_OCMODE_PWM1;                                     /* 输出配置为PWM1 */
  TIM3Config.OCPolarity   = TIM_OCPOLARITY_HIGH;                                 /* OC通道输出高电平有效 */
  TIM3Config.OCFastMode   = TIM_OCFAST_DISABLE;                                  /* 输出快速使能关闭 */
  TIM3Config.OCNPolarity  = TIM_OCNPOLARITY_HIGH;                                /* OCN通道输出高电平有效 */
  TIM3Config.OCNIdleState = TIM_OCNIDLESTATE_RESET;                              /* 空闲状态OC1N输出低电平 */
  TIM3Config.OCIdleState  = TIM_OCIDLESTATE_RESET;                               /* 空闲状态OC1输出低电平 */

  TIM3Config.Pulse = 1;                                               /* CC1值 */
  /* 配置通道1,用于Boost */
  if (HAL_TIM_PWM_ConfigChannel(&TIM3Handle, &TIM3Config, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
}

void PWMB(PWMsTypeDef MODE)
{
  if(MODE == RUN)
  {
    if (HAL_TIM_PWM_Start(&TIM3Handle, TIM_CHANNEL_1) != HAL_OK) 
    { 
      Error_Handler(); 
    }
  }
  else
  {
    if (HAL_TIM_PWM_Stop(&TIM3Handle, TIM_CHANNEL_1) != HAL_OK) 
    { 
      Error_Handler(); 
    }
  }
}



#include "initial.h"
/**
  * @brief  ϵͳʱ�����ú���
  * @param  ��
  * @retval ��
  */
void SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* �������� */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI; /* ѡ������HSE,HSI,LSI */
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                          /* ����HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                          /* HSI 1��Ƶ */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_24MHz;  /* ����HSIʱ��24MHz */
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;                         /* �ر�HSE */
  /*RCC_OscInitStruct.HSEFreq = RCC_HSE_16_32MHz;*/
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;                         /* �ر�LSI */

  /* �������� */
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* ʱ��Դ���� */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1; /* ѡ������ʱ�� HCLK,SYSCLK,PCLK1 */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI; /* ѡ��HSI��Ϊϵͳʱ�� */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;     /* AHBʱ�� 1��Ƶ */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;      /* APBʱ�� 1��Ƶ */
  /* ����ʱ��Դ */
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
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);//ѡ��SYSTICKʱ��Դ��
  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);//�趨���ȼ�
}


TIM_HandleTypeDef    TIM3Handle;
TIM_OC_InitTypeDef  TIM3Config;

void Timer3_Initial(void)
{
  __HAL_RCC_TIM3_CLK_ENABLE();
  
  TIM3Handle.Instance = TIM3;                                                  /* ѡ��TIM3 */
  TIM3Handle.Init.Period            = 100;                                      /* �Զ���װ��ֵ pd  Ft = 24M/200 = 120Khz*/
  TIM3Handle.Init.Prescaler         = 1 - 1;                                 /* Ԥ��Ƶ1*/
  TIM3Handle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                  /* ʱ�Ӳ���Ƶ */
  TIM3Handle.Init.CounterMode       = TIM_COUNTERMODE_UP;                      /* ���ϼ��� */
  TIM3Handle.Init.RepetitionCounter = 1 - 1;                                   /* ���ظ����� */
  TIM3Handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;          /* �Զ���װ�ؼĴ���û�л��� */
  /* ����ʱ�ӳ�ʼ�� */
  if (HAL_TIM_PWM_Init(&TIM3Handle) != HAL_OK)
  {
    Error_Handler();
  }
  
  TIM3Config.OCMode       = TIM_OCMODE_PWM1;                                     /* �������ΪPWM1 */
  TIM3Config.OCPolarity   = TIM_OCPOLARITY_HIGH;                                 /* OCͨ������ߵ�ƽ��Ч */
  TIM3Config.OCFastMode   = TIM_OCFAST_DISABLE;                                  /* �������ʹ�ܹر� */
  TIM3Config.OCNPolarity  = TIM_OCNPOLARITY_HIGH;                                /* OCNͨ������ߵ�ƽ��Ч */
  TIM3Config.OCNIdleState = TIM_OCNIDLESTATE_RESET;                              /* ����״̬OC1N����͵�ƽ */
  TIM3Config.OCIdleState  = TIM_OCIDLESTATE_RESET;                               /* ����״̬OC1����͵�ƽ */

  TIM3Config.Pulse = 1;                                               /* CC1ֵ */
  /* ����ͨ��1,����Boost */
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



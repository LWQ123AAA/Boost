#ifndef _INITIAL_H_
#define _INITIAL_H_
#include "public.h"

#define SYSTICK_F 8000 //  SYSTICK_F µÎ´ð¶¨Ê±Æ÷ÆµÂÊ£º 8000 = 8K = 125us


#define PWMB_PIN                    GPIO_PIN_2
#define PWMB_GPIO_PORT              GPIOA
#define PWMB_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define PWMB_GPIO_CLK_DISABLE()     __HAL_RCC_GPIOA_CLK_DISABLE()

extern TIM_HandleTypeDef    TIM3Handle;
extern TIM_OC_InitTypeDef  TIM3Config;

#define Pwm_Boost_Initial()  do{ Timer3_Initial();GPIO_INITIAL(PWMB_GPIO_PORT,PWMB_PIN,MODE_OUTPUT_T3CH1);}while(0)

#define Config_Pwmb_Duty(_VALUE_)  do{ PWMB(STOP); TIM3Config.Pulse = _VALUE_ ;\
                                        if (HAL_TIM_PWM_ConfigChannel(&TIM3Handle, &TIM3Config, TIM_CHANNEL_1) != HAL_OK){\
                                          Error_Handler();} PWMB(RUN);}while(0)

void SystemClockConfig(void);
void Systick_Initial(void);
void PWMB(PWMsTypeDef MODE);
void Timer3_Initial(void);

#endif


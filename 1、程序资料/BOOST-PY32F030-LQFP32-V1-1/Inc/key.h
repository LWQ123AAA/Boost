#ifndef _KEY_H_
#define _KEY_H_

#include "public.h"

#define  MAX_LOW_COUNT  250  //长按时间 250*5ms = 1.25s
#define  MAX_HIGH_COUNT  10
#define  SHORT_COUNT  10

#define KEY_PIN                    GPIO_PIN_6
#define KEY_GPIO_PORT              GPIOA
#define KEY_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define KEY_GPIO_CLK_DISABLE()     __HAL_RCC_GPIOA_CLK_DISABLE()

typedef struct 
{
  GPIO_TypeDef* port;
  uint16_t pin;
  uint16_t low_count;
  uint16_t high_count;
  uint8_t key_short_ready;
  uint8_t key_long_flag;
  uint8_t key_short_flag;
}key_typedef;

extern key_typedef  key_power;

#define Key_Initial()  do{   GPIO_INITIAL(KEY_GPIO_PORT,KEY_PIN,MODE_INPUT_UP);\
                             uint32_t * p_power = (uint32_t*)(&(key_power.pin));\
                             for(uint8_t i = 0; i<3;i++ )\
                             {\
                              *p_power = 0;\
                              p_power++;\
                             }\
                             key_power.port = KEY_GPIO_PORT;\
                             key_power.pin = KEY_PIN;\
                        }while(0)
                        
//函数声明
void Key_Reload_Long(key_typedef* pk);
void Key_Flag_Out_Scan(void);

#endif



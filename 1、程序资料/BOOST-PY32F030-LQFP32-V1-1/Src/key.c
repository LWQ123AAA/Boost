#include "key.h"
#include "gpio.h"
#include "initial.h"
#include "comp.h"

//GPIO底层初始化 ok
//头文件整理 ok
//调用，测试 ok

key_typedef  key_power;

void Key_Reload_Long(key_typedef * pk)
{
  if( HAL_GPIO_ReadPin( pk->port,pk->pin) == GPIO_PIN_RESET ){
    if((*pk).low_count<=MAX_LOW_COUNT)
    {
      (*pk).low_count ++;
      if((*pk).low_count == SHORT_COUNT){  //滤波数 50ms
        (*pk).high_count = 0;
        (*pk).key_short_ready = 1;
      }
      if((*pk).low_count == MAX_LOW_COUNT){
        (*pk).key_long_flag = 1;
        (*pk).key_short_ready = 0;
      }
    }
  }
  else{
    if((*pk).high_count<=MAX_HIGH_COUNT){
      (*pk).high_count++;
      if((*pk).high_count == MAX_HIGH_COUNT ){
        (*pk).low_count = 0;
        if((*pk).key_short_ready == 1){
          (*pk).key_short_flag = 1;
          (*pk).key_short_ready = 0;
        }
      }
    }
  }
}

//    step += 10;
//    if( step == 60 ){
//      step = 0;
//    }
//    Config_Pwmb_Duty(step);

uint8_t step;

void Key_Flag_Out_Scan(void)
{
    if(key_power.key_short_flag == 1){
        key_power.key_short_flag = 0;
        step++;
        if(step == 1){
            Comp_Start();
        }
        else{
            Comp_Stop();
            step = 0;
        }
    }
}




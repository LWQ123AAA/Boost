/**
  ******************************************************************************
  * @file    main.c
  * @author  SHENGYANG
  * @brief   Main program body
  * @date    2024/6/11
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

int main(void)
{
  /* 初始化所有外设，Flash接口，SysTick */
    
  HAL_Init();
#if defined(RSTPIN_MODE_GPIO)
  if( READ_BIT(FLASH->OPTR, FLASH_OPTR_NRST_MODE) == OB_RESET_MODE_RESET)
#else
  if( READ_BIT(FLASH->OPTR, FLASH_OPTR_NRST_MODE) == OB_RESET_MODE_GPIO)
#endif
  {
    /* 写OPTION */
    APP_FlashOBProgram();
  }
  
  SystemClockConfig();
  
  /*初始化滴答定时器*/
  Systick_Initial();
  
  Key_Initial();
  
  Pwm_Boost_Initial();
  
  Comp_Initial();
  
  while (1)
  {
    if(timer_5ms_flag == 1){
      timer_5ms_flag = 0;
      Key_Reload_Long(&key_power);
      Key_Flag_Out_Scan();
    }
  }
}

/**
  * @brief 禁止PF2复位函数
  * @param  无
  * @retval 无
  */
static void APP_FlashOBProgram(void)
{
  FLASH_OBProgramInitTypeDef OBInitCfg;

  HAL_FLASH_Unlock();        /* 解锁FLASH */
  HAL_FLASH_OB_Unlock();     /* 解锁OPTION */

  /* 配置OPTION选项 */
  OBInitCfg.OptionType = OPTIONBYTE_USER;
  OBInitCfg.USERType = OB_USER_BOR_EN | OB_USER_BOR_LEV | OB_USER_IWDG_SW | OB_USER_WWDG_SW | OB_USER_NRST_MODE | OB_USER_nBOOT1;

#if defined(RSTPIN_MODE_GPIO)
  /* BOR不使能/BOR上升3.2,下降3.1/软件模式看门狗/GPIO功能/System memory作为启动区 */
  OBInitCfg.USERConfig = OB_BOR_DISABLE | OB_BOR_LEVEL_3p1_3p2 | OB_IWDG_SW | OB_WWDG_SW | OB_RESET_MODE_GPIO | OB_BOOT1_SYSTEM;
#else
  /* BOR不使能/BOR上升3.2,下降3.1/软件模式看门狗/RST功能/System memory作为启动区 */
  OBInitCfg.USERConfig = OB_BOR_DISABLE | OB_BOR_LEVEL_3p1_3p2 | OB_IWDG_SW | OB_WWDG_SW | OB_RESET_MODE_RESET | OB_BOOT1_SYSTEM;
#endif

  /* 启动option byte编程 */
  HAL_FLASH_OBProgram(&OBInitCfg);

  HAL_FLASH_Lock();      /* 锁定FLASH */
  HAL_FLASH_OB_Lock();   /* 锁定OPTION */

  /* 产生一个复位，option byte装载 */
  HAL_FLASH_OB_Launch();
}

/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void Error_Handler(void){
  /* 无限循环 */
  while (1)
  {
  }
}

/************************ (C) COPYRIGHT Puya *****END OF FILE****/

#include "comp.h"

COMP_HandleTypeDef  hcomp;

void Comp_Initial(void){
    hcomp.Instance = COMP1;                                              /* 选择COMP1 */
    hcomp.Init.InputMinus      = COMP_INPUT_MINUS_1_4VREFINT;               /* 负输入为VREF(1.2V)/4 */
    hcomp.Init.InputPlus       = COMP_INPUT_PLUS_IO3;                    /* 正输入选择为PA1 */
    hcomp.Init.OutputPol       = COMP_OUTPUTPOL_INVERTED;             /* COMP1极性选择为反向 */
    hcomp.Init.Mode            = COMP_POWERMODE_HIGHSPEED;               /* COMP1功耗模式选择为High speed模式 */
    hcomp.Init.Hysteresis      = COMP_HYSTERESIS_ENABLE;                /* 迟滞功能关闭 */
    hcomp.Init.WindowMode      = COMP_WINDOWMODE_DISABLE;                /* 窗口模式关闭 */
    hcomp.Init.TriggerMode     = COMP_TRIGGERMODE_NONE;     
    /* COMP1初始化 */
    if (HAL_COMP_Init(&hcomp) != HAL_OK){
        Error_Handler();
    }
}



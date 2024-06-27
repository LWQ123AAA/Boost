#include "comp.h"

COMP_HandleTypeDef  hcomp;

void Comp_Initial(void){
    hcomp.Instance = COMP1;                                              /* ѡ��COMP1 */
    hcomp.Init.InputMinus      = COMP_INPUT_MINUS_1_4VREFINT;               /* ������ΪVREF(1.2V)/4 */
    hcomp.Init.InputPlus       = COMP_INPUT_PLUS_IO3;                    /* ������ѡ��ΪPA1 */
    hcomp.Init.OutputPol       = COMP_OUTPUTPOL_INVERTED;             /* COMP1����ѡ��Ϊ���� */
    hcomp.Init.Mode            = COMP_POWERMODE_HIGHSPEED;               /* COMP1����ģʽѡ��ΪHigh speedģʽ */
    hcomp.Init.Hysteresis      = COMP_HYSTERESIS_ENABLE;                /* ���͹��ܹر� */
    hcomp.Init.WindowMode      = COMP_WINDOWMODE_DISABLE;                /* ����ģʽ�ر� */
    hcomp.Init.TriggerMode     = COMP_TRIGGERMODE_NONE;     
    /* COMP1��ʼ�� */
    if (HAL_COMP_Init(&hcomp) != HAL_OK){
        Error_Handler();
    }
}



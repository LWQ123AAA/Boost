#ifndef _COMP_H_
#define _COMP_H_

#include "public.h"

#define Comp_Start() do{ HAL_COMP_Start(&hcomp); }while(0)
#define Comp_Stop() do{ HAL_COMP_Stop(&hcomp); }while(0)

extern COMP_HandleTypeDef  hcomp;

void Comp_Initial(void);

#endif


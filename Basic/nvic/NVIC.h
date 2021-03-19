#ifndef __NVIC_H
#define __NVIC_H	 
#include "sys.h"


extern u8 INT_MARK;//中断标志位
extern vu16 ADC_DMA_IN[2]; //声明外部变量


void KEYPAD4x4_INT_INIT (void);
void JoyStick_up_down(void);

#endif

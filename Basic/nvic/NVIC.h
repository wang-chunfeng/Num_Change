#ifndef __NVIC_H
#define __NVIC_H	 
#include "sys.h"


extern u8 INT_MARK;//�жϱ�־λ
extern vu16 ADC_DMA_IN[2]; //�����ⲿ����


void KEYPAD4x4_INT_INIT (void);
void JoyStick_up_down(void);

#endif

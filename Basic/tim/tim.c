

/*
//�������ҳ�Ʒ
//����ϵ�п�����Ӧ�ó���
//��ע΢�Ź��ںţ����ҵ���
//���ҿ������������� www.DoYoung.net/YT 
//������ѿ����н�ѧ��Ƶ�����ؼ������ϣ�������������
//�������ݾ��� ����������ҳ www.doyoung.net
*/

/*
���޸���־��
1- ������


*/

#include "oled0561.h"
#include "delay.h"

#include "tim.h"

extern int flag;//����ѡ���־λ 0->������ 1->�˽��� 2->ʮ���� 3->ʮ������

//��ʱ��ʱ����㹫ʽTout = ((��װ��ֵ+1)*(Ԥ��Ƶϵ��+1))/ʱ��Ƶ��;
//���磺1�붨ʱ����װ��ֵ=9999��Ԥ��Ƶϵ��=7199

void TIM3_Init(u16 arr,u16 psc){  //TIM3 ��ʼ�� arr��װ��ֵ pscԤ��Ƶϵ��
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStrue;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʹ��TIM3
    TIM3_NVIC_Init (); //����TIM3�ж�����
	      
    TIM_TimeBaseInitStrue.TIM_Period=arr; //�����Զ���װ��ֵ
    TIM_TimeBaseInitStrue.TIM_Prescaler=psc; //Ԥ��Ƶϵ��
    TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //�������������
    TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1; //ʱ�ӵķ�Ƶ���ӣ�����һ������ʱ���ã�һ����ΪTIM_CKD_DIV1
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStrue); //TIM3��ʼ������
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);//ʹ��TIM3�ж�    
    TIM_Cmd(TIM3,ENABLE); //ʹ��TIM3
}

void TIM3_NVIC_Init (void){ //����TIM3�ж�����
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x3;	//������ռ�������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIM3_IRQHandler(void){ //TIM3�жϴ�����
    if ((flag<7)&&(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)){	//�ж��Ƿ���TIM3�ж�
		OLED_DISPLAY_CLEAR_0();
        //�˴�д���û��Լ��Ĵ������
//		switch(flag)
//		{
//			case 0: 
//				OLED_DISPLAY_CLEAR_0();
////				OLED_DISPLAY_8x16(0,3*8,'|');//�ȴ��޸�
////				delay_ms(100);
//				break;
//			case 1: 
//				OLED_DISPLAY_CLEAR_0();
////				OLED_DISPLAY_8x16(2,3*8,'|');//�ȴ��޸�
////				delay_ms(100);
//				break;
//			case 2: 
//				OLED_DISPLAY_CLEAR_0();
////				OLED_DISPLAY_8x16(4,3*8,'|');//�ȴ��޸�
////				delay_ms(100);
//				break;
//			case 3: 
//				OLED_DISPLAY_CLEAR_0();
////				OLED_DISPLAY_8x16(6,3*8,'|');//�ȴ��޸�
////				delay_ms(100);
//				break;
//			default: ;break;																		 
//		}
    }
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}

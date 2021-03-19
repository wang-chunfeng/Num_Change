/*
���޸���־������
2020.10.3 ������/unicorn 
��ģ���������ʵ�֣�����淶��ɣ�V1.0�汾��Ȼ����һ���Ĵ�����Ҫ��ʹ���з���
ͬʱ��


*/

#include "NVIC.h"
#include "delay.h"
#include "oled0561.h"
#include "adc.h"
#include "change.h"

u8 INT_MARK;//�жϱ�־λ
u8 Display_num[17] = {'.','0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
char input[17];
int i;//����ѡ���λ��
int j;//forѭ������
float k;//forѭ������
float input_0;
u8 point = 0;//������ȡר��
int flag = 0;//����ѡ���־λ 0->������ 1->�˽��� 2->ʮ���� 3->ʮ������
u8 flag_1; //����ѡ����ת��־λ������ģ��ң�н��� 0->������ 1->�˽��� 2->ʮ���� 3->ʮ�����ơ�
u8 flag_2 = 15;//��Ļ��ʾ�еı�־λ
u8 flag_3 = 1;//�������ر�־λ
u8 flag_4 = 1;//�������ر�־λ
u8 flag_5 = 1;//ģ��ң�а�������λ

int *p1;	//���ս���ת�������
float output; //���ս���ת�������
int output_1; //���ո�������
float output_2; //���ո���С������
int t;//���鵹���м���ֵ

/*******************************************************************************
* ������         : EXTI2_IRQHandler(void)
* ��������		 : ģ��ң�а����жϺ���
* ����           : ��
* ���         	 : ��
* ˵��			 ���˺����������󣬻����������λ�����Ƚ�flag������λ�Թرն�ʱ
                   ���е�����Ч����ͬʱ����flag_5Ϊ���ѭ�����Ա��ܹ�һֱ�ڴ���
				   ���н���ģ��ң�е����Ҽ�⡣
*******************************************************************************/

void  EXTI2_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line2)!=RESET){//�ж�ĳ�����ϵ��ж��Ƿ���
	  EXTI_ClearITPendingBit(EXTI_Line2); //��� LINE �ϵ��жϱ�־λ 
	  flag = 7;//��λ�����ٹرն�ʱ���ж�
	while(flag_5){
		while(ADC_DMA_IN[0]<1500)//�ж�ң���Ƿ������ƶ�
		{
			delay_ms(100);
		 	if(ADC_DMA_IN[0]>1500)//����֮���ٴ��ж��Ƿ��λ
			{
				flag_2--;//ң���ƶ�һ�Σ���־λ��һ
			      if(flag_2<5)
				  {
			       flag_2=15;
				  }
			}
		}
		while(ADC_DMA_IN[0]>2500)//�ж�ң���Ƿ������ƶ�
		{
			delay_ms(100);
		 	if(ADC_DMA_IN[0]<2500)//����֮���ٴ��ж��Ƿ��λ
			{
				flag_2++;//ң���ƶ�һ�Σ���־λ��һ
			      if(flag_2>15)
				  {
			       flag_2=5;
				  }
			}
		}
	    OLED_DISPLAY_8x16(flag_1,flag_2*8,Display_num[i]);//һֱ���ж���ˢ����ʾ
		input[15-flag_2]=Display_num[i];//ʵʱ����ֵ���浽������
	   }
	} 
}
  
/*******************************************************************************
* ������         : EXTI1_IRQHandler(void)
* ��������		 : ��ת�����������жϺ���
* ����           : ��
* ���         	 : ��
* ˵��			 ���˺����ж����ȼ���ߣ�һ������������ִ�У�������һ���������鵽
                   ���������ݵ�ת����Ȼ�����flag_1����������һ�ε�flagֵ������
				   ����Ӧ��case����У����н���ת���ĺ�������
*******************************************************************************/

void  EXTI1_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line1)!=RESET){//�ж�ĳ�����ϵ��ж��Ƿ��� 
//��ȡ�����е���
	   for(j=0;j<=(15-flag_2);j++)//��������
		 {
			if(input[j]=='.')
				point = j;		
		 }
	   if((point<=4)&&(point>0))//�����С�����֣���������������������λС��
	  	 {
	         for(j=point-1,k=0.1;j>=0 ;j--,k=k/10)//С������
	          {
		         input_0=input_0+(input[j]-48)*k;
	          }
		    for(j=point+1,k=1;j<=(15-flag_2);j++,k*=10)//��������
	          {
		         input_0=input_0+(input[j]-48)*k;
	          }
		  }
	   else//���ȫΪ����
	     {
		    for(j=0,k=1;j<=(15-flag_2);j++,k*=10)//��������
	          {
		        input_0=input_0+(input[j]-48)*k;
	          }
	     }

    switch(flag_1)//���ݽ����ж�ʱ�ı�־���ж�Ӧ�Ĳ�����0Ϊ�����ƣ�2Ϊ�˽��ƣ�4Ϊʮ���ƣ�6Ϊʮ������
  {
/*�����Ƶ��ˡ�ʮ��ʮ������ת��*/
    case 0 :
	    p1 = two_change_eight(input_0);//�˽���
	        for(j=0;(p1[j]!=100);j++); //�������飬���ص�����ֵΪ100��Ϊ���һ������ֵ���õ����鳤��
		    for(i=0;j>0;j--,i++)//������ʾ
	           {
					OLED_DISPLAY_8x16(2,(15-i)*8,p1[j-1]);//�õ����鳤��֮�������������
	           }
        output = two_change_ten(input_0); //ʮ���Ʒ���ֵΪ�����ͣ�������Ҫת�������´���ΪС��ת����
		    output_1 = (int)output;  //��ȡ��������
		    if(output-(int)output>0)	//�������С��
			  { 
	             for(j = 0; output_1 != 0; j++) //ȡ��ÿһλ��
	               {
                       p1[j] = output_1 % 10; 
                       output_1 = output_1 / 10; 
                       p1[j] += 48;  //����48������ΪASSIC
				   } 
			     for(i = 0;i < j/2;i++)//��ʱ���鵹�� 
                   {
	          	       t = p1[i];
		               p1[i] = p1[j-i-1];
		               p1[j-i-1] = t;	
	               }
					   p1[j] = '.'; //С�����ִ���
	                   output_2 = output - (unsigned int)output_2; //��ȡ��һλС��
	                   p1[j+1] = (unsigned int)(output_2 * 10); 
					   p1[j+1] += 48; 
				       output_2 =  output_2 * 10 - (unsigned int)(output_2 * 10);	//��ȡ�ڶ�λС��
	                   p1[j+2] =  (unsigned int)(output_2 * 10);
					   p1[j+2] += 48;  
					   p1[j+3] = 100;				      
			  }
			else //����С������
      	      {
	             for(j = 0; output_1 != 0; j++)  //ȡ�����֣���������
	               {
                       p1[j] = output_1 % 10; 
                       output_1 = output_1 / 10; 
                       p1[j] += 48; 
				   } 
				 for(i = 0;i < j/2;i++)//���鵹�� 
                   {
	          	       t = p1[i];
		               p1[i] = p1[j-i-1];
		               p1[j-i-1] = t;	
	               }
					   p1[j] = 100;
	     	   }
	      for(j=0;(p1[j]!=100);j++); //����������ĳ���
		  for(i=0;j>0;j--,i++)//������ʾ
	           {
			      OLED_DISPLAY_8x16(4,(15-i)*8,p1[j-1]);
	           }
        p1 = two_change_sixteen(input_0); //ʮ������
		  for(j=0;(p1[j]!=100);j++);
		  for(i=0;j>0;j--,i++)//������ʾ
	           {
				  OLED_DISPLAY_8x16(6,(15-i)*8,p1[j-1]);
	           }			    
	break;

/*�˽��Ƶ�����ʮ��ʮ������ת��  ����ṹ���Ϸ��������ƣ�����������ע��*/
    case 2 :
	    p1 = eight_change_two(input_0);//�˽���
	        for(j=0;(p1[j]!=100);j++)
			 ;
		    for(i=0;j>0;j--,i++)//������ʾ
	          {
			     OLED_DISPLAY_8x16(0,(15-i)*8,p1[j-1]);
	          }
        output = eight_change_ten(input_0); //ʮ���Ʒ���ֵΪ�����ͣ�������Ҫת�������´���ΪС��ת����
	        output_1 = (int)output;
			if(output-(int)output>0)
			  { 
	             for(j = 0; output_1 != 0; j++) 
	               {
                      p1[j] = output_1 % 10; 
                      output_1 = output_1 / 10; 
                      p1[j] += 48; 
				   } 
				 for(i = 0;i < j/2;i++)//���鵹�� 
                   {
	          	      t = p1[i];
		              p1[i] = p1[j-i-1];
		              p1[j-i-1] = t;	
	               }
					  p1[j] = '.';
	             output_2 = output - (unsigned int)output_2;
	             p1[j+1] = (unsigned int)(output_2 * 10); 
				 p1[j+1] += 48; 
			     output_2 =  output_2 * 10 - (unsigned int)(output_2 * 10);
	             p1[j+2] =  (unsigned int)(output_2 * 10); 
				 p1[j+3] = 100;				      
			  }
			else
      		  {
	             for(j = 0; output_1 != 0; j++) 
	               {
                      p1[j] = output_1 % 10; 
                      output_1 = output_1 / 10; 
                      p1[j] += 48; 
				   } 
			     for(i = 0;i < j/2;i++)//���鵹�� 
                   {
	          	      t = p1[i];
		              p1[i] = p1[j-i-1];
		              p1[j-i-1] = t;	
	               }
				 p1[j] = 100;
	     	   }
			 for(j=0;(p1[j]!=100);j++)
			 ;
		     for(i=0;j>0;j--,i++)//������ʾ
	           {
				  OLED_DISPLAY_8x16(4,(15-i)*8,p1[j-1]);
	           }
        p1 = eight_change_sixteen(input_0); //ʮ������
	        for(j=0;(p1[j]!=100);j++)
			 ;
		    for(i=0;j>0;j--,i++)//������ʾ
	          {
			     OLED_DISPLAY_8x16(6,(15-i)*8,p1[j-1]);
	          }
    break;

/*ʮ���Ƶ������ˡ�ʮ������ת��  ����ṹ���Ϸ��������ƣ�����������ע��*/
    case 4 :
        p1 = ten_change_two(input_0);
		    for(j=0;(p1[j]!=100);j++)
			;
		    for(i=0;j>0;j--,i++)//������ʾ
	          {
			     OLED_DISPLAY_8x16(0,(15-i)*8,p1[j-1]);
	          }			 
        p1 = ten_change_eight(input_0);
            for(j=0;(p1[j]!=100);j++)
			;
		    for(i=0;j>0;j--,i++)//������ʾ
	          {
			      OLED_DISPLAY_8x16(2,(15-i)*8,p1[j-1]);
	          }
        p1 = ten_change_sixteen(input_0);
			for(j=0;(p1[j]!=100);j++)
			;
		    for(i=0;j>0;j--,i++)//������ʾ
	           {
				   OLED_DISPLAY_8x16(6,(15-i)*8,p1[j-1]);
	           }
    break;

/*ʮ�����Ƶ������ˡ�ʮ����ת��  ����ṹ���Ϸ��������ƣ�����������ע��*/
    case 6 :
	    for(i = 0;i < (16-flag_2)/2;i++)//���鵹�� 
          {
	           t = input[i];
		       input[i] = input[(16-flag_2)-i-1];
		       input[(16-flag_2)-i-1] = t;	
	       }		  
        p1 = sixteen_change_two(input,16-flag_2 );
			 for(j=0;(p1[j]!=100);j++)
			 ;
		     for(i=0;j>0;j--,i++)//������ʾ
	           {
					OLED_DISPLAY_8x16(0,(15-i)*8,p1[j-1]);
	            }
        p1 = sixteen_change_eight(input,16-flag_2 );
			 for(j=0;(p1[j]!=100);j++)
			 ;
		     for(i=0;j>0;j--,i++)//������ʾ
	           {
					OLED_DISPLAY_8x16(2,(15-i)*8,p1[j-1]);
	            }
        output = sixteen_change_ten(input,16-flag_2 );//�˺�������ֵΪ�����ͣ�������Ҫ������ֵתΪ����
			 output_1 = (int)output;//������������
			 if(output-(int)output>0)
			    { 
	               for(j = 0; output_1 != 0; j++) 
	                 {
                        p1[j] = output_1 % 10; 
                        output_1 = output_1 / 10; 
                        if(p1[j] < 10) 
                            p1[j] += 48; 
//        else 
//        { 
//            switch(p1[j]) 
//            { 
//            case 10: 
//                p1[j] = 'A'; 
//                break; 
//            case 11: 
//                p1[j] = 'B'; 					   
//                break; 
//            case 12: 
//                p1[j] = 'C'; 
//                break; 
//            case 13: 
//                p1[j] = 'D'; 
//                break; 
//            case 14: 
//                p1[j] = 'E'; 
//                break; 
//            case 15: 
//                p1[j] = 'F'; 
//                break;
//			default	:
//			;
//			break; 
//            } 
//        } 
					  } 
					for(i = 0;i < j/2;i++)//���鵹�� 
                  	  {
	          	           t = p1[i];
		                   p1[i] = p1[j-i-1];
		                   p1[j-i-1] = t;	
	                  }
					 p1[j] = '.';
	                 output_2 = output - (unsigned int)output_2;
	                 p1[j+1] = (unsigned int)(output_2 * 10); 
                     if(p1[j+1] < 10) 
                       p1[j+1] += 48; 
//        else 
//        { 
//            switch(p1[j+1]) 
//            { 
//            case 10: 
//                p1[j+1] = 'A'; 
//                break; 
//            case 11: 
//                p1[j+1] = 'B'; 					   
//                break; 
//            case 12: 
//                p1[j+1] = 'C'; 
//                break; 
//            case 13: 
//                p1[j+1] = 'D'; 
//                break; 
//            case 14: 
//                p1[j+1] = 'E'; 
//                break; 
//            case 15: 
//                p1[j+1] = 'F'; 
//                break;
//			default	:
//			;
//			break; 
//            } 
//        }  
					output_2 =  output_2 * 10 - (unsigned int)(output_2 * 10);
	                p1[j+2] =  (unsigned int)(output_2 * 10);
                    if(p1[j+2] < 10) 
                      p1[j+2] += 48; 
//        else 
//        { 
//            switch(p1[j+2]) 
//            { 
//            case 10: 
//                p1[j+2] = 'A'; 
//                break; 
//            case 11: 
//                p1[j+2] = 'B'; 					   
//                break; 
//            case 12: 
//                p1[j+2] = 'C'; 
//                break; 
//            case 13: 
//                p1[j+2] = 'D'; 
//                break; 
//            case 14: 
//                p1[j+2] = 'E'; 
//                break; 
//            case 15: 
//                p1[j+2] = 'F'; 
//                break;
//			default	:
//			;
//			break; 
//            } 
//        } 
					p1[j+3] = 100;				      
				}
			  else
      			{
	               for(j = 0; output_1 != 0; j++) 
	                 {
                        p1[j] = output_1 % 10; 
                        output_1 = output_1 / 10; 
                        if(p1[j] < 10) 
                        p1[j] += 48; 
//        else 
//        { 
//            switch(p1[j]) 
//            { 
//            case 10: 
//                p1[j] = 'A'; 
//                break; 
//            case 11: 
//                p1[j] = 'B'; 					   
//                break; 
//            case 12: 
//                p1[j] = 'C'; 
//                break; 
//            case 13: 
//                p1[j] = 'D'; 
//                break; 
//            case 14: 
//                p1[j] = 'E'; 
//                break; 
//            case 15: 
//                p1[j] = 'F'; 
//                break;
//			default	:
//			;
//			break; 
//            } 
//        }
					  } 
					for(i = 0;i < j/2;i++)//���鵹�� 
                  	  {
	          	         t = p1[i];
		                 p1[i] = p1[j-i-1];
		                 p1[j-i-1] = t;	
	                  }
					p1[j] = 100;
	     	   }
		  for(j=0;(p1[j]!=100);j++)
		  ;
		  for(i=0;j>0;j--,i++)//������ʾ
	        {
			  OLED_DISPLAY_8x16(4,(15-i)*8,p1[j-1]);
	        }
	break;
    default :
    ;
    break;

  }
	EXTI_ClearITPendingBit(EXTI_Line1);   //��� LINE �ϵ��жϱ�־λ
  }     
}

/*******************************************************************************
* ������         : EXTI3_IRQHandler(void)
* ��������		 : �����жϺ���
* ����           : ��
* ���         	 : ��
* ˵��			 ���˺����ж����ȼ��������������ж�֮�䣬���Դ��ģ��ҡ�˺�����
                   ����Ӳ��ԭ�򣬴��жϴ���Ҳ��˳����������������������Ҫflag_3
				   ��flag_4������Ӧ����λ���Դﵽִֻ��һ��������Ŀ��
*******************************************************************************/

void  EXTI3_IRQHandler(void){
	if(flag_3&&(EXTI_GetITStatus(EXTI_Line3)!=RESET)){//�ж�ĳ�����ϵ��ж��Ƿ��� 
      flag_4 = 0;//�ر������ж�
	if(flag_2>=11)//����С�����λ��
	  {
		switch(flag_1)//��ʾλ������
		{
		  case 0 :
		            i++;
		            if(i>2)
		              i=0;
		  break;
		  case 2 :
		            i++;
		            if(i>8)
		              i=0;
		  break;
		  case 4 :
		            i++;
		            if(i>10)
		              i=0;
		  break;
		  case 6 :
		            i++;
		            if(i>16)
		            i=0;
		  break;
		  default :
		  ;
		  break;
		}
	  }
	else
	  {
		switch(flag_1)//��ʾλ������
		{
		  case 0 :
		            i++;
		            if(i>2)
		              i=1;
		  break;
		  case 2 :
		            i++;
		            if(i>8)
		              i=1;
		  break;
		  case 4 :
		            i++;
		            if(i>10)
		              i=1;
		  break;
		  case 6 :
		            i++;
		            if(i>16)
		              i=1;
		  break;
		  default :
		  ;
		  break;
		}	  	
	  }	  
	  delay_ms(70);
   }
      EXTI_ClearITPendingBit(EXTI_Line3);   //��� LINE �ϵ��жϱ�־λ
	  flag_3 = 1;//�򿪱���ĺ���     
}


/*******************************************************************************
* ������         : EXTI0_IRQHandler(void)
* ��������		 : �����жϺ���
* ����           : ��
* ���         	 : ��
* ˵��			 ���˺����ж����ȼ��������������ж�֮�䣬���Դ��ģ��ҡ�˺�����
                   ����Ӳ��ԭ�򣬴��жϴ���Ҳ��˳����������������������Ҫflag_3
				   ��flag_4������Ӧ����λ���Դﵽִֻ��һ��������Ŀ��
*******************************************************************************/

void  EXTI0_IRQHandler(void){
	if(flag_4&&(EXTI_GetITStatus(EXTI_Line0)!=RESET)){//�ж�ĳ�����ϵ��ж��Ƿ��� 
      flag_3 = 0;	//�ر������ж�
	if(flag_2>=11)//����С�����λ��
	{
	  switch(flag_1)//��ʾλ������
		{
		  case 0 :
		            i--;
		            if(i<0)
		              i=2;
		  break;
		  case 2 :
				    i--;
				    if(i<0)
				      i=8;
		  break;
		  case 4 :
				    i--;
				    if(i<0)
				      i=10;
		  break;
		  case 6 :
				    i--;
				    if(i<0)
				      i=16;
		  break;
		  default :
		  ;
		  break;
		}
	}
	else
    {
       switch(flag_1)//��ʾλ������
	   {
		  case 0 :
				    i--;
				    if(i<1)
				    i=2;
		  break;
		  case 2 :
				    i--;
				    if(i<1)
				      i=8;
		  break;
		  case 4 :
				    i--;
				    if(i<1)
				      i=10;
		  break;
		  case 6 :
				    i--;
				    if(i<1)
				      i=16;
		  break;
		  default :
		  ;
		  break;
		}	 
	 }	 
	  delay_ms(70);
  }
	  EXTI_ClearITPendingBit(EXTI_Line0);   //��� LINE �ϵ��жϱ�־λ
	  flag_4 = 1;     
}

/*******************************************************************************
* ������         : JoyStick_up_down(void)
* ��������		 : ģ��ң�������ƶ��жϺ���
* ����           : ��
* ���         	 : ��
* ˵��			 ����
*******************************************************************************/

void JoyStick_up_down(void){
if(ADC_DMA_IN[1]<1500)//�ж�ң���Ƿ������ƶ� ����λӦС��5
		{
			delay_ms(110);
		 	if(ADC_DMA_IN[1]>1350)//����֮���ٴ��ж��Ƿ��λ
			{
				flag = flag+2;//ң���ƶ�һ�Σ���־λ��һ
			      if(flag>6)
				  {
			       flag=0;
				    }
			flag_1 = flag;//���ճ�ʼ��־����
				OLED_DISPLAY_CLEAR_0();	//����
				OLED_DISPLAY_8x16(flag,3*8,'|');//��һ��
//				delay_ms(200);																		 
		     }			

		 }
/*�ж�ң���Ƿ������ƶ�����ǰ��Ĵ����߼���ͬ*/
	 if(ADC_DMA_IN[1]>2500)
		 {
		    delay_ms(110);
		    if(ADC_DMA_IN[1]<2650)
			{
				flag = flag-2;
			     if(flag<0)
			      {
			        flag=6;
			      }
			flag_1 = flag;//���ճ�ʼ��־����
				OLED_DISPLAY_CLEAR_0();
				OLED_DISPLAY_8x16(flag,3*8,'|');
//				delay_ms(300);							
		    }
	    }
}

//�ж�����
void KEYPAD4x4_INT_INIT (void){	 //�����жϳ�ʼ��
	NVIC_InitTypeDef  NVIC_InitStruct;	//����ṹ�����
	EXTI_InitTypeDef  EXTI_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //����GPIOʱ�� ����Ҫ�븴��ʱ��һͬ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //����GPIOʱ�� ����Ҫ�븴��ʱ��һͬ������       
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);//���ö˿��ж���Ҫ���ø���ʱ��

//��1���ж� ģ��ң�а���	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource2);  //���� GPIO  �ж�
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line2;  //�����ж���
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;              //�ж�ʹ��
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;     //�ж�ģʽΪ �ж�
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;   //�½��ش���
	
	EXTI_Init(& EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI2_IRQn;   //�ж���     
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;  //ʹ���ж�
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=3;  //��ռ���ȼ� 2
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;     //�����ȼ�  2
	NVIC_Init(& NVIC_InitStruct);
	
//��2���ж�	 ��ת����������
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);  //����  GPIO �ж�
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line1;  //�����ж���
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;              //�ж�ʹ��
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;     //�ж�ģʽΪ �ж�
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;   //�½��ش���
	
	EXTI_Init(& EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI1_IRQn;   //�ж���
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;  //ʹ���ж�
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;  //��ռ���ȼ� 2
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;     //�����ȼ�  2
	NVIC_Init(& NVIC_InitStruct);

//��3���ж�	 �����ж�
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);  //����  GPIO �ж�
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line0;  //�����ж���
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;              //�ж�ʹ��
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;     //�ж�ģʽΪ �ж�
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising_Falling;   //�½��ش���
	
	EXTI_Init(& EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;   //�ж���
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;  //ʹ���ж�
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;  //��ռ���ȼ� 2
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;     //�����ȼ�  2
	NVIC_Init(& NVIC_InitStruct);

////��4���ж�	�����ж�
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3);  //����  GPIO �ж�
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line3;  //�����ж���
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;              //�ж�ʹ��
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;     //�ж�ģʽΪ �ж�
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising_Falling;   //�½��ش���
	
	EXTI_Init(& EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI3_IRQn;   //�ж���
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;  //ʹ���ж�
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;  //��ռ���ȼ� 2
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;     //�����ȼ�  2
	NVIC_Init(& NVIC_InitStruct);

}







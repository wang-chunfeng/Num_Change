/*
《修改日志》　　
2020.10.3 汪春峰/unicorn 
此模块基本功能实现，代码规范完成，V1.0版本任然存在一定的错误，需要在使用中发现
同时。


*/

#include "NVIC.h"
#include "delay.h"
#include "oled0561.h"
#include "adc.h"
#include "change.h"

u8 INT_MARK;//中断标志位
u8 Display_num[17] = {'.','0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
char input[17];
int i;//数组选择的位数
int j;//for循环计数
float k;//for循环计数
float input_0;
u8 point = 0;//数组提取专用
int flag = 0;//进制选择标志位 0->二进制 1->八进制 2->十进制 3->十六进制
u8 flag_1; //进制选择中转标志位，用于模拟遥感接收 0->二进制 1->八进制 2->十进制 3->十六进制、
u8 flag_2 = 15;//屏幕显示列的标志位
u8 flag_3 = 1;//右旋开关标志位
u8 flag_4 = 1;//左旋开关标志位
u8 flag_5 = 1;//模拟遥感按键控制位

int *p1;	//接收进制转换的输出
float output; //接收进制转换的输出
int output_1; //接收浮点整形
float output_2; //接收浮点小数部分
int t;//数组倒置中间数值

/*******************************************************************************
* 函数名         : EXTI2_IRQHandler(void)
* 函数功能		 : 模拟遥感按键中断函数
* 输入           : 无
* 输出         	 : 无
* 说明			 ：此函数被触发后，会进行两个置位，首先将flag进行置位以关闭定时
                   器中的清屏效果，同时进入flag_5为真的循环，以便能够一直在此中
				   断中进行模拟遥感的左右检测。
*******************************************************************************/

void  EXTI2_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line2)!=RESET){//判断某个线上的中断是否发生
	  EXTI_ClearITPendingBit(EXTI_Line2); //清除 LINE 上的中断标志位 
	  flag = 7;//置位，快速关闭定时器中断
	while(flag_5){
		while(ADC_DMA_IN[0]<1500)//判断遥感是否向左移动
		{
			delay_ms(100);
		 	if(ADC_DMA_IN[0]>1500)//消抖之后再次判断是否归位
			{
				flag_2--;//遥感移动一次，标志位减一
			      if(flag_2<5)
				  {
			       flag_2=15;
				  }
			}
		}
		while(ADC_DMA_IN[0]>2500)//判断遥感是否向右移动
		{
			delay_ms(100);
		 	if(ADC_DMA_IN[0]<2500)//消抖之后再次判断是否归位
			{
				flag_2++;//遥感移动一次，标志位加一
			      if(flag_2>15)
				  {
			       flag_2=5;
				  }
			}
		}
	    OLED_DISPLAY_8x16(flag_1,flag_2*8,Display_num[i]);//一直在中断中刷新显示
		input[15-flag_2]=Display_num[i];//实时传递值保存到数组中
	   }
	} 
}
  
/*******************************************************************************
* 函数名         : EXTI1_IRQHandler(void)
* 函数功能		 : 旋转编码器按键中断函数
* 输入           : 无
* 输出         	 : 无
* 说明			 ：此函数中断优先级最高，一旦被触发将会执行，首先是一个输入数组到
                   浮点型数据的转换，然后根据flag_1所保存的最后一次的flag值，进入
				   到相应的case语句中，进行进制转换的函数调用
*******************************************************************************/

void  EXTI1_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line1)!=RESET){//判断某个线上的中断是否发生 
//提取数组中的数
	   for(j=0;j<=(15-flag_2);j++)//遍历数组
		 {
			if(input[j]=='.')
				point = j;		
		 }
	   if((point<=4)&&(point>0))//如果有小数部分，本代码仅仅适用于最多四位小数
	  	 {
	         for(j=point-1,k=0.1;j>=0 ;j--,k=k/10)//小数部分
	          {
		         input_0=input_0+(input[j]-48)*k;
	          }
		    for(j=point+1,k=1;j<=(15-flag_2);j++,k*=10)//整数部分
	          {
		         input_0=input_0+(input[j]-48)*k;
	          }
		  }
	   else//如果全为整数
	     {
		    for(j=0,k=1;j<=(15-flag_2);j++,k*=10)//整数部分
	          {
		        input_0=input_0+(input[j]-48)*k;
	          }
	     }

    switch(flag_1)//根据进入中断时的标志进行对应的操作，0为二进制，2为八进制，4为十进制，6为十六进制
  {
/*二进制到八、十、十六进制转换*/
    case 0 :
	    p1 = two_change_eight(input_0);//八进制
	        for(j=0;(p1[j]!=100);j++); //遍历数组，返回的数组值为100的为最后一个返回值，得到数组长度
		    for(i=0;j>0;j--,i++)//遍历显示
	           {
					OLED_DISPLAY_8x16(2,(15-i)*8,p1[j-1]);//得到数组长度之后输出整个数组
	           }
        output = two_change_ten(input_0); //十进制返回值为浮点型，所以需要转换，以下代码为小数转数组
		    output_1 = (int)output;  //提取整数部分
		    if(output-(int)output>0)	//如果含有小数
			  { 
	             for(j = 0; output_1 != 0; j++) //取出每一位数
	               {
                       p1[j] = output_1 % 10; 
                       output_1 = output_1 / 10; 
                       p1[j] += 48;  //加上48，保存为ASSIC
				   } 
			     for(i = 0;i < j/2;i++)//此时数组倒置 
                   {
	          	       t = p1[i];
		               p1[i] = p1[j-i-1];
		               p1[j-i-1] = t;	
	               }
					   p1[j] = '.'; //小数部分处理
	                   output_2 = output - (unsigned int)output_2; //提取第一位小数
	                   p1[j+1] = (unsigned int)(output_2 * 10); 
					   p1[j+1] += 48; 
				       output_2 =  output_2 * 10 - (unsigned int)(output_2 * 10);	//提取第二位小数
	                   p1[j+2] =  (unsigned int)(output_2 * 10);
					   p1[j+2] += 48;  
					   p1[j+3] = 100;				      
			  }
			else //不含小数部分
      	      {
	             for(j = 0; output_1 != 0; j++)  //取出数字，存入数组
	               {
                       p1[j] = output_1 % 10; 
                       output_1 = output_1 / 10; 
                       p1[j] += 48; 
				   } 
				 for(i = 0;i < j/2;i++)//数组倒置 
                   {
	          	       t = p1[i];
		               p1[i] = p1[j-i-1];
		               p1[j-i-1] = t;	
	               }
					   p1[j] = 100;
	     	   }
	      for(j=0;(p1[j]!=100);j++); //遍历出数组的长度
		  for(i=0;j>0;j--,i++)//遍历显示
	           {
			      OLED_DISPLAY_8x16(4,(15-i)*8,p1[j-1]);
	           }
        p1 = two_change_sixteen(input_0); //十六进制
		  for(j=0;(p1[j]!=100);j++);
		  for(i=0;j>0;j--,i++)//遍历显示
	           {
				  OLED_DISPLAY_8x16(6,(15-i)*8,p1[j-1]);
	           }			    
	break;

/*八进制到二、十、十六进制转换  代码结构与上方代码类似，不再做过多注释*/
    case 2 :
	    p1 = eight_change_two(input_0);//八进制
	        for(j=0;(p1[j]!=100);j++)
			 ;
		    for(i=0;j>0;j--,i++)//遍历显示
	          {
			     OLED_DISPLAY_8x16(0,(15-i)*8,p1[j-1]);
	          }
        output = eight_change_ten(input_0); //十进制返回值为浮点型，所以需要转换，以下代码为小数转数组
	        output_1 = (int)output;
			if(output-(int)output>0)
			  { 
	             for(j = 0; output_1 != 0; j++) 
	               {
                      p1[j] = output_1 % 10; 
                      output_1 = output_1 / 10; 
                      p1[j] += 48; 
				   } 
				 for(i = 0;i < j/2;i++)//数组倒置 
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
			     for(i = 0;i < j/2;i++)//数组倒置 
                   {
	          	      t = p1[i];
		              p1[i] = p1[j-i-1];
		              p1[j-i-1] = t;	
	               }
				 p1[j] = 100;
	     	   }
			 for(j=0;(p1[j]!=100);j++)
			 ;
		     for(i=0;j>0;j--,i++)//遍历显示
	           {
				  OLED_DISPLAY_8x16(4,(15-i)*8,p1[j-1]);
	           }
        p1 = eight_change_sixteen(input_0); //十六进制
	        for(j=0;(p1[j]!=100);j++)
			 ;
		    for(i=0;j>0;j--,i++)//遍历显示
	          {
			     OLED_DISPLAY_8x16(6,(15-i)*8,p1[j-1]);
	          }
    break;

/*十进制到二、八、十六进制转换  代码结构与上方代码类似，不再做过多注释*/
    case 4 :
        p1 = ten_change_two(input_0);
		    for(j=0;(p1[j]!=100);j++)
			;
		    for(i=0;j>0;j--,i++)//遍历显示
	          {
			     OLED_DISPLAY_8x16(0,(15-i)*8,p1[j-1]);
	          }			 
        p1 = ten_change_eight(input_0);
            for(j=0;(p1[j]!=100);j++)
			;
		    for(i=0;j>0;j--,i++)//遍历显示
	          {
			      OLED_DISPLAY_8x16(2,(15-i)*8,p1[j-1]);
	          }
        p1 = ten_change_sixteen(input_0);
			for(j=0;(p1[j]!=100);j++)
			;
		    for(i=0;j>0;j--,i++)//遍历显示
	           {
				   OLED_DISPLAY_8x16(6,(15-i)*8,p1[j-1]);
	           }
    break;

/*十六进制到二、八、十进制转换  代码结构与上方代码类似，不再做过多注释*/
    case 6 :
	    for(i = 0;i < (16-flag_2)/2;i++)//数组倒置 
          {
	           t = input[i];
		       input[i] = input[(16-flag_2)-i-1];
		       input[(16-flag_2)-i-1] = t;	
	       }		  
        p1 = sixteen_change_two(input,16-flag_2 );
			 for(j=0;(p1[j]!=100);j++)
			 ;
		     for(i=0;j>0;j--,i++)//遍历显示
	           {
					OLED_DISPLAY_8x16(0,(15-i)*8,p1[j-1]);
	            }
        p1 = sixteen_change_eight(input,16-flag_2 );
			 for(j=0;(p1[j]!=100);j++)
			 ;
		     for(i=0;j>0;j--,i++)//遍历显示
	           {
					OLED_DISPLAY_8x16(2,(15-i)*8,p1[j-1]);
	            }
        output = sixteen_change_ten(input,16-flag_2 );//此函数返回值为浮点型，所以需要将返回值转为数组
			 output_1 = (int)output;//接收整数部分
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
					for(i = 0;i < j/2;i++)//数组倒置 
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
					for(i = 0;i < j/2;i++)//数组倒置 
                  	  {
	          	         t = p1[i];
		                 p1[i] = p1[j-i-1];
		                 p1[j-i-1] = t;	
	                  }
					p1[j] = 100;
	     	   }
		  for(j=0;(p1[j]!=100);j++)
		  ;
		  for(i=0;j>0;j--,i++)//遍历显示
	        {
			  OLED_DISPLAY_8x16(4,(15-i)*8,p1[j-1]);
	        }
	break;
    default :
    ;
    break;

  }
	EXTI_ClearITPendingBit(EXTI_Line1);   //清除 LINE 上的中断标志位
  }     
}

/*******************************************************************************
* 函数名         : EXTI3_IRQHandler(void)
* 函数功能		 : 右旋中断函数
* 输入           : 无
* 输出         	 : 无
* 说明			 ：此函数中断优先级处于两个按键中断之间，可以打断模拟摇杆函数，
                   由于硬件原因，此中断触发也会顺带触发左旋函数，所以需要flag_3
				   与flag_4进行相应的置位，以达到只执行一个函数的目的
*******************************************************************************/

void  EXTI3_IRQHandler(void){
	if(flag_3&&(EXTI_GetITStatus(EXTI_Line3)!=RESET)){//判断某个线上的中断是否发生 
      flag_4 = 0;//关闭左旋中断
	if(flag_2>=11)//控制小数点的位数
	  {
		switch(flag_1)//显示位数限制
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
		switch(flag_1)//显示位数限制
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
      EXTI_ClearITPendingBit(EXTI_Line3);   //清除 LINE 上的中断标志位
	  flag_3 = 1;//打开本身的函数     
}


/*******************************************************************************
* 函数名         : EXTI0_IRQHandler(void)
* 函数功能		 : 左旋中断函数
* 输入           : 无
* 输出         	 : 无
* 说明			 ：此函数中断优先级处于两个按键中断之间，可以打断模拟摇杆函数，
                   由于硬件原因，此中断触发也会顺带触发左旋函数，所以需要flag_3
				   与flag_4进行相应的置位，以达到只执行一个函数的目的
*******************************************************************************/

void  EXTI0_IRQHandler(void){
	if(flag_4&&(EXTI_GetITStatus(EXTI_Line0)!=RESET)){//判断某个线上的中断是否发生 
      flag_3 = 0;	//关闭右旋中断
	if(flag_2>=11)//控制小数点的位数
	{
	  switch(flag_1)//显示位数限制
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
       switch(flag_1)//显示位数限制
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
	  EXTI_ClearITPendingBit(EXTI_Line0);   //清除 LINE 上的中断标志位
	  flag_4 = 1;     
}

/*******************************************************************************
* 函数名         : JoyStick_up_down(void)
* 函数功能		 : 模拟遥感上下移动判断函数
* 输入           : 无
* 输出         	 : 无
* 说明			 ：无
*******************************************************************************/

void JoyStick_up_down(void){
if(ADC_DMA_IN[1]<1500)//判断遥感是否向下移动 ，置位应小于5
		{
			delay_ms(110);
		 	if(ADC_DMA_IN[1]>1350)//消抖之后再次判断是否归位
			{
				flag = flag+2;//遥感移动一次，标志位加一
			      if(flag>6)
				  {
			       flag=0;
				    }
			flag_1 = flag;//接收初始标志保存
				OLED_DISPLAY_CLEAR_0();	//清屏
				OLED_DISPLAY_8x16(flag,3*8,'|');//第一行
//				delay_ms(200);																		 
		     }			

		 }
/*判断遥感是否向上移动，与前面的代码逻辑相同*/
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
			flag_1 = flag;//接收初始标志保存
				OLED_DISPLAY_CLEAR_0();
				OLED_DISPLAY_8x16(flag,3*8,'|');
//				delay_ms(300);							
		    }
	    }
}

//中断配置
void KEYPAD4x4_INT_INIT (void){	 //按键中断初始化
	NVIC_InitTypeDef  NVIC_InitStruct;	//定义结构体变量
	EXTI_InitTypeDef  EXTI_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //启动GPIO时钟 （需要与复用时钟一同启动）
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //启动GPIO时钟 （需要与复用时钟一同启动）       
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);//配置端口中断需要启用复用时钟

//第1个中断 模拟遥感按键	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource2);  //定义 GPIO  中断
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line2;  //定义中断线
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;              //中断使能
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;     //中断模式为 中断
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;   //下降沿触发
	
	EXTI_Init(& EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI2_IRQn;   //中断线     
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;  //使能中断
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=3;  //抢占优先级 2
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;     //子优先级  2
	NVIC_Init(& NVIC_InitStruct);
	
//第2个中断	 旋转编码器按键
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);  //定义  GPIO 中断
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line1;  //定义中断线
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;              //中断使能
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;     //中断模式为 中断
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;   //下降沿触发
	
	EXTI_Init(& EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI1_IRQn;   //中断线
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;  //使能中断
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;  //抢占优先级 2
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;     //子优先级  2
	NVIC_Init(& NVIC_InitStruct);

//第3个中断	 右旋中断
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);  //定义  GPIO 中断
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line0;  //定义中断线
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;              //中断使能
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;     //中断模式为 中断
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising_Falling;   //下降沿触发
	
	EXTI_Init(& EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;   //中断线
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;  //使能中断
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;  //抢占优先级 2
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;     //子优先级  2
	NVIC_Init(& NVIC_InitStruct);

////第4个中断	左旋中断
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3);  //定义  GPIO 中断
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line3;  //定义中断线
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;              //中断使能
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;     //中断模式为 中断
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising_Falling;   //下降沿触发
	
	EXTI_Init(& EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI3_IRQn;   //中断线
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;  //使能中断
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;  //抢占优先级 2
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;     //子优先级  2
	NVIC_Init(& NVIC_InitStruct);

}







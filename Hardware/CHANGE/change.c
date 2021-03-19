/*
《修改日志》　　
2020.10.3 汪春峰/unicorn 
此模块基本功能实现，代码规范完成，V1.0版本任然存在一定的错误，需要在使用中发现
同时，keil4中的文件为最新版本，电脑中的模块测试如果出错，则以此文件转换函数为准，
进行修改。


*/



#include "change.h"

/*二进制到八、十、十六进制转换函数*/
/*******************************************************************************
* 函数名         : two_change_eight(float num)
* 函数功能		 : 二到八进制转换函数
* 输入           : 浮点型数据
* 输出         	 : int型数组首地址
* 注意			 ：此函数调用的是二到十进制，再用十到八进制进行转换
*******************************************************************************/

int* two_change_eight(float num) 
{ 
        float result = 0;
//        float two_change_ten(float num); 	//单独测试时需要打开这两行代码进行函数声明
//        int* ten_change_eight(float num); 		       
		result = two_change_ten(num);
		return (ten_change_eight(result)); 
}


/*******************************************************************************
* 函数名         : two_change_ten(float num)
* 函数功能		 : 二到十进制转换函数
* 输入           : 浮点型数据
* 输出         	 : 浮点型数据
* 注意			 ：小数部分的转换，只能处理四位小数
*******************************************************************************/

float two_change_ten(float num) 
{
      int j;
      float i;
	  unsigned int num_1;//接收整形变量
	  unsigned int num_2;//对小数部分的数据进行处理
      float result = 0;	 //返回结果
      num_1 = (unsigned int)num; //接收整数部分
	if ((num - (unsigned int)num)>0) //判断是否含有小数
   {	
      for(i = 1; num_1 != 0; i *= 2) //取出每一位，依次*2的次方
       {  
            result += (num_1 % 10) * i; 
            num_1 = num_1 / 10; 
       }
	  num_2 = num*10000;
      for(i = 1.0/(2*2*2*2),j=1; j < 5; i *= 2,j++) //小数部分的转换，只能处理四位小数，首先放大一万倍，然后取出来进行操作
       {  
            result += ((unsigned int)num_2 % 10) * i; 
            num_2 = num_2 / 10; 
       }
	   	return result;	
	}
	else //处理整数部分
	{
     for(i = 1; num_1 != 0; i *= 2) //取出每一位，依次*2的次方
       {  
            result += (num_1 % 10) * i; 
            num_1 = num_1 / 10; 
       }
	   	 return result;		
	}	
}


/*******************************************************************************
* 函数名         : two_change_sixteen(float num)
* 函数功能		 : 二到十六进制转换函数
* 输入           : 浮点型数据
* 输出         	 : int型数组首地址
* 注意			 ：此函数调用的是二到十，十再到八
*******************************************************************************/

int* two_change_sixteen(float num) 
{
        float result = 0;
//        float two_change_ten(float num); 		//单独测试时需要打开这两行代码进行函数声明
//        int* ten_change_sixteen(float num); 		       
		result = two_change_ten(num);
		return (ten_change_sixteen(result)); 

}
 

/*八进制到二、十、十六进制转换函数*/

/*******************************************************************************
* 函数名         : eight_change_two(float num)
* 函数功能		 : 八到二进制转换函数
* 输入           : 浮点型数据
* 输出         	 : int型数组首地址
* 注意			 ：此函数调用的是八到十，再是十到八
*******************************************************************************/

int* eight_change_two(float num)
{
        float result = 0;
//        float eight_change_ten(float num); //单独测试时需要打开这两行代码进行函数声明
//        int* ten_change_two(float num); 		       
		result = eight_change_ten(num);
		return (ten_change_two(result)); 

}


/*******************************************************************************
* 函数名         : eight_change_ten(float num)
* 函数功能		 : 八到十进制转换函数
* 输入           : 浮点型数据
* 输出         	 : 浮点型数据
* 注意			 ：小数部分只能进行四位的转换
*******************************************************************************/

 float eight_change_ten(float num) 
{
      int j;
      float i;
	  unsigned int num_1;//接收整形变量
	  unsigned int num_2;//对小数部分的数据进行处理
      float result = 0; 
 	if ((num - (unsigned int)num)>=0)  //判断是否含有小数，整体逻辑与二到十的逻辑结构相同
   {
      num_1 = (unsigned int)num;	
      for(i = 1; num_1 != 0; i *= 8) 
       {  
            result += (num_1 % 10) * i; 
            num_1 = num_1 / 10; 
       }
	  num_2 = num*10000;
      for(i = 1.0/(8*8*8*8),j=1; j < 5; i *= 8,j++) 
       {  
            result += ((unsigned int)num_2 % 10) * i; 
            num_2 = num_2 / 10; 
       }
	   
	   return result;
	}
	else
	{
      for(i = 1; num != 0; i *= 8) 
       {  
            result = result + ((unsigned int)num % 10) * i; 
            num = num / 10; 
       }
	   return result; 	
	}		
}


/*******************************************************************************
* 函数名         : eight_change_sixteen(float num)
* 函数功能		 : 八到十六进制转换函数
* 输入           : 浮点型数据
* 输出         	 : int型数组首地址
* 注意			 ：此为八到十，再是十到十六
*******************************************************************************/

int* eight_change_sixteen(float num) 
{ 
    float result = 0; 
    result = eight_change_ten(num);
    return (ten_change_sixteen(result));
}

/*十进制到二、八、十六进制转换函数*/

/*******************************************************************************
* 函数名         : ten_change_two(float num) 
* 函数功能		 : 十到二进制转换函数
* 输入           : 浮点型数据
* 输出         	 : int型数组首地址
* 注意			 ：此函数小数部分处理存在误差，仅仅用到两位小数进行了转换，当前
                   算法无法解决此误差，返回数组最后一位100为结束标志位
*******************************************************************************/

int* ten_change_two(float num) 
{ 
	int i,j;//for循环标志位
    int t;//数组倒置中间值 
	unsigned int num_1;//接收整形变量
	float num_2;//对小数部分的数据进行处理
	static int p[17];
  if ((num - (unsigned int)num)>0) //判断是否含有小数
 {
	num_1 = (unsigned int)num;	 //接收整数部分
	for(i = 0; num_1 != 0; i++)	  //取出每一位数
	{
     	p[i] = num_1 % 2; 
        num_1 = num_1 / 2;
        p[i] += 48;		//加上assic
	}
		for(j = 0;j < i/2;j++)//数组倒置 ，i为当前数组长度
	{
		t = p[j];
		p[j] = p[i-j-1];
		p[i-j-1] = t;	
	}
	p[i] = '.';
	
	num_2 = num - (int)num;//进行小数部分处理
	p[i+1] = (unsigned int)(num_2 * 2);
	p[i+1] += 48;
	num_2 =  num_2 * 2 - (unsigned int)(num_2 * 2);//进行第二位小数部分的处理
	p[i+2] =  (unsigned int)(num_2 * 2);
	p[i+2] += 48;
	p[i+3] = 100;  //给返回数组的一个标志位
	return p;
 }
    else
   {
       num_1 = (unsigned int)num;//提取整数进行转换
	   for(j = 0; num_1 != 0; j++) 
	  {
       p[j] = num_1 % 2; 
        num_1 = num_1 / 2; 
            p[j] += 48; 
      }
     	for(i = 0;i < j/2;i++)//数组倒置 
	{
		t = p[i];
		p[i] = p[j-i-1];
		p[j-i-1] = t;	
	}
	 p[j]=100;
	 return p;
	} 
} 

/*******************************************************************************
* 函数名         : ten_change_eight(float num) 
* 函数功能		 : 十到八进制转换函数
* 输入           : 浮点型数据
* 输出         	 : int型数组首地址
* 注意			 ：此函数小数部分处理存在误差，仅仅用到两位小数进行了转换，当前
                   算法无法解决此误差，返回数组最后一位100为结束标志位
*******************************************************************************/

int* ten_change_eight(float num) 
{ 
	int i,j;//for循环标志位
    int t;//数组倒置中间值 
	unsigned int num_1;//接收整形变量
	float num_2;//对小数部分的数据进行处理
	static int p[17];
  if ((num - (unsigned int)num)>0) //判断是否含有小数
 {
	num_1 = (unsigned int)num;
	for(i = 0; num_1 != 0; i++)
	{
     	p[i] = num_1 % 8; 
        num_1 = num_1 / 8;
        p[i] += 48;
	}
		for(j = 0;j < i/2;j++)//数组倒置 ，i为当前的数组长度
	{
		t = p[j];
		p[j] = p[i-j-1];
		p[i-j-1] = t;	
	}
	p[i] = '.';	 //小数部分处理，仅仅处理后面三位小数
	
	num_2 = num - (int)num;
	p[i+1] = (unsigned int)(num_2 * 8);
	p[i+1] += 48;
	num_2 =  num_2 * 8 - (unsigned int)(num_2 * 8);
	p[i+2] =  (unsigned int)(num_2 * 8);
	p[i+2] += 48;
	p[i+3] = 100;
	return p;
 }
    else
   {
       num_1 = (unsigned int)num;//提取整数进行转换
	   for(j = 0; num_1 != 0; j++) 
	  {
       p[j] = num_1 % 8; 
        num_1 = num_1 / 8; 
            p[j] += 48; 
      }
     	for(i = 0;i < j/2;i++)//数组倒置 
	{
		t = p[i];
		p[i] = p[j-i-1];
		p[j-i-1] = t;	
	}
	 p[j]=100;
	 return p;
	} 
} 

/*******************************************************************************
* 函数名         : ten_change_sixteen(float num) 
* 函数功能		 : 十到十六进制转换函数
* 输入           : 浮点型数据
* 输出         	 : int型数组首地址
* 注意			 ：此函数小数部分处理存在误差，仅仅用到两位小数进行了转换，当前
                   算法无法解决此误差，返回数组最后一位100为结束标志位
*******************************************************************************/

int* ten_change_sixteen(float num)
{
    int j=0,i=0;//计数
    int t;//数组倒置中间值 
	unsigned int num_1;//接收整形变量
	float num_2;//对小数部分的数据进行处理 
    static int p[17];
	if ((num - (unsigned int)num)>0) //判断是否含有小数
   {
       num_1 = (unsigned int)num;//提取整数进行转换
	   for(j = 0; num_1 != 0; j++) 
	  {
       p[j] = num_1 % 16; 
        num_1 = num_1 / 16; 
        if(p[j] < 10)  //需要将每一个数转坏为ASSIc存入
            p[j] += 48; 
        else 
        { 
            switch(p[j]) 
            { 
            case 10: 
                p[j] = 'A'; 
                break; 
            case 11: 
                p[j] = 'B'; 					   
                break; 
            case 12: 
                p[j] = 'C'; 
                break; 
            case 13: 
                p[j] = 'D'; 
                break; 
            case 14: 
                p[j] = 'E'; 
                break; 
            case 15: 
                p[j] = 'F'; 
                break; 
            } 
        } 
     }
	for(i = 0;i < j/2;i++)//数组倒置 ，j为当前数组长度 ，小数点后面的数字不需要进行数组倒置
	{
		t = p[i];
		p[i] = p[j-i-1];
		p[j-i-1] = t;	
	}
     
	 p[j] = '.';  //小数部分的处理，取出第一位小数，转换之后存入数组
	 num_2 = num - (unsigned int)num;
	 p[j+1] = (unsigned int)(num_2 * 16);
	 
        if(p[j+1] < 10) 
            p[j+1] += 48; 
        else 
        { 
            switch(p[j+1]) 
            { 
            case 10: 
                p[j+1] = 'A'; 
                break; 
            case 11: 
                p[j+1] = 'B'; 					   
                break; 
            case 12: 
                p[j+1] = 'C'; 
                break; 
            case 13: 
                p[j+1] = 'D'; 
                break; 
            case 14: 
                p[j+1] = 'E'; 
                break; 
            case 15: 
                p[j+1] = 'F'; 
                break; 
            } 
        }
		 	  
	 num_2 =  num_2 * 16 - (unsigned int)(num_2 * 16); //小数部分的处理，取出第二位小数，转换之后存入数组
	 p[j+2] =  (unsigned int)(num_2 * 16);
	 
        if(p[j+2] < 10) 
            p[j+2] += 48; 
        else 
        { 
            switch(p[j+2]) 
            { 
            case 10: 
                p[j+2] = 'A'; 
                break; 
            case 11: 
                p[j+2] = 'B'; 					   
                break; 
            case 12: 
                p[j+2] = 'C'; 
                break; 
            case 13: 
                p[j+2] = 'D'; 
                break; 
            case 14: 
                p[j+2] = 'E'; 
                break; 
            case 15: 
                p[j+2] = 'F'; 
                break; 
            } 
        } 	 
	 
	 p[j+3] = 100;//数组结束标志位
	 return p;
	 	  
   }

   else
   {
       num_1 = (unsigned int)num;//提取整数进行转换	，与前面的逻辑结构相同
	   for(j = 0; num_1 != 0; j++) 
	  {
       p[j] = num_1 % 16; 
        num_1 = num_1 / 16; 
        if(p[j] < 10) 
            p[j] += 48; 
        else 
        { 
            switch(p[j]) 
            { 
            case 10: 
                p[j] = 'A'; 
                break; 
            case 11: 
                p[j] = 'B'; 					   
                break; 
            case 12: 
                p[j] = 'C'; 
                break; 
            case 13: 
                p[j] = 'D'; 
                break; 
            case 14: 
                p[j] = 'E'; 
                break; 
            case 15: 
                p[j] = 'F'; 
                break; 
            } 
        } 
     }
     	for(i = 0;i < j/2;i++)//数组倒置 
	{
		t = p[i];
		p[i] = p[j-i-1];
		p[j-i-1] = t;	
	}
	 p[j]=100;
	 return p;
	} 
}

/*十六进制到二、八、十进制转换函数*/

/*******************************************************************************
* 函数名         : sixteen_change_two(char b[], int k) 
* 函数功能		 : 十六到二进制转换函数
* 输入           : 需要转换的数组首地址 数组长度
* 输出         	 : int型数组首地址
* 注意			 ：此函数为十六到十，再是十到二
*******************************************************************************/

int* sixteen_change_two(char b[], int k)
{
   float c;
//   float sixteen_change_ten(char a[], int k);//单独测试时需要打开声明 
//   int* ten_change_two(float num);
   c = sixteen_change_ten( b , k);
   return (ten_change_two(c));
     
} 

/*******************************************************************************
* 函数名         : sixteen_change_eight(char b[], int k) 
* 函数功能		 : 十六到八进制转换函数
* 输入           : 需要转换的数组首地址 数组长度
* 输出         	 : int型数组首地址
* 注意			 ：此函数为十六到十，再是十到八
*******************************************************************************/

int* sixteen_change_eight(char b[], int k)
{
   float result;
//   float sixteen_change_ten(char a[], int k); 
//   int* ten_change_eight(float num);
   result = sixteen_change_ten( b , k);
   return (ten_change_eight(result));
     
} 
   
/*******************************************************************************
* 函数名         : sixteen_change_ten(char b[], int k) 
* 函数功能		 : 十到十进制转换函数
* 输入           : 需要转换的数组首地址 数组长度
* 输出         	 : int型数组首地址
* 注意			 ：此函数算法与前面算法略微有点差别，精度理论上来说会高一点，但
                   是任然存在误差，且无法消除
*******************************************************************************/ 

float sixteen_change_ten(char a[], int k) //输入一个数组与它的长度
{ 
    int i , l,s = 0;//s为遍历数组中，小数点的位置记录值，l为s的记录值，i为for计数值 
    float j;
    float result = 0; //函数返回值
    for(i = 0; (s==0)&&(i < k); i++) //首先进行索引转换，将数组中的数字提取出来
    { 
        if(a[i] <= '9' && a[i] >= '0') 
        { 
            a[i] = a[i] - 48; //减去ASSIC
        } 
        else 
        { 
            switch(a[i]) 
            { 
            case 'A': 
                a[i] = 10; 
                break; 
            case 'B': 
                a[i] = 11; 
                break; 
            case 'C': 
                a[i] = 12; 
                break; 
            case 'D': 
                a[i] = 13; 
                break; 
            case 'E': 
                a[i] = 14; 
                break; 
            case 'F': 
                a[i] = 15; 
                break; 
            case 'a': 
                a[i] = 10; 
                break; 
            case 'b': 
                a[i] = 11; 
                break; 
            case 'c': 
                a[i] = 12; 
                break; 
            case 'd': 
                a[i] = 13; 
                break; 
            case 'e': 
                a[i] = 14; 
                break; 
            case 'f': 
                a[i] = 15; 
                break;
			case '.':
				s = 1;//置位，退出当前循环，处理小数部分
				break;  	 
            default: ;break; 
            } 
        } 
    }
    l=i;//记录小数点的位置，小数点位置为i-1

   if(s)//判断是否含有小数
  {
  	i = i - 2;//处理整数部分
    for( j = 1; i >= 0; i--, j *= 16) //整数部分转换
    { 
        result += a[i] * j; 
    }

	    for(i = l; i < k ; i++) //将l的值重新赋值为i，当前i值为小数点的位置，将小数点后面的数进行提取转换
    { 
        if(a[i] <= '9' && a[i] >= '1') 
        { 
            a[i] = a[i] - 48; 
        } 
        else 
        { 
            switch(a[i]) 
            { 
            case 'A': 
                a[i] = 10; 
                break; 
            case 'B': 
                a[i] = 11; 
                break; 
            case 'C': 
                a[i] = 12; 
                break; 
            case 'D': 
                a[i] = 13; 
                break; 
            case 'E': 
                a[i] = 14; 
                break; 
            case 'F': 
                a[i] = 15; 
                break; 
            case 'a': 
                a[i] = 10; 
                break; 
            case 'b': 
                a[i] = 11; 
                break; 
            case 'c': 
                a[i] = 12; 
                break; 
            case 'd': 
                a[i] = 13; 
                break; 
            case 'e': 
                a[i] = 14; 
                break; 
            case 'f': 
                a[i] = 15; 
                break;
            default: ; 
            } 
        } 
    }

    for(i = l , j=1.0/16; i < k; i++, j *= 1.0/16)//小数点后面的数字进行处理 
    { 
        result += a[i] * j; 
    }
	     	return result;
 }
 else //处理整数部分
 {
 	i = i - 1;
    for( j = 1; i >= 0; i--, j *= 16) //整数部分转换
    { 
        result += a[i] * j; 
    }
	return result;
 } 
} 


 

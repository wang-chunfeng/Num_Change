/*
���޸���־������
2020.10.3 ������/unicorn 
��ģ���������ʵ�֣�����淶��ɣ�V1.0�汾��Ȼ����һ���Ĵ�����Ҫ��ʹ���з���
ͬʱ��keil4�е��ļ�Ϊ���°汾�������е�ģ���������������Դ��ļ�ת������Ϊ׼��
�����޸ġ�


*/



#include "change.h"

/*�����Ƶ��ˡ�ʮ��ʮ������ת������*/
/*******************************************************************************
* ������         : two_change_eight(float num)
* ��������		 : �����˽���ת������
* ����           : ����������
* ���         	 : int�������׵�ַ
* ע��			 ���˺������õ��Ƕ���ʮ���ƣ�����ʮ���˽��ƽ���ת��
*******************************************************************************/

int* two_change_eight(float num) 
{ 
        float result = 0;
//        float two_change_ten(float num); 	//��������ʱ��Ҫ�������д�����к�������
//        int* ten_change_eight(float num); 		       
		result = two_change_ten(num);
		return (ten_change_eight(result)); 
}


/*******************************************************************************
* ������         : two_change_ten(float num)
* ��������		 : ����ʮ����ת������
* ����           : ����������
* ���         	 : ����������
* ע��			 ��С�����ֵ�ת����ֻ�ܴ�����λС��
*******************************************************************************/

float two_change_ten(float num) 
{
      int j;
      float i;
	  unsigned int num_1;//�������α���
	  unsigned int num_2;//��С�����ֵ����ݽ��д���
      float result = 0;	 //���ؽ��
      num_1 = (unsigned int)num; //������������
	if ((num - (unsigned int)num)>0) //�ж��Ƿ���С��
   {	
      for(i = 1; num_1 != 0; i *= 2) //ȡ��ÿһλ������*2�Ĵη�
       {  
            result += (num_1 % 10) * i; 
            num_1 = num_1 / 10; 
       }
	  num_2 = num*10000;
      for(i = 1.0/(2*2*2*2),j=1; j < 5; i *= 2,j++) //С�����ֵ�ת����ֻ�ܴ�����λС�������ȷŴ�һ�򱶣�Ȼ��ȡ�������в���
       {  
            result += ((unsigned int)num_2 % 10) * i; 
            num_2 = num_2 / 10; 
       }
	   	return result;	
	}
	else //������������
	{
     for(i = 1; num_1 != 0; i *= 2) //ȡ��ÿһλ������*2�Ĵη�
       {  
            result += (num_1 % 10) * i; 
            num_1 = num_1 / 10; 
       }
	   	 return result;		
	}	
}


/*******************************************************************************
* ������         : two_change_sixteen(float num)
* ��������		 : ����ʮ������ת������
* ����           : ����������
* ���         	 : int�������׵�ַ
* ע��			 ���˺������õ��Ƕ���ʮ��ʮ�ٵ���
*******************************************************************************/

int* two_change_sixteen(float num) 
{
        float result = 0;
//        float two_change_ten(float num); 		//��������ʱ��Ҫ�������д�����к�������
//        int* ten_change_sixteen(float num); 		       
		result = two_change_ten(num);
		return (ten_change_sixteen(result)); 

}
 

/*�˽��Ƶ�����ʮ��ʮ������ת������*/

/*******************************************************************************
* ������         : eight_change_two(float num)
* ��������		 : �˵�������ת������
* ����           : ����������
* ���         	 : int�������׵�ַ
* ע��			 ���˺������õ��ǰ˵�ʮ������ʮ����
*******************************************************************************/

int* eight_change_two(float num)
{
        float result = 0;
//        float eight_change_ten(float num); //��������ʱ��Ҫ�������д�����к�������
//        int* ten_change_two(float num); 		       
		result = eight_change_ten(num);
		return (ten_change_two(result)); 

}


/*******************************************************************************
* ������         : eight_change_ten(float num)
* ��������		 : �˵�ʮ����ת������
* ����           : ����������
* ���         	 : ����������
* ע��			 ��С������ֻ�ܽ�����λ��ת��
*******************************************************************************/

 float eight_change_ten(float num) 
{
      int j;
      float i;
	  unsigned int num_1;//�������α���
	  unsigned int num_2;//��С�����ֵ����ݽ��д���
      float result = 0; 
 	if ((num - (unsigned int)num)>=0)  //�ж��Ƿ���С���������߼������ʮ���߼��ṹ��ͬ
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
* ������         : eight_change_sixteen(float num)
* ��������		 : �˵�ʮ������ת������
* ����           : ����������
* ���         	 : int�������׵�ַ
* ע��			 ����Ϊ�˵�ʮ������ʮ��ʮ��
*******************************************************************************/

int* eight_change_sixteen(float num) 
{ 
    float result = 0; 
    result = eight_change_ten(num);
    return (ten_change_sixteen(result));
}

/*ʮ���Ƶ������ˡ�ʮ������ת������*/

/*******************************************************************************
* ������         : ten_change_two(float num) 
* ��������		 : ʮ��������ת������
* ����           : ����������
* ���         	 : int�������׵�ַ
* ע��			 ���˺���С�����ִ�������������õ���λС��������ת������ǰ
                   �㷨�޷�������������������һλ100Ϊ������־λ
*******************************************************************************/

int* ten_change_two(float num) 
{ 
	int i,j;//forѭ����־λ
    int t;//���鵹���м�ֵ 
	unsigned int num_1;//�������α���
	float num_2;//��С�����ֵ����ݽ��д���
	static int p[17];
  if ((num - (unsigned int)num)>0) //�ж��Ƿ���С��
 {
	num_1 = (unsigned int)num;	 //������������
	for(i = 0; num_1 != 0; i++)	  //ȡ��ÿһλ��
	{
     	p[i] = num_1 % 2; 
        num_1 = num_1 / 2;
        p[i] += 48;		//����assic
	}
		for(j = 0;j < i/2;j++)//���鵹�� ��iΪ��ǰ���鳤��
	{
		t = p[j];
		p[j] = p[i-j-1];
		p[i-j-1] = t;	
	}
	p[i] = '.';
	
	num_2 = num - (int)num;//����С�����ִ���
	p[i+1] = (unsigned int)(num_2 * 2);
	p[i+1] += 48;
	num_2 =  num_2 * 2 - (unsigned int)(num_2 * 2);//���еڶ�λС�����ֵĴ���
	p[i+2] =  (unsigned int)(num_2 * 2);
	p[i+2] += 48;
	p[i+3] = 100;  //�����������һ����־λ
	return p;
 }
    else
   {
       num_1 = (unsigned int)num;//��ȡ��������ת��
	   for(j = 0; num_1 != 0; j++) 
	  {
       p[j] = num_1 % 2; 
        num_1 = num_1 / 2; 
            p[j] += 48; 
      }
     	for(i = 0;i < j/2;i++)//���鵹�� 
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
* ������         : ten_change_eight(float num) 
* ��������		 : ʮ���˽���ת������
* ����           : ����������
* ���         	 : int�������׵�ַ
* ע��			 ���˺���С�����ִ�������������õ���λС��������ת������ǰ
                   �㷨�޷�������������������һλ100Ϊ������־λ
*******************************************************************************/

int* ten_change_eight(float num) 
{ 
	int i,j;//forѭ����־λ
    int t;//���鵹���м�ֵ 
	unsigned int num_1;//�������α���
	float num_2;//��С�����ֵ����ݽ��д���
	static int p[17];
  if ((num - (unsigned int)num)>0) //�ж��Ƿ���С��
 {
	num_1 = (unsigned int)num;
	for(i = 0; num_1 != 0; i++)
	{
     	p[i] = num_1 % 8; 
        num_1 = num_1 / 8;
        p[i] += 48;
	}
		for(j = 0;j < i/2;j++)//���鵹�� ��iΪ��ǰ�����鳤��
	{
		t = p[j];
		p[j] = p[i-j-1];
		p[i-j-1] = t;	
	}
	p[i] = '.';	 //С�����ִ����������������λС��
	
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
       num_1 = (unsigned int)num;//��ȡ��������ת��
	   for(j = 0; num_1 != 0; j++) 
	  {
       p[j] = num_1 % 8; 
        num_1 = num_1 / 8; 
            p[j] += 48; 
      }
     	for(i = 0;i < j/2;i++)//���鵹�� 
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
* ������         : ten_change_sixteen(float num) 
* ��������		 : ʮ��ʮ������ת������
* ����           : ����������
* ���         	 : int�������׵�ַ
* ע��			 ���˺���С�����ִ�������������õ���λС��������ת������ǰ
                   �㷨�޷�������������������һλ100Ϊ������־λ
*******************************************************************************/

int* ten_change_sixteen(float num)
{
    int j=0,i=0;//����
    int t;//���鵹���м�ֵ 
	unsigned int num_1;//�������α���
	float num_2;//��С�����ֵ����ݽ��д��� 
    static int p[17];
	if ((num - (unsigned int)num)>0) //�ж��Ƿ���С��
   {
       num_1 = (unsigned int)num;//��ȡ��������ת��
	   for(j = 0; num_1 != 0; j++) 
	  {
       p[j] = num_1 % 16; 
        num_1 = num_1 / 16; 
        if(p[j] < 10)  //��Ҫ��ÿһ����ת��ΪASSIc����
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
	for(i = 0;i < j/2;i++)//���鵹�� ��jΪ��ǰ���鳤�� ��С�����������ֲ���Ҫ�������鵹��
	{
		t = p[i];
		p[i] = p[j-i-1];
		p[j-i-1] = t;	
	}
     
	 p[j] = '.';  //С�����ֵĴ���ȡ����һλС����ת��֮���������
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
		 	  
	 num_2 =  num_2 * 16 - (unsigned int)(num_2 * 16); //С�����ֵĴ���ȡ���ڶ�λС����ת��֮���������
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
	 
	 p[j+3] = 100;//���������־λ
	 return p;
	 	  
   }

   else
   {
       num_1 = (unsigned int)num;//��ȡ��������ת��	����ǰ����߼��ṹ��ͬ
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
     	for(i = 0;i < j/2;i++)//���鵹�� 
	{
		t = p[i];
		p[i] = p[j-i-1];
		p[j-i-1] = t;	
	}
	 p[j]=100;
	 return p;
	} 
}

/*ʮ�����Ƶ������ˡ�ʮ����ת������*/

/*******************************************************************************
* ������         : sixteen_change_two(char b[], int k) 
* ��������		 : ʮ����������ת������
* ����           : ��Ҫת���������׵�ַ ���鳤��
* ���         	 : int�������׵�ַ
* ע��			 ���˺���Ϊʮ����ʮ������ʮ����
*******************************************************************************/

int* sixteen_change_two(char b[], int k)
{
   float c;
//   float sixteen_change_ten(char a[], int k);//��������ʱ��Ҫ������ 
//   int* ten_change_two(float num);
   c = sixteen_change_ten( b , k);
   return (ten_change_two(c));
     
} 

/*******************************************************************************
* ������         : sixteen_change_eight(char b[], int k) 
* ��������		 : ʮ�����˽���ת������
* ����           : ��Ҫת���������׵�ַ ���鳤��
* ���         	 : int�������׵�ַ
* ע��			 ���˺���Ϊʮ����ʮ������ʮ����
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
* ������         : sixteen_change_ten(char b[], int k) 
* ��������		 : ʮ��ʮ����ת������
* ����           : ��Ҫת���������׵�ַ ���鳤��
* ���         	 : int�������׵�ַ
* ע��			 ���˺����㷨��ǰ���㷨��΢�е��𣬾�����������˵���һ�㣬��
                   ����Ȼ���������޷�����
*******************************************************************************/ 

float sixteen_change_ten(char a[], int k) //����һ�����������ĳ���
{ 
    int i , l,s = 0;//sΪ���������У�С�����λ�ü�¼ֵ��lΪs�ļ�¼ֵ��iΪfor����ֵ 
    float j;
    float result = 0; //��������ֵ
    for(i = 0; (s==0)&&(i < k); i++) //���Ƚ�������ת�����������е�������ȡ����
    { 
        if(a[i] <= '9' && a[i] >= '0') 
        { 
            a[i] = a[i] - 48; //��ȥASSIC
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
				s = 1;//��λ���˳���ǰѭ��������С������
				break;  	 
            default: ;break; 
            } 
        } 
    }
    l=i;//��¼С�����λ�ã�С����λ��Ϊi-1

   if(s)//�ж��Ƿ���С��
  {
  	i = i - 2;//������������
    for( j = 1; i >= 0; i--, j *= 16) //��������ת��
    { 
        result += a[i] * j; 
    }

	    for(i = l; i < k ; i++) //��l��ֵ���¸�ֵΪi����ǰiֵΪС�����λ�ã���С����������������ȡת��
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

    for(i = l , j=1.0/16; i < k; i++, j *= 1.0/16)//С�����������ֽ��д��� 
    { 
        result += a[i] * j; 
    }
	     	return result;
 }
 else //������������
 {
 	i = i - 1;
    for( j = 1; i >= 0; i--, j *= 16) //��������ת��
    { 
        result += a[i] * j; 
    }
	return result;
 } 
} 


 

#include <reg51.h>
#include <math.h>
#define uchar unsigned char
#define uint unsigned int
#define KeyPort  P1

uchar code duanma[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e};// ��ʾ����ֵ0~F��+-*/ ��
uchar code weima[]={0x3e,0x3d,0x3b,0x37,0x2f,0x1f};//λ��,������ʾ�ĸ�LED
uchar tempdata[6]={0x3f,0x00,0x00,0x00,0x00,0x00}; //�洢��ӦLEDӦ����ʾ��ֵ����ʼ��һλ����Ϊ0

void delayms(void);	//��ʱ
uchar kbscan(void);	 //����ɨ��
uchar keypro(void);	 //��ֵ����				
void display(void);  //�������ʾ



//����Ҫѭ��������㣬����Ҫ��һ��whileѭ����
void main (void)	//�߼�����
{
   uchar temp,tempbak;
   uint num1,num2,sym,value;
   int i,count,num,biaozhi;
   P1=0xff;
   count=0;
   num =0;
   num1=0;
   num2=0;
   temp=0;
   sym=0;
   biaozhi=0;
   tempbak=0;

  while(1)			//���޼���
  {
	temp=keypro();  //��ȡ����ֵ���ж������ֻ��������
	if(temp!=tempbak)
	{
	    if(temp>=0&&temp<=9&&biaozhi==0)   //�����һ��������
		{
		  num1=num1*10+temp;
		  for(i=count;i>0;i--)
		  {
		  	tempdata[i] = tempdata[i-1];
		  }
		  tempdata[0]=duanma[temp];
		  count++;
	
		}
	
	
		else if(temp>=10&&temp<=13&&biaozhi==0)	 //�����˲��������豣���һ��������num1�Ͳ�����
		{
		  sym=temp;	//����������
	
		  for(i=count;i>0;i--)
		  {
		  	tempdata[i] = tempdata[i-1];
		  }
		  tempdata[0]=duanma[temp];
		  count++;
	
		  num=count;	//��¼��һ�������ϲ�������λ��
		  biaozhi++;
		}
	
	
		else if(temp>=0&&temp<=9&&biaozhi==1)	//����ڶ���������
		{
		  num2=num2*10+temp;	
		  	 
		  for(i=count;i>0;i--)
		  {
		  	tempdata[i] = tempdata[i-1];
		  }
		  tempdata[0]=duanma[temp];
		  count++;
	
		}	
				   
		else if(temp==14&&biaozhi==1)		//�Ⱥţ���Ҫ������
		{
	
		  //�Ӽ��˳�
		  if(sym==10)value=num1+num2;
		  else if(sym==11)value=num1-num2;
		  else if(sym==12)value=num1*num2;
		  else if(sym==13)value=num1/num2;
		  for(i=0;i<6;i++)tempdata[i]=0x00;	  //ǰ����ʾ���ȱ�Ϊ0
	
		  //�ѽ���浽tempdata[]��
	
		  if(value<10)tempdata[0]=duanma[value]; 
		  else if(value<100){
		  	tempdata[1]=duanma[value/10];
			tempdata[0]=duanma[value%10];
		  }	
		  
		  else if(value<1000){
			tempdata[2]=duanma[value/100];
		  	tempdata[1]=duanma[(value%100)/10];
			tempdata[0]=duanma[value%10];
		  }	
		 
		  else if(value<10000){
			tempdata[3]=duanma[value/1000];
			tempdata[2]=duanma[(value%1000)/100];
		  	tempdata[1]=duanma[(value%100)/10];
			tempdata[0]=duanma[value%10];
		  }	
		  
		  else if(value<100000){
			tempdata[4]=duanma[value/10000];
			tempdata[3]=duanma[(value%10000)/1000];
			tempdata[2]=duanma[(value%1000)/100];
		  	tempdata[1]=duanma[(value%100)/10];
			tempdata[0]=duanma[value%10];
		  }	
	
		  else if(value<1000000){
			tempdata[5]=duanma[value/100000];	
		    tempdata[4]=duanma[(value%100000)/10000];
			tempdata[3]=duanma[(value%10000)/1000];
			tempdata[2]=duanma[(value%1000)/100];
		  	tempdata[1]=duanma[(value%100)/10];
			tempdata[0]=duanma[value%10];
		  }
	
		  biaozhi=0;
		  count=0;
		  num=0;
		  num1=0;
		  num2=0;
		}
	
	
		else if(temp==15)			 //���
		{
		  biaozhi=0;
		  count=0;
		  num=0;
		  num1=0;
		  num2=0;
		  for(i=0;i<6;i++)tempdata[i]=0x00;
		  tempdata[0]=0x3f;
		}
		  					
		
//	    delayms();
		tempbak=temp;
	} 
     display();			 //��ʾ
  }
}


void display(void)
{
  uchar i;
  for(i=0;i<6;i++)  //���������
	{
	  P2=0x00;
	  P2=tempdata[i]; //�������ʾ��ֵ
	  P3=weima[5-i];  //��һ���������ʾ
	  delayms();
	}
}

/* 
	���̴������
		1.ȷ���Ƿ��м�����-ȥ����
		2.��һ�������´����Ǹ���
		3.��Ӧ����ִ��ʲô����
*/

// ɨ����̷�����Ӧλ�ñ���	
uchar kbscan(void) //����ɨ�躯��
{ 
	uchar sccode,recode;
	P1=0xf0; // P1.0~P1.3��ȫ0��P1.4~P1.7����

	if ( (P1 & 0xf0)!=0xf0)  // * ��P1�ڸ���λ��ȫΪ1�м�����* /
	{
		delayms(); // * ��ʱȥ����* /
		if ((P1&0xf0)!=0xf0) // * �ڶ�����ֵ* /
		{ 
			sccode =0xfe; // * ���λ��0 * /
			while((sccode&0x10)!=0)   // �������һ��ѭ��
			{
				P1 =sccode;    //*P1�����ɨ����
				if ( (P1 & 0xf0)!=0xf0) //  ��P1.4~P1.7��ȫΪ1�������м�����
				{
					recode = P1 & 0xf0; // * ����P1�ڸ���λֵ������λ��Ϊȫ1, ��Ϊ��ֵ* /
					return((sccode&0x0f)|(recode));     //*����+��ֵ=�����뷵��������
				}
		        else
			    {
					sccode =(sccode<<1)|0x01; // * ������޼����£�����һ�У���ɨ��ֵ����һλ
				}
		    } 
		}
	}
	return( 0 );	  // * �޼����£�����ֵΪ0 
} 


void delayms(void)	//��ʱ����
{
  uchar i;						 
  for(i=200;i>0;i--){;}
}


//���ݼ��̵õ�����
unsigned char keypro(void)	 //��ֵת������
{
 	switch(kbscan())
	{
	  case 0xee:return 7;break;
	  case 0xde:return 8;break;
	  case 0xbe:return 9;break;
	  case 0x7e:return 13;break;// ����
	  case 0xed:return 4;break;
	  case 0xdd:return 5;break;
	  case 0xbd:return 6;break;
	  case 0x7d:return 12;break;//�˷�
	  case 0xeb:return 1;break;
	  case 0xdb:return 2;break;
	  case 0xbb:return 3;break;
	  case 0x7b:return 11;break;//����
	  case 0xe7:return 15;break;//���
	  case 0xd7:return 0;break;
	  case 0xb7:return 14;break;//����
	  case 0x77:return 10;break;//�ӷ�
	  default:return 0xff;break;
   }
}

 // �ó���ʵ��Ƶ�ʼƺͲ�ռ�ձȣ���ʼ���ݿ��ܲ�׼���ȴ�����ˢ���ȶ����ɡ�
#include "reg51.h"
#include "intrins.h"

// Define P2 pins������P2�˿ڵ����
/*
#define DATA_BUS  P0 
sbit RS=P2^0;
sbit RW=P2^1;
sbit E=P2^2; */

extern	int bcd_to_led(uint x);	//����ӳ��򣬴���DISPBUFF[4]�е�����

// Define new types
typedef unsigned char   uchar;
typedef unsigned int    uint;

// ������
void check_busy(void);
void write_command(uchar com);
void write_data(uchar ddata);
void LCD_init(void);
void string(uchar ad ,uchar *s);
void lcd_test(void);
void Init_zhongduan(void);	//�жϳ�ʼ��
void get_result();	//1sʱ����Ƶ�ʣ�ռ�ձȣ����ڡ�
void delay(uint);	//��ʱ����
void display(void);	//��ʾ����
void buffer_display(uint x);	// �������������

//ȫ�ֱ�������
//button1_mode->���ģʽѡ���ⲿ�ж�1���ڣ���ʼ��Ϊ0.
//maichong_number-��1s�ڵ��������������ڼ���Ƶ�ʡ�����
//timer0_number->��ʱ��0�������
//timer1_number->��ʱ��1�жϴ�����20�ε�1s
//timer1_flag->�ﵽ1s�ı�־����1s�ſ���������ɾ�˴˱���
uint button1_mode = 0,maichong_number=0,timer0_number=0,timer1_number=0,timer1_flag = 0;
uint frequent=0;	  //Ƶ�ʣ�ռ�ձȣ�����
unsigned long int zhankongbi=0;
unsigned long zhouqi=0;
uint DISPBUFF[] = {0,0,0,0};	//����6λ��������ʾ

sbit udata=P3^6;
sbit uclk=P3^7;

void delayms()
{
	 uint j;
	 for(j=0;j<=30000;j++) ;
}
/*****************************************

  �����򡢳�ʼ��������ʾ����

*****************************************/
void main(void)
 { 
 	//LCD_init(); //LCD��ʼ��
	//IE = 0x85;
	//TCON = 0x05;
    Init_zhongduan();
    while(1)
    { 		
		display();
    }
 }

void Init_zhongduan(void)	//�жϳ�ʼ�� ����
{
    IE=0x8f;
    TCON=0x55;	//Ĭ�ϰ��ⲿ�ж�Ҳ�򿪡�
    TMOD=0x19;  //��ʱ��0gateλ��1	  
    TH0=0;
    TL0=0; //��ʱ��ʼΪ0
    TH1=0x3c;
    TL1=0xb0;  //��ʱ����ʼֵ����ʱ50ms
}

void display()	//��ʾ��������ͬģʽ��ʾ��ͬ���
{
   
	if(button1_mode == 0)  //Ƶ��
	{
		 buffer_display(frequent);
	}
	else if(button1_mode == 1)	//����
	{

	   buffer_display(zhouqi);

	}	
	else if(button1_mode == 2)	//ռ�ձ�
	{
	   buffer_display(zhankongbi);

	}	
	delay(2500);	//ˢ����ֵ	
//  	write_command(0x01); //����
  	delay(1); 
}


void buffer_display(uint x)  //����Ƶ�ʵȽ�����������ʾ��ƵĻ��
{
   int i;
   for(i=3;i>=0;i--)
   {
        DISPBUFF[i]=x%10;
	    x=x/10;
   }//����ֵ����buffer

	 for (i=0;i<=3;i++) 
	 {
	 	serial_data(bcd_to_led(DISPBUFF[3-i])&0xff);  //���û���ӳ���		
	 }		 
	 delayms();
}

void serial_data(uchar  dd)
{   
	uchar i;
	for (i=0;i<=7;i++)
	{
    	if((dd>>i)&0x01)	 udata=1;
	    else udata=0;
   		uclk=1;  uclk=0;
	}
}

void delay(uint j)
{ 
   uchar i = 60;
   for(; j>0; j--)
    { 
	  while(--i);
      i = 59;
      while(--i);
      i = 60;
    }
}

*/
/*************************************************

�жϴ�����-----�ĸ��ж϶�����

*************************************************/
int MODE1() interrupt 2 //���������ⲿ1�ж�,�л���ʾģʽ
{
  	write_command(0x01); //��ʾ���� 
	if(button1_mode < 2) button1_mode++;
	else button1_mode = 0;

}

int mode0() interrupt 0	//�ⲿ�ж�0����������ƽʱ�����жϡ�
{						//�ж�����ƽ��Ŀ+1

	 if(maichong_number == 0)  //0�������ˡ��ʼ���ö�ʱ��
	 {
 	    TH0=0;
	    TL0=0; //��ʱ��ʼΪ0
	    TH1=0x3c;
	    TL1=0xb0;  //��ʱ����ʼֵ����ʱ50ms			  
	 }
	 maichong_number++;	  //����������һ
}

int timer0() interrupt 1 //������0�жϣ����ʱ�����жϣ�һ����������ͻ��ʱ��
{
   	 TH0=0;
     TL0=0; //��ʱ��ʼΪ0��
	 timer0_number++;
}  //���Լ���1s����������ռʱ��


int timer1() interrupt 3	//��ʱ��1�жϣ�����Ū1sʱ��
{
	
   	TH1=0x3c;
  	TL1=0xb0;	//�������ö�ʱ��ֵ��50ms ��20��Ϊ1s
	timer1_number++;
    if(timer1_number == 20)	 //����1s������Ƶ��ռ�ձȡ�
	{	
		get_result();
		timer1_flag = 1;
		maichong_number = 0; //��������0
		timer1_number = 0;	 //������0
		timer0_number = 0; //�����������
		Init_zhongduan(); //�жϳ�ʼ��
		TH0=0;
        TL0=0; //��ʱ��ʼΪ0��
	}
}

void get_result(void)  //�����жϵó������ݵô����
{
	//�������̫���ˣ�����ֱ��256*256�����㣬���ܵ�Ƭ���Լ������⡣
	float t1,t2;
	t1 = (timer0_number*256/100)*256/100;// 
	t2 = (TH0*(256)+TL0)/10000;	  
    zhankongbi =(t1+t2);//���Ϊ�ٷֱ�			 
	frequent = maichong_number - maichong_number/1000-1; //Ƶ�ʣ���������
/*	if (frequent < 20)	   //��ms��ʾ����
	{
	   	zhouqi = 1000/frequent;
	}
    else zhouqi = 1000000/frequent;	   */

}


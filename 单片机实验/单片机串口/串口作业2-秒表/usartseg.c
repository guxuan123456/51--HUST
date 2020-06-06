#include<reg52.h>
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

extern	int bcd_to_led(uint x);	//����ӳ��򣬴���DISPBUFF[6]�е�����

//��������
void init();  //��ʼ������
void display();	//��ʾ����
void delayms();	 //�ӳٺ���
void serial_data(uchar  dd);
void send_char_com(unsigned char ch);
void uart_send_str(unsigned char *s);

//ȫ�ֱ���
uchar idata DISPBUFF[]={5,8,5,8,8,6};	//��ʼ������
sbit udata=P3^6;
sbit uclk=P3^7;
uchar  indata;

/********
main()����
********/
main( )
{

	init();
    while(1)
    {
        display();
    }
}

void delayms()
{
	 uint j;
	 for(j=0;j<=30000;j++) ;
} 

void init()
{
	//9600bps@11.0592MHz
    SCON = 0x50;	//8λ����,�ɱ䲨����
    TMOD = 0x21;	//��ʱ��1Ϊ��ʽ2,��ʱ��0Ϊ��ʽ1
	TL1 = 0xFD;		//��ʱ��ֵ
	TH1 = 0xFD;		//��ʱ��ֵ
	TH0=-10000/256;	//һ�μ����ж�Ϊ10ms��
	TL0=-10000%256; //������ֵ   
	TR1 = 1;		//������ʱ��1
	TR0= 0;			//��ʱ��0����������ʼֹͣ��ʱ
	ES = 1;			//���������ж� 
	ET0= 1;			//������ʱ��0�ж�
	EX0=1;			//�����ⲿ�ж�0������1
	EX1=1;			//�����ⲿ�ж�1,����2	
	IT0=1;			//����1�½��ش���
	IT1=1;			//����2Ϊ�½��ش���
	EA = 1;			//�������ж�
	uart_send_str("�������1��������ͣ������2����\r\n");
}

void display()
{
	 uchar  i;
	 for (i=0;i<=5;i++) 
	 {
	 	serial_data(bcd_to_led(DISPBUFF[5-i])&0xff);  //���û���ӳ���		
	 }		 
	 delayms();
    
}


/**************************
�����ַ��ȴ�����س���
**************************/
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

//�򴮿ڷ���һ���ַ� 
void send_char_com(unsigned char ch)
{
    SBUF=ch;
    while(TI==0);
    TI=0;
}
// �����ַ���
void uart_send_str(unsigned char *s)
{
	while(*s != '\0')// '\0':�ַ���������־
	{
		send_char_com(*s);// ����1���ֽ����ݣ�1���ַ�ռ8λ��1�ֽ�
		s++;// ָ����һ���ַ�
	}
}

/****************************
�жϴ������
��ʱ��0�жϣ�ʵ������������
****************************/
int timer0() interrupt 1 
{
	TH0=-10000/256;	//һ�μ����ж�Ϊ10ms����Ҫ�ж�100�ε���1s
	TL0=-10000%256;

	DISPBUFF[5]++;
	if(DISPBUFF[5]==10)
	{
		DISPBUFF[5]=0;
	  	DISPBUFF[4]++;
	  	if(DISPBUFF[4]==10)
	  	{
	    	DISPBUFF[4]=0;
	    	DISPBUFF[3]++;
			if(DISPBUFF[3]==10)
	    	{
	      		DISPBUFF[3]=0;
	      		DISPBUFF[2]++;
		  		if(DISPBUFF[2]==6)
	      		{
	        		DISPBUFF[2]=0;
	        		DISPBUFF[1]++;
					if(DISPBUFF[1]==10)
	        		{		 
	          			DISPBUFF[1]=0;
	          			DISPBUFF[0]++;
			  			if(DISPBUFF[0]==6)	DISPBUFF[0]=0;
					}
		  		}
			}
	  	}
	}
}    

int mode1() interrupt 0	   //����1�жϣ��ı��ʱ��״̬�����رջ��ߴ�
{
   if(TR0==1)
   {
   		TR0=0;
	 	uart_send_str("STATUS: STOP\r\n");
		uart_send_str("\r\r��ǰ��ʱ: \r");
		send_char_com(DISPBUFF[0]+48);
		send_char_com(DISPBUFF[1]+48);
		send_char_com('-');
		send_char_com(DISPBUFF[2]+48);
		send_char_com(DISPBUFF[3]+48);
		send_char_com('-');
		send_char_com(DISPBUFF[4]+48);
		send_char_com(DISPBUFF[5]+48);
		send_char_com('\n');
   }
   else 
   {
     	TR0=1;
	 	uart_send_str("STATUS: START\r\n");
   }
}

int mode2() interrupt 2		 //����2�ж�
{
   uint i;	 
   TR0=0;
   for(i=0;i<=5;i++)	DISPBUFF[i]=0;
   uart_send_str("\r\nSTATUS: CLEAR\r\n");
}

void usart() interrupt 4 using 1   // �����жϷ���������ֻ������ʱ��ʾ��������ֱ��ɾ�� 
{     
  if(RI)
  { 
  	RI=0;
    indata=SBUF;
  }
}

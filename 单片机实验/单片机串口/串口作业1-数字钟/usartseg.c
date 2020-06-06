#include<reg52.h>
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

extern	int bcd_to_led(uint x);	//����ӳ��򣬴���DISPBUFF[6]�е�����
//ȫ�ֱ�������
uchar idata DISPBUFF[6]={2,2,4,8,3,6};
uchar idata CLOCK[4]={0,0,0,0};
sbit udata=P3^6;
sbit uclk=P3^7;
sbit bell=P1^0;
uchar indata,mode=0;
uint number = 0;  // 1s��ʱҪ��
uint index_j=0,index_n=0;  //Уʱ����������ʱ�����±�

//��������
void init();  //��ʼ������
void display();	//��ʾ����
void delayms();
void serial_data(uchar  dd);
void send_char_com(unsigned char ch);
void uart_send_str(unsigned char *s);
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

/********************
��ʼ������ʾ����ʱ����
********************/
void init()	  //��ʼ��,��ʾ��ʱ�ӵ�
{
  	bell=1;
  //9600bps@11.0592MHz
    SCON = 0x50;	//8λ����,�ɱ䲨����
    TMOD = 0x21;	//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ����ʱ��0Ϊ1��ʽ
	ET0= 1;			//����T0�ж�
	TL1 = 0xFD;		
	TH1 = 0xFD;		
	TH0 = 0x3c;	
    TL0 = 0xb0;     //������ֵ50ms
	TR1 = 1;		//������ʱ��1
	TR0= 1;			//������ʱ��0
	ES = 1;			//���������ж� 
	EA = 1;			//�������ж�
   	uart_send_str("������ҵ��������U201713499\n\n");
	uart_send_str("\r\r�����ʽ���£�");
    uart_send_str("\r\r ʱ��Уʱ��j + xxxxxx + e");
	uart_send_str("\r\r �������ã�n + xxxx + e\r");	
} 

void display()
{
	uchar  i;
	
	for (i=0;i<=2;i++)
	{
     	serial_data(((DISPBUFF[4-2*i]<<4)|DISPBUFF[5-2*i])&0x000000ff);
    }
    delayms();

	if(DISPBUFF[0]==CLOCK[0]&&DISPBUFF[1]==CLOCK[1]&&DISPBUFF[2]==CLOCK[2]&&DISPBUFF[3]==CLOCK[3])	
	{
		bell=0;
	}
	else bell=1;	
}

void delayms()
{
	uint j;
	for(j=0;j<=20000;j++);
}


/**************************
�����ַ��ȴ�����س���
**************************/
void serial_data(uchar  dd)
{   
  uchar i;
  for (i=0;i<=7;i++)
  {
    if(bcd_to_led(dd>>i)) udata=1;
    else udata=0;
    uclk=1;  
    uclk=0;
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


/*******************
��ʱ���жϣ�1sʱ���һ
�����жϣ����������ַ�
*******************/

timer0() interrupt 1
{
  TH0 = 0X3c;
  TL0 = 0xb0;//���ü�����ֵ����ʱ50ms

  number++;

  if(number==20)
  {
     number=0;
	 DISPBUFF[5]++;
	 if(DISPBUFF[5]==10)
	 {
	  	 DISPBUFF[5]=0;
	  	 DISPBUFF[4]++;
	  	 if(DISPBUFF[4]==6)
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
					if(DISPBUFF[1]==10&&DISPBUFF[0]<2)
	        		{		 
	          			DISPBUFF[1]=0;
	          			DISPBUFF[0]++;
					}
					else if(DISPBUFF[0]==2&&DISPBUFF[1]==4)
					{
			  			DISPBUFF[0]=0;
			  			DISPBUFF[1]=0;
					}
		  		}
			}
	  	 }
	  }
	}
}    

void usart() interrupt 4 using 1   // �����жϷ������ 
{      
	if(RI)
  	{ 
		RI=0;
    	indata=SBUF;
		send_char_com(indata);
		if((indata<=57&&indata>=48)|indata=='n'|indata=='j'|indata=='e')
		{
   		if(indata=='j')	   //Уʱģʽ
   		{
     		mode=1;
			TR0=0;	 //Уʱ��ʱ�Ӳ���
   		}

   		if(indata=='n')	mode=2;		//����ģʽ

   		if(indata=='e')	  //����ģʽ�������
   		{
     		if(mode == 1)	//Уʱ
			{
				index_j=0;
			 	uart_send_str("\r\r����ʱ��ɹ�: \r");
				send_char_com(DISPBUFF[0]+48);
				send_char_com(DISPBUFF[1]+48);
				send_char_com('-');
				send_char_com(DISPBUFF[2]+48);
				send_char_com(DISPBUFF[3]+48);
				send_char_com('-');
				send_char_com(DISPBUFF[4]+48);
				send_char_com(DISPBUFF[5]+48);
				send_char_com('\n');
				uart_send_str("\r\r�����ʽ���£�");
    			uart_send_str("\r\r ʱ��Уʱ��j + xxxxxx + e");
				uart_send_str("\r\r �������ã�n + xxxx + e \r");
			}
			if(mode == 2)
			{
				index_n=0;
				uart_send_str("\r\r�������ӳɹ���\r");
				send_char_com(CLOCK[0]+48);
				send_char_com(CLOCK[1]+48);
				send_char_com('-');
				send_char_com(CLOCK[2]+48);
				send_char_com(CLOCK[3]+48);
				send_char_com('\n');
				uart_send_str("\r\r�����ʽ���£�");
    			uart_send_str("\r\r ʱ��Уʱ��j + xxxxxx + e");
				uart_send_str("\r\r �������ã�n + xxxx + e \r");
			}
			mode=0;
			TR0=1;	   //�ָ���ʱ��
   		}
   		
		if(indata<=57&&indata>=48&&mode==1&&index_j<6)	//	��ȡ����.Уʱ
   		{
     		DISPBUFF[index_j]=indata-48;
	 		index_j++;
	 	//	if(index_j==6)	index_j=0;
   		}
   		if(indata<=57&&indata>=48&&mode==2&&index_n < 4)	//����
   		{
     		CLOCK[index_n]=indata-48;
	 		index_n++;
	 		//if(index_n==4) index_n=0;
   		}
		}
		else
		{
			uart_send_str("\r\r�����ʽ����\n\n");
			uart_send_str("\r\r�����ʽ���£�");
    		uart_send_str("\r\r ʱ��Уʱ��j + xxxxxx + e");
			uart_send_str("\r\r �������ã�n + xxxx + e \r");
		}
  	}
}


#include<reg51.h>
#include<absacc.h>
#define uchar unsigned char
#define uint unsigned int

//��������
extern	int bcd_to_led(uint x);	//����ӳ��򣬴���DISPBUFF[6]�е�����
void delayms();	//��ʱ����
void display();	//��ʾ����
void time_jinwei_chuli();	//ʱ���λ������


// ȫ�ֱ�������
uint mode = 0; //1��ʾ����Сʱ��2��ʾ�������ӣ�0��ʾ������
uint second = 36,minute = 48,hour = 22,number = 0;   //�룬�֣�ʱ��ʱ���������
uint DISPBUFF[6]={2,2,4,8,3,6};	  //��ʼ���������ʾ
uint dian_state[6]={0,0,0,0,0,0}; //����ܵ��״̬,�����߲���

main()
{
	// ��ʱ������
	IE = 0x87;	    //1000 0111�������жϣ����ж�INT1,T0,INT0
	TCON = 0x15;    //0001 0101-->�ж�INT0��INT1ѡ���½��ش�������ʱ��T0������
	TMOD = 0x01;    //����ģʽ0,13λ��ʱ������
	TH0=-10000/256;	//һ�μ����ж�Ϊ10ms����Ҫ�ж�100�ε���1s
	TL0=-10000%256;
	while(1)  //����ѭ�����ȴ��ж�
	{
		display();	
	}			
}



void delayms()
{
   uchar i;
   for(i=200;i>0;i--){;}
}


void display()
{
	uchar i;
	P1=0xFE;//��һ����
	for(i=0;i<6;i++)
	{
		P2=bcd_to_led(DISPBUFF[i])|dian_state[i];//���û���ӳ����������״̬
		delayms();								 //�͵�״̬����õ�������ʾ״̬
		P1=(P1<<1)+1;	
	}
}

// �жϺ�������

int timer0() interrupt 1	  //��ʱ��0�ж�
{	
	TH0=-10000/256;	//һ�μ����ж�Ϊ10ms����Ҫ�ж�100�ε���1s
	TL0=-10000%256;	//�ж�ʱ���ó�ʼֵ
	number++;	//�жϴ�����1

	if(number == 100)	//1s
	{		
	   number = 0;	//����ֵ��Ϊ0
	   second++;	//������һ
	   time_jinwei_chuli();	//ʱ���λ������
	}
		
}

int MODE1() interrupt 0	//�ⲿmode�ж�
{
	delayms();
	switch(mode) //�ʼ������
	{
		//0��ʾ��������1��ʾ��Сʱ��2��ʾ������
		case 0:	   //������
			{
				dian_state[0]=0x80;
				dian_state[1]=0x80;
				mode=1;	//��������ת��һ״̬������Сʱ				
			};
			break;
		case 1:
			{
				dian_state[0]=0x00;
				dian_state[1]=0x00;
				dian_state[2]=0x80;
				dian_state[3]=0x80;
				mode=2;	//��ת��һ״̬����������
			};
			break;
		case 2:
			{
				dian_state[0]=0x00;
				dian_state[1]=0x00;
				dian_state[2]=0x00;
				dian_state[3]=0x00;
				mode=0; //��ת��һ״̬��������								
			};
			break;			
	}
}


int ADD() interrupt 2  //�ⲿ�жϣ�����ʱ��
{	
	delayms();

	if(mode==1)	  //��Сʱ
	{
		if(hour==23)hour=0;
		else hour++;
	}
	else if(mode==2)  //������
	{
		if(minute==59)minute=0;
		else minute++;
	}
	time_jinwei_chuli();
}


void time_jinwei_chuli()  //ʱ���λ������
{
  	if(second==60)	 //��60s
	{
	 	second=0;
	  	minute++;
	  	
		if(minute==60)
	  	{
	    	minute=0;
	    	hour++;
			if(hour==24)
			{
		  		hour=0;
			}
	  	}
	}

	DISPBUFF[0]=hour/10;
	DISPBUFF[1]=hour%10;
	DISPBUFF[2]=minute/10;
	DISPBUFF[3]=minute%10;
	DISPBUFF[4]=second/10;
	DISPBUFF[5]=second%10;	
}










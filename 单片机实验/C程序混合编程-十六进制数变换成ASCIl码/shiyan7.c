#include<absacc.h> 
extern  void turn_to_ascii(unsigned char p1, unsigned char p2);//�����ຯ��
extern  void init();  
void main(){ 
	unsigned char p1;  //p1ΪƬ�ⴢ��ת�Ƶ�ַ
	unsigned char p2;  //Ƭ�ڴ洢��ַ
	unsigned char num;   //������
	p1 = 0x00; //ƫ�Ƶ�ַΪ0
	p2 = 0x30; //Ƭ��30H��ʼ
	init();    //��ʼ�����ݣ����û��
	for(num = 0x00;num<0x14;num++){
		turn_to_ascii(p1,p2); //���ݵ�ַ
		p1 = p1 + 2;		  //Ƭ���ַת��2
		p2++;	//Ƭ��ת��1
	}	
}

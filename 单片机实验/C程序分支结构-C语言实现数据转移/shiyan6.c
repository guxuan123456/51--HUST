# include <absacc.h>

main()
{
  char xdata *p;	//�洢���ݳ�ʼλ��
  unsigned char begin = 0x16;
  unsigned int sum = 0;

  for(p=0x4050;p<0x4060;p++)	 //���ݳ�ʼ��
  {
  	 *p = begin;
	 begin++;
  }

  // ѭ����ȡ�����Сֵ��ƽ����
  XBYTE[0x4090] = 0;//���ֵ��ʼ��
  XBYTE[0x4091] = 0xFF;//��Сֵ��ʼ��

  for(p=0x4050;p<0x4060;p++)	 //���ݳ�ʼ��
  {
  	 sum+=*p;  //���

	 if(XBYTE[0x4090]<*p){
	   XBYTE[0x4090] = *p;
	 }

	 if(XBYTE[0x4091]>*p){
	   XBYTE[0x4091] = *p;
	 }
  }

   //��ƽ��ֵ������
    XBYTE[0x4080]  = sum/16;
	XBYTE[0x4081]  = sum%16;

  return 0;
}

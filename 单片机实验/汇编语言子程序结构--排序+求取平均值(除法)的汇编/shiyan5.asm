 /* ����ѡ�񲻻���ֽ�λ����������ѭ����������ʱ�����ǽ�λ���*/

	  ORG 0000H
	  LJMP MAIN
	  ORG 0100H

MAIN: MOV A,#20H	;��ʼֵ��λ
	  MOV DPTR,#4050H
	  MOV R2,#10H

	  ACALL INIT
	  ACALL AVERAGE
	  ACALL SORT
	  LJMP DONE

INIT: MOVX @DPTR,A
	  INC DPTR
	  DEC A	
	  MOV B,A
	  MOV A,#01H	   ;��λ����01H
	  MOVX @DPTR,A
	  MOV A,B
	  INC DPTR
	  DJNZ R2,INIT
	  MOV DPTR,#4050H
	  MOV R2,#10H
	  RET

AVERAGE: MOVX A,@DPTR
		 MOV B,A
		 MOV A,20H

		 ADD A,B
		 MOV 20H,A
		 MOV A,21H
		 ADDC A,#00H
		 MOV 21H,A
		 INC DPTR
		 INC DPTR
		 DJNZ R2,AVERAGE
		 MOV DPTR,#4051H
		 MOV R2,#10H
		 SJMP SUMHIGH

//������еĺͣ��ʹ���20H,21H������λ��Ϣ����22H����
SUMHIGH: MOVX A,@DPTR
		 MOV B,A
		 MOV A,21H

		 ADD A,B
		 MOV 21H,A
		 MOV A,22H
		 ADDC A,#00H
		 MOV 22H,A
		 INC DPTR
		 INC DPTR
		 DJNZ R2,SUMHIGH

		 MOV R5,#10H
      	 MOV R6,21H
	     MOV R7,20H
	     SJMP DIV_H2
		 RET
DIV_H2:			;������8λΪ00H����������8Ϊ��00H���������϶��ǵ��ֽ�
	MOV      A,R5
	MOV      R0,A		;R0�ݴ����
	MOV      B,A	
	MOV      A,R6					
	DIV      AB			;��������8λ��������
	JB       OV,UIDIV_END;��鵽������8λҲΪ00H��ֱ�ӽ�������
	MOV      R6,A					
	MOV      R5,B	;�̴���R6����������R5
	MOV      B,#08H	;��λ�����08H��

UIDIV_LOOP2:		;��8λ����
	MOV      A,R7
	RLC     A	 //�����Ƿ��λ
	MOV R7,A
    JC   NEXT	//��λ˵�����������1,��ʱ�������Ʋ�����1
    SJMP JIA0	//����λ���������0

JIA0: MOV A,R5
      RLC A	  	 //�õ�������Ҫ�ж������ͳ����Ĵ�С
	  MOV R5,A	 //�����浽R5
	  MOV 10H,R0		   //��10H��ʱ����������Ǹ�ֵ��
	  CJNE A,10H,CHANGE		//�н�λ��ת,�н�λ����С 
	  SJMP NEXT2

NEXT: MOV A,R5
      ADD A,R5
	  ADD A,#01H   //�õ�������Ҫ�ж������ͳ����Ĵ�С
	  MOV R5,A	   ///�����浽R5
	  MOV 10H,R0
	  CJNE A,10H,CHANGE
	  SJMP NEXT2	
CHANGE:	JNC NEXT2
        SJMP NEXT1
NEXT1:
//����С��������
	MOV A,R1
	ADD A,R1
	MOV R1,A
	DJNZ  B,UIDIV_LOOP2	//���������ڼ�����
	SJMP DONE1
NEXT2: //��������
    SUBB A,R0	
    MOV R5,A
    MOV A,R1
	ADD A,R1	
	ADD A,#01H
	MOV R1,A
	DJNZ   B,UIDIV_LOOP2	//�������ڼ�����
	SJMP DONE1
UIDIV_END:	
	SJMP DONE1

DONE1:	 //���������洢��
	MOV 22H,R1
	MOV 23H,R6
    MOV 24H,R5
	MOV A,22H
	MOV DPTR,#4080H
	MOVX @DPTR,A
	INC DPTR
	MOV A,23H
	MOVX @DPTR,A
	INC DPTR
 	MOV A,24H
	MOVX @DPTR,A
	RET




SORT: MOV DPTR,#4050H
	  MOV R0,#30H
	  MOV R2,#20H
	  SJMP MOVE

MOVE: MOVX A,@DPTR
      MOV @R0,A
	  INC R0
	  INC DPTR
	  DJNZ R2,MOVE
	  MOV R0,#4EH
	  MOV R2,#10H
	  MOV DPTR,#4050H
	  SJMP PAIXU

PAIXU: MOV A,@R0
	   MOVX @DPTR,A
	   INC DPTR
	   INC R0
	   MOV A,@R0
	   MOVX @DPTR,A
	   INC DPTR
	   DEC R0
	   DEC R0
	   DEC R0
	   DJNZ R2,PAIXU
	   RET
	  
DONE: SJMP DONE
END
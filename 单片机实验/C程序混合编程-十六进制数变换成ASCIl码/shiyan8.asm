    DE  SEGMENT CODE      
	PUBLIC   init,_turn_to_ascii   
	RSEG   DE 
//��ʼ��30H��ʼ��20�����ֽ�ʮ��������
init: 		MOV R1,#14H  //20��ֵ
			MOV R0,#30H	 //��ʼ��ַ
			MOV A,#00H  //��ʼֵ
XUNHUAN:    MOV @R0,A
			INC A
			INC R0
			DJNZ R1,XUNHUAN  
    		RET 
			

_turn_to_ascii: MOV A,R5  ;ȡ����p2 
			MOV R0,A
			MOV  R1,  #50H           
		    MOV  @R1,  #0          
		    MOV  A,  @R0		//ȡ������
			//����ת��
		    XCHD  A,  @R1           
		    ORL  50H,  #30H           
		    SWAP  A
		    ORL  A,  #30H              
		    MOV  51H,  A 
		  	MOV A,R7   ;ȡ����p1
			MOV R2,A
		 	MOV DPTR,#6000H
			JZ ZHUANYI
LOOP:		INC DPTR
			DJNZ R2,LOOP 
ZHUANYI:	MOV  R1, #50H
			MOV  A, @R1
			MOVX @DPTR,A
			INC DPTR
			INC R1
			MOV  A, @R1
			MOVX @DPTR,A
     		RET 
			END

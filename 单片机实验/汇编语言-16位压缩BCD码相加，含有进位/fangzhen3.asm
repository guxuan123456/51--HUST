;File name:    fangzhen3.asm
;Description:  ˫�ֽ�BCD�����
;Date:  	   2020.3.24
;Designed by: 	xuan gu
/* ˼·������Ͱ�λ��������ӣ�����浽�Ͱ�λ31H�У���λ����30H��
		���ż���߰�λ��������ӣ��ټ���30H�еĽ�λ��Ϣ���õ��߰�λ����30H����λ����32H*/

									  

	        ORG  0000H		
			LJMP MAIN
			ORG  0100H


MAIN:	   	MOV  SP,  #40H           ;����ջָ��
            CLR  C               	 ;��λλ����

		    MOV  20H,  #49H          ;20H��Ԫ��ֵ
		    MOV  21H,  #87H          ;21H��Ԫ��ֵ
            MOV  22H,  #69H          ;22H��Ԫ��ֵ
		    MOV  23H,  #82H          ;23H��Ԫ��ֵ
            MOV  24H,  #13H          ;24H��Ԫ��ֵ
		    MOV  25H,  #14H          ;25H��Ԫ��ֵ

		    MOV  A,    20H            ;20H+22H 
		    ADD  A,    22H
		    DA A                      ; BCD����
		    MOV  31H,    A			  ;ǰ������λ�������31H
		    MOV   A,32H
		    ADDC  A,#00H              ;����λ����32H
            MOV  32H,    A 

		    MOV  A,    31H            ;22H+20H+24H 
		    ADD  A,    24H
		    DA A                       ; BCD����
		    MOV  31H,    A			  ;��λ�������31H
		    MOV   A,32H
		    ADDC  A,#00H              ;����λ���ڸ�λ32H
            MOV  32H,    A 

			//��ʼ�Ӹ߰�λ
			CLR  C 
			MOV  A,    21H            ;21H+�Ͱ�λ��λ
		    ADD  A,    32H
		    DA A                      ; BCD����
		    MOV  30H,    A			  ;��λ�������30H
		    MOV   A, #00H
		    ADDC  A,#00H              ;����λ����32H
            MOV  32H,    A 



            MOV  A,    30H            ;21H+23H 
		    ADD  A,    23H
		    DA A                       ; BCD����
		    MOV  30H,    A
		    MOV   A,32H
		    ADDC A,#00H              ;����λ���ڸ�λ32H
            MOV 32H,    A 
		 
		    
            MOV  A,    30H            ;21H+23H+25H 
		    ADD  A,    25H
		    DA A                       ; BCD����
		    MOV  30H,    A
		    MOV   A,32H
		    ADDC A,#00H              ;����λ���ڸ�λ32H
            MOV 32H,    A 

HERE:	    SJMP  HERE                ;̤��
		    END 

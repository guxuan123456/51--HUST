;File name:    fangzhen3_teacher.asm
;Description:  1�ֽ�BCD�����
;Date:  	   2020.3.24
;Designed by: 	xuan gu
;Source used:    
;   31H+32H+33H+34H BCD data ->35H+36H(��λ) BCD data 
;



	        ORG  0000H		
			LJMP MAIN
			ORG  0100H


MAIN:	   	MOV  SP,  #40H           ;����ջָ��
            CLR  C               	 ;��λλ����

		    MOV  31H,  #349H          ;31H��Ԫ��ֵ
		    MOV  32H,  #87H          ;32H��Ԫ��ֵ
            MOV  33H,  #69H          ;33H��Ԫ��ֵ
		    MOV  34H,  #82H          ;34H��Ԫ��ֵ
            MOV  35H,  #00H          ;35H��Ԫ��ֵ
		    MOV  36H,  #00H          ;36H��Ԫ��ֵ

		    MOV  A,    31H            ;32H+31H 
		    ADD  A,    32H
		    DA A                       ; BCD����
		    MOV  35H,    A
		    MOV   A,36H
		    ADDC A,#00H              ;����λ���ڸ�λ36H
            MOV  36H,    A 

		    MOV  A,    35H            ;32H+31H+33H 
		    ADD  A,    33H
		    DA A                       ; BCD����
		    MOV  35H,    A
		    MOV   A,36H
		    ADDC A,#00H              ;����λ���ڸ�λ36H
            MOV  36H,    A 
            MOV  A,    35H            ;32H+31H+33H+34H 
		    ADD  A,    34H
		    DA A                       ; BCD����
		    MOV  35H,    A
		    MOV   A,36H
		    ADDC A,#00H              ;����λ���ڸ�λ36H
            MOV 36H,    A 
		 
HERE:	    SJMP  HERE                ;̤��
		    END 


	  	  	ORG 0000H
			LJMP MAIN
		
			ORG 0100H
		
		MAIN:MOV SP, #40H ;����ջָ��
		//Ƭ�ڸ�ֵ���Ͱ�λ��ǰ���߰�λ�ں�
		    MOV 20H, #LOW(5152H)
			MOV 21H, #HIGH(5152H) ;
		    MOV 22H, #LOW(5354H)
			MOV 23H, #HIGH(5354H)
			MOV 24H, #LOW(5556H)
			MOV 25H, #HIGH(5556H)
			MOV 26H, #LOW(5758H)
			MOV 27H, #HIGH(5758H)
		    
		//Ƭ�����ݸߵͰ�λ����֮��任ΪASCII��֮����Ƭ��RAM
			MOV DPTR, #3000H

			MOV A,21H
			ANL A, #0FH
			ORL A, #30H
			MOVX @DPTR, A
			INC	DPTR
			MOV A,21H
			ANL A,#0F0H
			SWAP A
			ORL A, #30H
			MOVX @DPTR, A
			INC	DPTR

			MOV A,20H
			ANL A, #0FH
			ORL A, #30H
			MOVX @DPTR, A
			INC	DPTR
			MOV A,20H
			ANL A,#0F0H
			SWAP A
			ORL A, #30H
			MOVX @DPTR, A
			INC	DPTR

			MOV A,23H
			ANL A, #0FH
			ORL A, #30H
			MOVX @DPTR, A
			INC	DPTR
			MOV A,23H
			ANL A,#0F0H
			SWAP A
			ORL A, #30H
			MOVX @DPTR, A
			INC	DPTR

			MOV A,22H
			ANL A, #0FH
			ORL A, #30H
			MOVX @DPTR, A
			INC	DPTR
			MOV A,22H
			ANL A,#0F0H
			SWAP A
			ORL A, #30H
			MOVX @DPTR, A
			INC	DPTR

			MOV A,25H
			ANL A, #0FH
			ORL A, #30H
			MOVX @DPTR, A
			INC	DPTR
			MOV A,25H
			ANL A,#0F0H
			SWAP A
			ORL A, #30H
			MOVX @DPTR, A
			INC	DPTR
		

			MOV A,24H
			ANL A, #0FH
			ORL A, #30H
			MOVX @DPTR, A
			INC	DPTR
			MOV A,24H
			ANL A,#0F0H
			SWAP A
			ORL A, #30H
			MOVX @DPTR, A
			INC	DPTR

			MOV A,27H
			ANL A, #0FH
			ORL A, #30H
			MOVX @DPTR, A
			INC	DPTR
			MOV A,27H
			ANL A,#0F0H
			SWAP A
			ORL A, #30H
			MOVX @DPTR, A
			INC	DPTR

			MOV A,26H
			ANL A, #0FH
			ORL A, #30H
			MOVX @DPTR, A
			INC	DPTR
			MOV A,26H
			ANL A,#0F0H
			SWAP A
			ORL A, #30H
			MOVX @DPTR, A
			INC	DPTR
	   END
		/*
		File name: e1.asm
		
		Description: 1�ֽ�BCD��ת��Ϊ2�ֽ�ASCII
		
		2�ֽ�ASCII��ת��Ϊ1�ֽ�BCD��
		
		Date:
		
		Designed by:
		
		Source used: 30H: BCD data
		
		31H, 32H��ASCII data
		
		31H, 32H ->33H?BCD data
		*/
		
		ORG 0000H
		
		LJMP MAIN
		
		ORG 0100H
		
		MAIN:MOV SP, #40H ;����ջָ��
		
		MOV 30H,#49H;30H��Ԫ��ֵ
		
		MOV R0, #32H ;R0ָ�븳ֵ
		
		MOV @R0, #0 ;32H��Ԫ����
		
		MOV A, 30H
		
		XCHD A, @R0 ;����ֽ�
		
		ORL 32H, #30H ;ת��ΪASCII
		
		SWAP A
		
		ORL A, #30H ;ת��ΪASCII
		
		MOV 31H, A ;�������31H��Ԫ
		
		MOV A, 31H;��31H��Ԫȡֵ
		
		ANL A, #0FH;ת��ΪBCD
		
		SWAP A
		
		MOV 33H, A;�������33H��Ԫ
		
		MOV A, 32H;��32H��Ԫȡֵ
		
		ANL A, #0FH;ת��ΪBCD
		
		ORL 33H, A;�ϲ��ֽ�
		
		HERE:SJMP HERE ;̤��
		
		END

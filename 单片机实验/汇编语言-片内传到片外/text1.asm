		
		/*
		File name: text1.asm
		
		Date: 2020.15.03
		
		Designed by: xuan Gu
		
		Source used: R0: jishuqi
		
		DPTR:;Ƭ������ָ��
		*/

		
		ORG 0000H
		
		LJMP MAIN
		
		ORG	0100H
		
		MAIN: MOV SP,#40H
		
		FILL: CLR A ; A�Ĵ�������
		
		MOV R0, #00H;��ѭ��������
		
		MOV DPTR, #7000H;������ָ��
		
		FILL1:	MOVX @DPTR, A;���͵�Ƭ��RAM
		
		INC A;A���ݼ�1
		
		INC DPTR;�޸�����ָ��
		
		INC R0;�޸�ѭ��������
		
		CJNE R0, #00H, FILL1
		
		HERE:	SJMP HERE;ԭ��̤��
		
		END

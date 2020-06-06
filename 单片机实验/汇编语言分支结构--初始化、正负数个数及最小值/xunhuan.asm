	  ORG 0000H
	  LJMP MAIN
	  ORG 0100H

MAIN: MOV A,#-08H	;���ó�ʼֵ
	  MOV R0,#1EH	;��һ��ַΪ20
	  MOV R2,#13H	;18����ֵ

// ��ʼ������
INIT: INC A
	  INC R0
	  MOV @R0,A
	  DJNZ R2,INIT
		
	  MOV R0,#20H	
	  MOV R2,#13H		
	  MOV 63H,#0H		;�������ֵ
	  MOV 64H,#-1H		; ������Сֵ
	  SJMP START

START: MOV A,@R0
	   DJNZ R2,NEXT
	   SJMP DONE

NEXT:  JZ ZERO	          ;X=0
	   JB ACC.7, NEGATIVE  ;X<0
	   SJMP  POSITIVE		;X>0


ZERO:  MOV A, 62H		  ;X=0
	   INC A
	   MOV 62H, A
	   INC R0
	   SJMP START

NEGATIVE: MOV B,64H
		  MOV 64H,A			 ;X<0		
		  MOV A, 61H		;��������  
          INC A
          MOV 61H, A
          INC R0
					 
		  MOV A,64H		   ;MIN
          CJNE A,B,CHANGE1

	   	  SJMP START

CHANGE1: JNC SMALL									;������Сֵ
		 MOV 64H,A
		 SJMP START

SMALL: MOV 64H,B
	   SJMP START

POSITIVE: MOV B,63H
		  MOV 63H,A
		  MOV A, 60H		  ;X>0
		  INC A
		  MOV 60H, A
		  INC R0

		  MOV A,63H		   ;MAX
          CJNE A,B,CHANGE2
		  
	   	  SJMP START

CHANGE2: JNC BIGGER
		 MOV 63H,B
		 SJMP START 

BIGGER: MOV 63H,A
		SJMP START

DONE: 	SJMP DONE

END
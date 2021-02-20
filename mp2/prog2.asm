; Alex Kim netid:alexk4 2/19/2021
; This program will print out a calcution of the squence of numbers and operators input 
; in reverse polish notation. It does this by making use of a stack. The program first
; waits for an input and then echoes it to the screen. This input is checked to see if
; it is an operand or a operator and goes through the necessary calculations by popping
; and pushing values from and to the stack. Once an equal sign is detected and the stack
; only has one value, the decimal solution is held in R5 and the hexadecimal solution is
; written in ASCII to the screen.
;partners: egchen2
;
; table of register use in this part of the code
;    R0 holds character inputted and later used to print
;    R1 used as a temporary register that checks the character inputted
;    R2 used as a temporary register in operator subroutine
;    R3 holds first popped operand
;    R4 holds second popped operand
;    R5 used as error check and to check stack
;    R6 used to check stack
;	 (many temporary registers used for PRINT_HEX subroutine arbitrarily)


.ORIG x3000
	
;your code goes here

;Read next input
NEXTCHAR
	GETC
	OUT

	AND R3,R3,#0
	AND R4,R4,#0

;Check if '=' inputted
	LD	R1,EQUALSIGN
	ADD R1,R1,R0
	BRz CHECK

;Check if space inputted
	ADD R1,R0,#-16
	ADD R1,R1,#-16
	BRz NEXTCHAR
	
;Check if input is valid and operator or operand and pop and push accordingly
	LD 	R1,MULTSIGN		;Checks if operator is multiplication
	ADD R1,R1,R0
	BRnp #10			;Skips to check next operator
	JSR POP				;Pops two values to R3 and R4 if correct operator
	ADD R5,R5,#0
	BRp	INVALID
	ADD R4,R4,R0
	JSR POP
	ADD R5,R5,#0
	BRp	INVALID
	ADD R3,R3,R0
	JSR MUL				;Goes to operator subroutine
	BR	GOPUSH			;Goes to push the solution

	LD 	R1,ADDSIGN		;Checks if operator is addition
	ADD R1,R1,R0
	BRnp #10
	JSR POP
	ADD R5,R5,#0
	BRp	INVALID
	ADD R3,R3,R0
	JSR POP
	ADD R5,R5,#0
	BRp	INVALID
	ADD R4,R4,R0
	JSR PLUS
	BR	GOPUSH

	LD 	R1,SUBSIGN		;Checks if operator is subtraction
	ADD R1,R1,R0
	BRnp #10
	JSR POP
	ADD R5,R5,#0
	BRp	INVALID
	ADD R4,R4,R0
	JSR POP
	ADD R5,R5,#0
	BRp	INVALID
	ADD R3,R3,R0
	JSR MIN
	BR	GOPUSH

	LD 	R1,DIVSIGN		;Checks if operator is division
	ADD R1,R1,R0
	BRnp #10
	JSR POP
	ADD R5,R5,#0
	BRp	INVALID
	ADD R4,R4,R0
	JSR POP
	ADD R5,R5,#0
	BRp	INVALID
	ADD R3,R3,R0
	JSR DIV
	BR	GOPUSH

	LD 	R1,EXPSIGN		;Checks if operator is exponent
	ADD R1,R1,R0
	BRnp #10
	JSR POP
	ADD R5,R5,#0
	BRp	INVALID	
	ADD R4,R4,R0
	JSR POP
	ADD R5,R5,#0
	BRp	INVALID
	ADD R3,R3,R0
	JSR EXP
	BR	GOPUSH

	LD 	R1,ZERO			;Checks if operand is between 0-9
	ADD R0,R1,R0
	BRn INVALID
	ADD R1,R0,#-9
	BRp INVALID
	BR 	GOPUSH

;Push calculated solution to operation onto stack

GOPUSH
	JSR PUSH
	BR	NEXTCHAR

;Check to see if stack has only one value if '=' is detected

CHECK
	LD R6,STACK_START		;Finds x3FFF to compare to STACK_TOP to find whether there is only one value
	AND R5,R5,#0
	ADD R5,R6,#-1
	NOT R5,R5
	ADD R5,R5,#1
	LD 	R6,STACK_TOP
	ADD R5,R6,R5			
	BRnp INVALID			;If not, invalid
	JSR POP					;If so, pop the value and get ready to print final solution
	AND R3,R3,#0
	ADD R3,R3,R0
	JSR PRINT_HEX	

;Finished

DONE
	HALT

;Invalid Expression was inputted

INVALID					;In the cases that stack has more than one value or stack underflow occurs
	LD R0,STR_START
	PUTS
	HALT

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal

;Store decimal solution in R5 and convert to hex solution written in ASCII to print to display

PRINT_HEX

	ST	R7,SAVER7		;Save R7

	AND R5,R5,#0		; Clear R5
	ADD R5,R5,R3		; Decimal solution in R5
	AND R1,R1,#0
	ADD R1,R1,#4		; Initialize hex digit loop count to 4

EXTRACT
	AND R4,R4,#0		; Clear R4
	AND R0,R0,#0		; Clear R0
	ADD R0,R0,#4		; Initialize binary digit loop count to 4
EXTRACT_LOOP
	ADD R4,R4,R4		; Shift to copy next bit
	ADD R3,R3,#0		; Check for 1 or 0 bit
	BRzp SHIFT			; Skip ahead if 0 bit found
	ADD R4,R4,#1		; Add 1 if 1 bit found
SHIFT
	ADD R3,R3,R3		; Shift to check next bit
	ADD R0,R0,#-1		; Decrement counter
	BRp EXTRACT_LOOP	; Go through and copy 4 bits of 'binary'
	ADD R0,R4,#-10		; Check if number is 0 to 9
	BRzp MORE_THAN_NINE ; Skip ahead if more than 9
	LD	R0,FOUREIGHT	; Add #48 to print ASCII value 0 to 9
	BR	PRINT
MORE_THAN_NINE
	LD	R0,FIVEFIVE		; Add #55 to print ASCII value A to F
PRINT
	ADD R0,R4,R0		; Print ASCII value
	OUT
	ADD R1,R1,#-1		;Decrement counter
	BRp EXTRACT			; Go through and print 4 bits of 'hex'

	LD R7,SAVER7		;Restore R7

	RET


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here
						;Simply adds two numbers
	AND R0,R0,#0
	ADD R0,R3,R4
	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here
						;Converts second number to negative and adds
	AND R0,R0,#0
	NOT R4,R4
	ADD R4,R4,#1
	ADD R0,R3,R4
	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
	AND R0,R0,#0
	AND R1,R1,#0
	
MULLOOP					;Adds first number, second number of times
	ADD R1,R1,R3
	ADD R4,R4,#-1
	BRp MULLOOP
	BRn MULZERO

	ADD R0,R0,R1
	RET

MULZERO					;In the case that the second value is 0
	ADD R0,R0,#0
	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
	AND R0,R0,#0
	AND R1,R1,#0
	ADD R1,R1,R3
	NOT R4,R4
	ADD R4,R4,#1

DIVLOOP				;Increments number of times the number can be subtracted before 0
	ADD R0,R0,#1
	ADD	R1,R1,R4
	BRzp DIVLOOP

	ADD R0,R0,#-1
	RET	

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
	AND R0,R0,#0	
	ADD R3,R3,#0
	BRz EXPZERO
	ADD R4,R4,#0
	BRz EXPONE	
	

	AND R1,R1,#0
	ADD R4,R4,#-1
	
OUTLOOP				;Determines how many times the base is multiplied by itself
	ADD R2,R2,R3
INLOOP				;Multiplies the base by itself 
	ADD R1,R1,R3
	ADD R2,R2,#-1
	BRp INLOOP

	ADD R4,R4,#-1
	BRnp OUTLOOP

	ADD R0,R0,R1
	RET

EXPZERO				;Used in the case the base is 0
	ADD R0,R0,#0
	RET	

EXPONE				;Used in the case the power is 0
	ADD R0,R0,#1
	RET

;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R4
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
SAVER7		.BLKW #1	;Saves R7 to be restored again
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;Used to compare stack top and check for only one value
STACK_TOP	.FILL x4000	;
EQUALSIGN	.FILL #-61	;Operator values in ASCII to check input character
MULTSIGN	.FILL #-42	;
ADDSIGN		.FILL #-43	;
SUBSIGN		.FILL #-45	;
DIVSIGN		.FILL #-47	;
EXPSIGN		.FILL #-94	;
ZERO		.FILL #-48	;Used to check operand between 0 and 9 
STR_START	.FILL STRING	; string starting address
STRING		.STRINGZ "Invalid Expression"
FOUREIGHT	.FILL #48	; Decimal number to zero to nine ASCII
FIVEFIVE	.FILL #55	; Decimal number to A to F

.END

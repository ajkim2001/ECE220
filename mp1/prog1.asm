;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST
	
; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments

; Alex Kim netid:alexk4 2/5/2021
; This program will print out a histogram that counts the number of each 
; letter and non-letter used in a string. I accomplished this by printing
; the character and space first in each line, then copying the calculated
; values into a hex format, and then printing the ASCII values.
; To print the ASCII values in hex format, I had to check each digit 
; to see if it was greater than 9 to print A-F. After that, I looped back
; to print all 27 lines while incrementing the first character of each line.
; partners: seltzer6, egchen2

; table of register use in this part of the code
;    R0 used as a temporary register for all printing uses
;    R1 used as the loop count during histogram printing
;    R2 holds a pointer to the histogram (x3F00)
;    R3 holds value at histogram address during copying
;    R4 holds the copied value during copying
;    R5 used as the loop count during copying
;    R6 used to print the first ASCII character of each line


	; Initialize registers 

	LD R6,CHAR_BINS		; Start R6 before @ ASCII decimal value
	LD R1,NUM_BINS		; Initialize loop count to 27
	LD R2,HIST_ADDR     ; Point R2 to the start of the histogram

	; Loop to print histogram starts here
	
BINLOOP	
	ADD R6,R6,#1		; Increment next ASCII character
	AND R0,R0,#0      	; Clear R0
	ADD R0,R6,R0		; Print first character
	OUT
	LD	R0,SPACE		; Print space
	OUT					; 

	; 4 digit hex copy starts here

	LDR R3,R2,#0		; Loads data at current histogram address
	AND R5,R5,#0		; Clear R5
	ADD R5,R5,#4		; Initialize hex digit loop count to 4

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
	ADD R5,R5,#-1		;Decrement counter
	BRp EXTRACT			; Go through and print 4 bits of 'hex'

	; Next line print and prepare until all 27 lines printed

	LD	R0,NEW			; Load x000A new line into R0
	OUT					; Print new line

	ADD R2,R2,#1		; Go to next line of histogram
	ADD R1,R1,#-1		; Decrement loop count
	BRp BINLOOP			; Continue until loop count reaches zero




DONE	HALT			; Done


; the data needed by the program
NEW			.FILL x000A	; Used by OUT to print a new line
CHAR_BINS	.FILL #63	; Used to print first character of each line
SPACE		.FILL #32	; Used to print space
NUM_BINS	.FILL #27	; 27 loop iterations
FOUREIGHT	.FILL #48	; Decimal number to zero to nine ASCII
FIVEFIVE	.FILL #55	; Decimal number to A to F
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END

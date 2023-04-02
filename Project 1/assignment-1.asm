; The number C must be found which lies between 2 other numbers A and B.
; A and B are both even numbers and A is less than B.
; The missing instructions are filled in.
.ORIG x3000 ;Start from address x3000
LD R0,A ; Loads the value from A into R0 
LD R1,B ; Loads the value from B into R1
X NOT R2,R0 ; Finds the inverse value of R0 and stores it in R2 (a)
ADD R2,R2,#1 ;Counts R2 1 so you get the negative value of R0 and save in R2 (b)
ADD,R2,R2,R1 ;Adds R2 to R1 and saves in R2 (since R2 is negative, R2 is actually subtracted from R1)
BRz DONE ;If the previous instruction returned 0: go to DONE (c)
ADD,R1,R1,#-1 ; Counts B 1 down
ADD R0,R0,#1 ;Counts A 1 up 
BRnzp X ;If the previous instruction gave something negative, 0 or positive: go to X
DONE ST R1,C ;Save the value in R1 in C
TRAP x25 ; Stop the program
A .BLKW #1 ; ; Reserve 1 location in memory and call it A 
B .BLKW #1 ; Reserver 1 lokation i hukkkomelsen og kald den B
C .BLKW #1 ; Reserver 1 lokation i hukkkomelsen og kald den C
.END
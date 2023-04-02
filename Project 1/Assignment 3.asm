; Must find out if a number between 0 and 99 is a prime number
; Prime numbers under 99 are:
; 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97  If it is,so load1 into R0, otherwise,load 0 into R0
        .ORIG x3000
        JSR isPrime; Call isPrime subroutine and save the return address 
        HALT ;  Stop the program
;
; WE have a number saved in R1 and we want to checK if it is a prime number
isPrime ST R7,RETURNADDRESS ; Save the return address , saved in R7 to memory when the subroutin finishes
        LEA R3, ARRAY; We define a pointer R3 , innitilized to point to the first address of the array , which contains all prime numbers from 0 to 100
REPEAT    LDR R0,R3,#0 ; We take the first value, R3 point to (the first prime number of the array in the memory) and save it to R0
        BRz DONE ; check If the value stored in R0 is zero ( null terminated array = the end of array) so take the branch DONE
; We want to check if the given number R1 matches  the value in R0 (Does R1= R0 ? <=> chech R1-R0 = 0)
        NOT R0,R0 ;  R0 1s complement
        ADD R0,R0,#1 ; R0 2s complement
        ADD R0,R0,R1 ; if R1 match Ro that means R1 is prime number
        BRz YES ; if the subtraction is zero , the number is prime so take the branch YES
        ADD R3,R3,#1 ; Otherwise let R3 point to the next item ( next prime number) in our array
        BR REPEAT ;  Unconditional branch to go to the branch REPEAT to check again
YES   AND R0,R0,#0 ;  Clear R0
        ADD R0,R0,#1 ;  load R0 with 1
DONE    LD R7,RETURNADDRESS ;  Get the return address from memory and load it again into R7
        RET  ; Return from subroutine 
;
;Data
RETURNADDRESS   .BLKW #1 ;  Here where we declare and save the return adress of the subroutine isPrime
ARRAY           .FILL #2  ; Declare and initialize the array in memory , which includes prime numbers from 0 to 100
                .FILL #3
                .FILL #5
                .FILL #7
                .FILL #11
                .FILL #13
                .FILL #17
                .FILL #19
                .FILL #23
                .FILL #29
                .FILL #31
                .FILL #37
                .FILL #41
                .FILL #43
                .FILL #47
                .FILL #53
                .FILL #59
                .FILL #61
                .FILL #67
                .FILL #71
                .FILL #73
                .FILL #79
                .FILL #83
                .FILL #89
                .FILL #97
NULL            .FILL #0     ;Null terminated array
                .END         ;End the program
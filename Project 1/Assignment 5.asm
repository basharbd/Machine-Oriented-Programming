; merge all subroutines in a single program
; we will not repeat the comments , it were in the prior assignments
        .ORIG x3000
FOREVER JSR readS
        AND R1,R1,#0
        ADD R1,R1,R0
        JSR isPrime
        JSR resultS
        BR FOREVER
        HALT


readS   ST R7,RETURN 
        LEA R0,MESSAGE 
        PUTS 
        GETC 
        OUT 
        LD R4,ASCII 
        ADD R0,R0,R4 
        AND R4,R4,#0
        AND R1,R1,#0 
        ADD R1,R1,#10 
        JSR MULT1 
        GETC 
        OUT 
        LD R4,ASCII 
        ADD R0,R0,R4 
        AND R4,R4,#0 
        ADD R0,R2,R0 
        LD R7,RETURN 
        RET 


isPrime ST R7,RETURNADDRESS 
        LEA R3, ARRAY
REPEAT  LDR R0,R3,#0 
        BRz DONE 
        NOT R0,R0
        ADD R0,R0,#1
        ADD R0,R0,R1 
        BRz YES
        ADD R3,R3,#1 
        BR REPEAT  
YES     AND R0,R0,#1 
        ADD R0,R0,#1 
DONE    LD R7,RETURNADDRESS
        RET



resultS ST R7,RETURNADDRESS1
        ADD R0,R0,#0
        BRz NEJ
        BR YESPRIM
NEJ     LEA R0,NEJMESSAGE
        PUTS 
        BR DONE1 
YESPRIM LEA R0,JAMESSAGE
        PUTS  
DONE1   LD R7,RETURNADDRESS1 
        RET 




MULT1   AND R2,R2,#0  
        ADD R2,R0,#0 
        BR MULT2 
MULT2   ADD R1,R1,#-1 
        BRnz DONE2 
        ADD R2,R2,R0 
        BR MULT2 
DONE2   AND R1,R1,#0 
        RET  



; Data
RETURN          .BLKW #1 
RETURNADDRESS   .BLKW #1 
RETURNADDRESS1  .BLKW #1 
ASCII          .FILL #-48 
ARRAY           .FILL #2
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
NULL            .FILL #0
JAMESSAGE       .STRINGZ "\nThe number is prime\n"
NEJMESSAGE      .STRINGZ "\nThe number is not prime\n"
MESSAGE         .STRINGZ "Input a 2 digit decimal number:"
                .END
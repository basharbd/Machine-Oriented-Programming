;   The program read R0 , if zero prints " The number is not prime" otherwise prints " The number is prime"
        .ORIG x3000
        JSR resultS ; Call resultS subroutine
        HALT   ; End the program
;
;
resultS ST R7,RETURNADDRESS1 ; Store the return address from R7 to memory
        ADD R0,R0,#0 ; Just check R0
        BRz NEJ ; If R0 is Zero take the branch NOPE
        BR YESPRIM; Otherwise take the unconditional branch YESPRIM
NEJ     LEA R0,NEJMASSEGE ; The address of the string which we want to print 
        PUTS  ; Print the message from Ro
        BR DONE ; unconditional branch to DONE label
YESPRIM LEA R0,JAMESSAGE ; The address of the string which we want to print
        PUTS ; Print the message from Ro
DONE    LD R7,RETURNADDRESS1 ;  Load the return address from memory to R7
        RET  ; Return from the subroutine

; Data
RETURNADDRESS1   .BLKW #1 ; Save the return address her in memory
JAMESSAGE        .STRINGZ "The number is prime"  
NEJMASSEGE       .STRINGZ "The number is not prime"
                 .END     ; End the program
; Der skal findes tallet C der ligger mellem 2 andre tal A og B.
; A og B er begge lige numre og A er mindre end B.
; De manglende instruktioner udfyldes.
    .ORIG x3000                 ; Der startes fra adresse x3000
    LD R0,A                 ; Loader værdien fra A i R0
    LD R1,B                  ; Loader værdien fra B i R1
    
X   NOT R2,R0                  ; Finder den inverse værdi af R0 og gemmer den i R2 (a)

    ADD R2,R2,#1                   ; Tæller R2 1 op så man får den negative værdi af R0 og gem i R2 (b)
    ADD,R2,R2,R1                    ; Lægger R2 til R1 og gemmer i R2 (siden R2 er negativt bliver R2 reelt trukket fra R1)
    BRz DONE ;                        Hvis den forrige instruktion gav 0: gå videre til DONE (c) 
    
    ADD,R1,R1,#-1                     ; Tæller B 1 ned
    ADD R0,R0,#1                     ; Tæller A 1 op (d)   
    BRnzp X                      ; Hvis den forrige instruktion gav noget negativt, 0 eller positivt: gå til X
    
DONE ST R1,C                          ; Gem værdien i R1 i C

    TRAP x25 ; Stop programmet
    
A   .BLKW #1 ; Reserver 1 lokation i hukkkomelsen og kald den A
B   .BLKW #1 ; Reserver 1 lokation i hukkkomelsen og kald den B
C   .BLKW #1 ; Reserver 1 lokation i hukkkomelsen og kald den C
    .END

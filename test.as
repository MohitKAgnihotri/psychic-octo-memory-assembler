.entry W
.extern V
   add $15,$27,$31
move $10,$20
    mvhi $3,$13
    mvlo $21,$22
addi $4,-44,$23
 subi $31,564,$12
 andi $12,157,$21
 blt $3,$22,MAIN
.extern Z
 beq $23,$10,F
  bgt $9,$8,MAIN
lb $4,345,$7
 sb $15,231,$2
 lw $30,-332,$31
 jmp Z
 sh $12,-23,$23
 jmp $2
  jmp V
  la F
  call V
  W: .db 1,34,76,24
   .dh 23,45,75,32
   .dw 21314,32423,5645,675
STR: .asciz "nadav pivonia"
stop

<<<<<<< HEAD
<mian>:
    addi sp,sp,-4
    sw ra,0(sp)
    addi a0,x0,-1
    addi a1,x0,2
    jal ra ,absadd
    lw ra,0(sp)
    jalr x0,ra
<absadd>:
    addi sp,sp,-12
    sw ra,8(sp)
    sw s0,4(sp)
    sw a1,0(sp)
    jal ra,abs
    add a0,a0,s0
    lw a0,0(sp)
    jal ra, abs
    add a0,a0,s0

    lw s0, 4(sp) #
    lw ra ,8(sp)
    addi sp ,sp,12
    jalr x0,ra
=======
<mian>:
    addi sp,sp,-4
    sw ra,0(sp)
    addi a0,x0,-1
    addi a1,x0,2
    jal ra ,absadd
    lw ra,0(sp)
    jalr x0,ra
<absadd>:
    addi sp,sp,-12
    sw ra,8(sp)
    sw s0,4(sp)
    sw a1,0(sp)
    jal ra,abs
    add a0,a0,s0
    lw a0,0(sp)
    jal ra, abs
    add a0,a0,s0

    lw s0, 4(sp) #
    lw ra ,8(sp)
    addi sp ,sp,12
    jalr x0,ra
>>>>>>> a73a13b226717f7103f548730cc403470029c9fc
    
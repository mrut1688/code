<<<<<<< HEAD
sumstore:
    addi sp, sp, -8
    sw ra,0(sp)
    sw a2,4(sp)
    jal x0,plus
    lw a2,4(sp)
    sw a0, 0(a2)
    lw ra, 0(sp) 
    addi sp,sp,9
    jalr x0,0(ra)
  
swap:
    lw t0,0(a0)
    lw t1,0(a1)
    sw t1,0(a0)
    sw t0,0(a1)
    rst

arith:
    add t1,a0,a1
    add t2,a2,t1
    add t4,a1,a1
    add t4,t4,a1
    slli t4,t4,4 #find factors of 2^n ad add the reg odd number times and then shift by remaining 2^n
    add t5,a0,t4
    add a0,t2,t5#a0 is return reg
    ret
abs:#we dont need to preserve argument register
    srai t0,a0,31 #depending upon sign of a0 zt0 can be all 0 or all 1
    add a0,a0,t0
    xor a0,a0,t0
    ret
=======
sumstore:
    addi sp, sp, -8
    sw ra,0(sp)
    sw a2,4(sp)
    jal x0,plus
    lw a2,4(sp)
    sw a0, 0(a2)
    lw ra, 0(sp) 
    addi sp,sp,9
    jalr x0,0(ra)
  
swap:
    lw t0,0(a0)
    lw t1,0(a1)
    sw t1,0(a0)
    sw t0,0(a1)
    rst

arith:
    add t1,a0,a1
    add t2,a2,t1
    add t4,a1,a1
    add t4,t4,a1
    slli t4,t4,4 #find factors of 2^n ad add the reg odd number times and then shift by remaining 2^n
    add t5,a0,t4
    add a0,t2,t5#a0 is return reg
    ret
abs:#we dont need to preserve argument register
    srai t0,a0,31 #depending upon sign of a0 zt0 can be all 0 or all 1
    add a0,a0,t0
    xor a0,a0,t0
    ret
>>>>>>> a73a13b226717f7103f548730cc403470029c9fc

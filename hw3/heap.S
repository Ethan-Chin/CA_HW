# DO NOT REMOVE THIS LINE WHEN SUBMITTING
.import input.S

.text
.globl	main
main:
    la  s4, heap    #load heap
    lw  s5, len #load len
    li  s9, 32 # capacity


    la  s2, input   # load input
    lw  s3, input_len   # load input_len

    li  s1, 0   # int i = 0
    li  s6, -1  # load pop flag
    li  s7, -2  # load print_heap flag


main_loop:   # read one elem in input everytime
    bge s1, s3,  end    # if (i >= input_len) break;
    lw  s8, 0(s2)   # load input[i]

    bne s8, s6, endif_pop   # if (input[i] != -1) pass;
    jal pop # pop();
endif_pop:

    bne s8, s7, endif_print_heap  # if (input[i] != -2) pass;
    jal print_heap  # print_heap();
endif_print_heap:

    blt s8, x0, endif_insert # if (input[i] < 0) pass;
    mv  a1, s8  # load input[i] to the params list for insert(int elem)
    jal insert  # insert(int elem)
endif_insert:

    addi    s2, s2, 4   # i++
    addi    s1, s1, 1   # i++
    j main_loop  # repeatedly do the loop




swap:   # swap heap[a] and head[b]
    slli    t1, a1, 2  # load the offset of the first elem
    add t1, s4, t1  # locate the first elem
    lw  t3, 0(t1)   # load the value of the first elem

    slli    t2, a2, 2  # load the offset of the second elem
    add t2, s4, t2  # locate the second elem
    lw  t4, 0(t2)   # load the value of the second elem

    sw  t3, 0(t2)   # head[b] = the value of haed[a]
    sw  t4, 0(t1)   # head[a] = the value of head[b]
    jr  ra  # return




insert: # insert an elem to the heap, a1 storing the elem to be inserted. Notice to check overflow
    # save the save register to the stack
    addi    sp, sp, -28 # move the stack pointer
    sw  ra, 0(sp)   # save the return adress
    sw  s1, 4(sp)   # save s1
    sw  s2, 8(sp)   # save s2
    sw  s3, 12(sp)  # save s3
    sw  s6, 16(sp)  # save s6
    sw  s7, 20(sp)  # save s7
    sw  s8, 24(sp)  # save s8

    # you can't modify s4 (&heap), s5 (len) and s9 (capacity)

    blt s5, s9, endif_overflow #     if (len + 1 > 32) exit with -1;
    li  a0, 17  # ecall ID of exit
    li  a1, -1  # exit code
    ecall   # exit
endif_overflow:
    
    slli    t0, s5, 2 # load &heap[len]
    add t0, s4, t0  # load &heap[len]
    sw  a1, 0(t0)   # heap[len] = elem
    addi    s5, s5, 1   # len++

    addi    s1, s5, -1  # i = len - 1

insert_loop:
    li  t0, 1   # tmp = 1
    blt s1, t0,  end_insert_loop # for (i = len - 1; i > 0 ; )
    addi    t0, s1, -1  # tmp = i - 1
    srai    s2, t0, 1   # j = tmp / 2

    slli    t0, s1, 2   # load &heap[i]
    add t0, s4, t0  # load &heap[i]
    lw  t1, 0(t0)   # load heap[i]

    slli    t0, s2, 2   # load &heap[j]
    add t0, s4, t0  # load &heap[j]
    lw  t2, 0(t0)   # load heap[j]

    bge t1, t2, end_insert_loop # if (heap[i] < heap[j])
    
    mv  a1, s1  # call swap(i, j);
    mv  a2, s2  # call swap(i, j);
    jal swap    # call swap(i, j);
    mv  s1, s2  # i = j
    j   insert_loop # do the loop

end_insert_loop:

    # load the save register from the stack
    lw  ra, 0(sp)   # load the return adress
    lw  s1, 4(sp)   # load s1
    lw  s2, 8(sp)   # load s2
    lw  s3, 12(sp)  # load s3
    lw  s6, 16(sp)  # load s6
    lw  s7, 20(sp)  # load s7
    lw  s8, 24(sp)  # load s8
    addi    sp, sp, 28 # move the stack pointer
    
    jr  ra  # return to the main()




pop: # print the poped value. Notice to check underflow
    # save the save register to the stack
    # you can't modify s4 (&heap), s5 (len) and s9 (capacity)
    addi    sp, sp, -28 # move the stack pointer
    sw  ra, 0(sp)   # save the return adress
    sw  s1, 4(sp)   # save s1
    sw  s2, 8(sp)   # save s2
    sw  s3, 12(sp)  # save s3
    sw  s6, 16(sp)  # save s6
    sw  s7, 20(sp)  # save s7
    sw  s8, 24(sp)  # save s8

    addi    t0, s5, -1  # tmp = len - 1

    bge t0, x0, endif_underflow #     if (len - 1 < 0) exit with -1;
    li  a0, 17  # ecall ID of exit
    li  a1, -1  # exit code
    ecall   # exit
    endif_underflow:

    li  a1, 0  # swap(0, len - 1)
    mv  a2, t0  # swap(0, len - 1)
    jal swap    # swap(0, len - 1)

    addi    s5, s5, -1  # len--

    li  s1, 0   # i = 0

pop_loop:
    slli    s2, s1, 1   # m = 2 * i + 1
    addi    s2, s2, 1   # m = 2 * i + 1

    slli    s3, s1, 1   # n = 2 * i + 2
    addi    s3, s3, 2   # n = 2 * i + 2

    bge s2, s5, end_pop_loop    # if (m >= len) break;


    slli    t0, s1, 2   # load &heap[i]
    add t0, s4, t0  # load &heap[i]
    lw  s6, 0(t0)   # load heap[i]
    
    slli    t0, s2, 2   # load &heap[m]
    add t0, s4, t0  # load &heap[m]
    lw  s7, 0(t0)   # load heap[m]
    
    bge s3, s5, pop_loop_else_a   # if (n < len) ... a

    slli    t0, s3, 2   # load &heap[n]
    add t0, s4, t0  # load &heap[n]
    lw  s8, 0(t0)   # load heap[n]

    bge s8, s7, pop_loop_else_c # if (heap[n] < heap[m]) ... c

    
    bge s8, s6, end_pop_loop    # if (heap[n] < heap[i]) otherwise break end_pop_loop... d

    mv  a1, s1  # swap(i, n)
    mv  a2, s3  # swap(i, n)
    jal swap    # swap(i, n)
    mv  s1, s3  # i = n

    j   pop_loop # exit ... d (c) (a)

pop_loop_else_c:    # else ... c

    bge s7, s6, end_pop_loop    # if (heap[m] < heap[i]) otherwise break end_pop_loop... e

    mv  a1, s1  # swap(i, m)
    mv  a2, s2  # swap(i, m)
    jal swap    # swap(i, m)
    mv  s1, s2  # i = m

    j   pop_loop # exit ... e (c) (a)


pop_loop_else_a:    # else ... a

    bge s7, s6, end_pop_loop    # if (heap[m] < heap[i]) otherwise break end_pop_loop... b

    mv  a1, s1  # swap(i, m)
    mv  a2, s2  # swap(i, m)
    jal swap    # swap(i, m)
    mv  s1, s2  # i = m
    j   pop_loop # exit ... b (a)



end_pop_loop:
    

    # print the item popped
    slli    t0, s5, 2   # load &heap[len]
    add t0, s4, t0  # load &heap[len]
    lw  a1, 0(t0)   #load heap[len]
    li  a0, 1   # ecall ID of print_int
    ecall   # printf("%d", heap[i]);
    li  a1, '\n'    # load "\n"
    li  a0, 11   # ecall ID of print_char (break_line)
    ecall   # printf("\n");
    


    # load the save register from the stack
    lw  ra, 0(sp)   # load the return adress
    lw  s1, 4(sp)   # load s1
    lw  s2, 8(sp)   # load s2
    lw  s3, 12(sp)  # load s3
    lw  s6, 16(sp)  # load s6
    lw  s7, 20(sp)  # load s7
    lw  s8, 24(sp)  # load s8
    addi    sp, sp, 28 # move the stack pointer

    jr  ra  # return to the main()




print_heap:
    li  t0, 0   # i = 0
    addi    t5, s5, -1  # load len-1

print_heap_loop:
    bge t0, s5, end_print_heap_loop # if (i >= len) break;
    
    slli    t1, t0, 2   # load &heap[i]
    add t1, s4, t1  # load &heap[i]
    lw  a1, 0(t1)   # load heap[i]
    li  a0, 1   # ecall ID of print_int
    ecall   # printf("%d", heap[i]);

    bne t0, t5, endif_print_heap_loop    # if (i == len - 1)
    li  a1, '\n'    # load "\n"
    li  a0, 11   # ecall ID of print_char (break_line)
    ecall   # printf("\n");
    j end_print_heap_loop   # break;
endif_print_heap_loop:

    li  a1, ' '    # load " "
    li  a0, 11   # ecall ID of print_char (blank space)
    ecall   # printf(" ");
    
    addi    t0, t0, 1   # i++

    j print_heap_loop   # do the loop

end_print_heap_loop:

    jr  ra

end:
    li  a1, 0
    li  a0, 17
    ecall

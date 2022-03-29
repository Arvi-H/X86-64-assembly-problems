/*
    decode2:
        subq %rdx, %rsi     -> y -= z
        imulq %rsi, %rdi    -> x *= y
        movq %rsi, %rax     -> a = y
        salq $63, %rax      -> a =<< 63
        sarq $63, %rax      -> a =>> 63
        xor %rdi, %rax      -> a ^= x
        ret                 -> return a
*/

// x in %rdi, y in %rsi, z in %rdx, a in %rax

long decode2 (long x, long y, long z) {
    y -= z;
    x *= y;

    long a = y;

    a <<= 63;
    a >>= 63;
    a ^= x;
    
    return a;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

/*
    loop:
        movl   %esi, %ecx   -> ecx = n;    
        movl   $1, %edx     -> edx = 1;
        movl   $0, %eax     -> eax = 0;
        jmp    .L2          
    .L3:
        movq   %rdi, %r8    -> r8 = rdi
        andq   %rdx, %r8    -> r8 & rdx
        orq    %r8, %rax    -> r8 | result
        salq   %cl, %rdx    -> rdx << n
    .L2
        testq  %rdx, %rdx   -> rdx & rdx
        jne    .L3          -> != 0
        rep; ret            -> repeat return
*/

// x in %rdi, n in %esi, result in %rax, mask in %rdx

long loop(long x, long n) {
    long result = 0;
    long mask;
    
    for (mask = 1; mask != 0; mask <<= n) {    // DEBUG *****
        result |= x & mask;
    }

    return result;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 





 
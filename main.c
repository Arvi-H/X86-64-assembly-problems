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
        movl   %esi, %ecx   -> cl = n;    
        movl   $1, %edx     -> rdx = 1;
        movl   $0, %eax     -> rax = 0;
        jmp    .L2          
    .L3:
        movq   %rdi, %r8    -> r8 = x
        andq   %rdx, %r8    -> r8 & rdx
        orq    %r8, %rax    -> r8 | result
        salq   %cl, %rdx    -> rdx <<= n
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

const int M;

void transpose(long A[M][M]) {
    long i, j;
    for (i = 0; i < M; i++)
        for (j = 0; j < i; j++) {
            long t = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = t;
        }
}

// When compiled with optimization level -O1, GCC

/*
    .L6:
        movq   (%rdx), %rcx -> rcx = *rdx  
        movq   (%rax), %rsi -> rsi = *rax  
        movq   %rsi, (%rdx) -> *rdx = rsi = *rax // 
        movq   %rcx, (%rax) -> *rax = rcx 
        
        addq   $8, %rdx     -> rdx += 8 (ptr)
        addq   $120, %rax   -> rax += 120 (ptr)

        cmpq   %rdi, %rax   -> if (rax - rdi) != 0
        jne    .L6          ->  Recurse
*/
 
// Which register holds a pointer to array element A[i][j]? -> rdx

// Which register holds a pointer to array element A[j][i]? -> rax

// What is the value of M? -> M = 15 (120/8)
 
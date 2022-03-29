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





int main(void) {}
/*
    decode2:
        subq %rdx, %rsi     -> y -= z
        imulq %rsi, %rdi    -> x *= y
        movq %rsi, %rax     -> 
        salq $63, %rax
        sarq $63, %rax
        xor %rdi, %rax
        ret
*/

// x in %rdi, y in %rsi, z in %rdx

long decode2 (long x, long y, long z) {

}



int main(void) {}
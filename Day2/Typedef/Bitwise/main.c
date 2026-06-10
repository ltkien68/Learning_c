#include <stdio.h>
#include <stdint.h>

uint8_t a = 0;
uint8_t b = 0x08; // 0000 1000 ~ = 1111 0111; &= (1 << 3): &= 0000 1000 => 0000 0000


int main() {
    /*
        or bit --> set bit -> 1
        cái gì hoặc với 1 đều bằng 1
        0 | 1 = 1
        1 | 1 = 1
        1 | 0 = 1
        0 | 0 = 0
    */
    a |= (1 << 3);

    printf("%p\n", a);

    /* 
        and bit --> clear bit -> 0
        cái gì và với 0 đều bằng 0
        cái gì và với 1 đều bằng chính nó 
     */
    /*  
        not bit (~): 1 --> 0, 0 --> 1
    */
    b &= ~(1 << 3);
    printf("%p\n", b);

    return 0;
}
/*

Implement a function unsigned getMinRotL(unsigned x);
that returns the smallest value that can be obtained by repeatedly applying a left nibble-rotate to x.

A left nibble-rotate means:
take the most significant nibble (the top 4 bits) of the number,shift the whole number left by 4 bits,
and put that most significant nibble into the least significant nibble (the bottom 4 bits).

Print the result in hexadecimal. The number is on 32 bits.

*/

#include<stdio.h>
#include<stdint.h>

unsigned int get_nibble(uint32_t n, unsigned int pos)
{
    n = n & ( 0xF << (pos*4));     // or just:   return (n >> (4 * pos)) & 0xF
    n = n >> (pos*4);
    return n;
}

uint32_t rotate_nibble_once(uint32_t n)
{
    unsigned int nibble = get_nibble(n,7);
    n = n << 4;
    n = n | nibble;
    return n;
}

uint32_t getMinRotL(unsigned n)
{
    uint32_t min_n=n;
    for(unsigned int i=0;i<8;i++)
    {
        n = rotate_nibble_once(n);
        if(n<min_n) min_n=n;
    }

    return min_n;
}

int main()
{
    uint32_t n = 0xB1245FCA;
    printf("The nr %x has the minimum rotated nr %x.", n,getMinRotL(n));
    return 0;
}
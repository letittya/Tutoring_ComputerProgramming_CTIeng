/*  

Reverse bits of a given 32 bits signed integer.

Input: n = 43261596
Output: 964176192

43261596	-> 00000010100101000001111010011100
964176192	-> 00111001011110000010100101000000

*/

#include<stdio.h>
#include<stdint.h>

unsigned int reverseBits(unsigned int n) {
    unsigned int reverse=0, bit ;
    unsigned int size = sizeof(n)*8;
    for( unsigned int i=0; i< size; i++)
    {
        reverse = reverse << 1;
        bit = n & 1;
        n = n >> 1;
        reverse = reverse | bit;
    }
    return reverse;
}

int main()
{
    uint32_t n = 43261596;
    printf("The number %u with bits reversed is %u ",n,reverseBits(n));
    return 0;
}
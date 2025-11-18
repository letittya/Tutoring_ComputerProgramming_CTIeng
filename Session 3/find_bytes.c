/*

Implement a function which receives a uint16_t a number and another uint64_t b and checks whether all the bytes of a are to be 
found in b (in the same order but not necessarily adjacent).

i.e. a = 0xAB12 and b = 0xAB352DFF1278 is a pair of such numbers.

*/

#include<stdio.h>
#include<stdint.h>

unsigned int get_byte(uint64_t n, unsigned int pos)
{
    n = n & ((uint64_t)0xFF << (pos*8));
    n = n >> (pos*8);
    return n;
}

unsigned int is_found(uint16_t a, uint64_t b)
{
    unsigned int byte0_a = get_byte(a,0);
    unsigned int byte1_a = get_byte(a,1);

    unsigned int is_byte0=0, is_byte1=0;

    for(unsigned int i=0;i<8;i++)
    {
        unsigned int byte_b=get_byte(b,i);
        if(byte_b == byte0_a) is_byte0=1;
        else if ((byte_b == byte1_a) && (is_byte0==1)) is_byte1=1;   // we need to check if the appearance is in the same order 
    }
    if((is_byte0 == 1) &&  (is_byte1==1)) return 1;
    return 0;
}

int main()
{
    is_found(0xAB12, 0xAB352DFF1278) == 1? printf("All bytes are found in B.") : printf("Not all bytes are found in B.");
}
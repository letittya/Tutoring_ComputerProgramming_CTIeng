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
    unsigned int reverse=0, bit ;  // bit -> to store the current least significant bit
    unsigned int size = sizeof(n)*8;  // nr of bits 
    // process each bit one by one
    for( unsigned int i=0; i< size; i++)
    {
        reverse = reverse << 1;  // make space for the next bit (shift left)
        bit = n & 1;   // extract the least significant bit of n
        n = n >> 1;   // move to the next bit of n

        /*  Alternative method for extracting bit using GetBit:
        bit = n & (1<<i);
        if(bit!=0) bit=1;
        */

        reverse = reverse | bit;   // insert the extracted bit into the reversed number
    }
    return reverse;
}

int main()
{
    uint32_t n = 43261596;
    printf("The number %u with bits reversed is %u ",n,reverseBits(n));
    return 0;
}
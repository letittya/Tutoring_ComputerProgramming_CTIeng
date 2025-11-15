/*

Implement a function:   uint64_t injectNibbles(uint32_t n) which constructs a 64-bit unsigned integer based on the 
nibbles (4-bit groups) of the 32-bit number n.

The function must perform the following operations:
-Split the 32-bit number n into 8 nibbles, indexed from 0 (least significant nibble) to 7 (most significant nibble).
-For each nibble i, place its value into the lower nibble of byte i in the 64-bit result.
-Compute the XOR between each nibble i and the next nibble (i + 1), and store this result in the upper nibble of byte i.
-For the last nibble (index 7), XOR it with the first nibble (index 0) and store the result in the most significant nibble of 
the 64-bit result.
-Return the constructed 64-bit value.

Input:  n = 0x12488421  (decimal 306742305)
Output: 0x013264C808C46231

Hint: to display 64-bit hexadecimal numbers use %llx instead of %x

*/

#include<stdio.h>
#include<stdint.h>

unsigned int extract_nibble(uint32_t n, unsigned int pos)
{
    // n & (1<<pos) for 1 bit ----> for 1 nibble is  n & (0xF << (pos*4))
    n = n & (0xF << (pos*4));
    n = n >> (pos*4);
    return n;
}

unsigned int xor_nibble(unsigned int nibble1, unsigned int nibble2)
{
    return nibble1 ^ nibble2;
}

uint64_t injectNibbles(uint32_t n)
{
    unsigned int nibble1,nibble2,nibble3;
    uint64_t final_number=0;
    for (unsigned int i=0; i<8; i++)
    {
        // extract nibble i (positions: 0 to 7)
        nibble1=extract_nibble(n,i);

        // next nibble 
        if(i==7) nibble2=extract_nibble(n,0);
        else nibble2=extract_nibble(n,i+1);

        // XOR between current nibble and next nibble
        nibble3=xor_nibble(nibble1,nibble2);

         /*
            now place two nibbles inside byte i of the 64-bit number:

            byte i starts at bit position:   i * 8

            inside that byte:
                - lower nibble occupies bits 0–3
                - upper nibble occupies bits 4–7

            which means:
                nibble1 → shifted left by (i*8)
                nibble3 → shifted left by (i*8 + 4)
        */


        // if we dont cast the nibble to 64 bit, it reamins in 32 bit and shifting by i*8 could overflow or lose upper bits
        final_number = final_number | ((uint64_t)nibble1 << i*8);
        final_number = final_number | ((uint64_t)nibble3 << (i*8+4));

    }

    return final_number;
}

int main()
{
    uint32_t n=306742305;
    unsigned int pos=3;
    printf("The nr 0x%x has the nibble %d = 0x%x \n", n,pos,extract_nibble(n,pos));
    
    printf("The nr 0x%x has the inject nibble value 0x%llx", n,injectNibbles(n));
    return 0;
}
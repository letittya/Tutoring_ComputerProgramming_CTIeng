/*

Write a C program that reverses the nibbles of a 32-bit unsigned integer.
-First solve it using pure bitwise operations and loops
-Then solve it again using recursion + bitwise

A 32-bit number contains 8 nibbles, indexed from least significant (index 0) to most significant (index 7). Each nibble consists of 4 bits.

Example: 0xA86FC102   ----> 0x201CF68A

*/

#include <stdio.h>
#include <stdint.h>

uint32_t get_nibble(uint32_t n, unsigned int pos)
{
    n = n & (0xF<<(pos*4));
    n = n >> (pos*4);
    return n;
}

uint32_t reverse_nibbles(uint32_t n)
{
    uint32_t reverse = 0, nibble;
    for( unsigned int i=0; i<8; i++)
    {
        reverse = reverse << 4;
        nibble = get_nibble(n,i);
        reverse = reverse | nibble;
    }

    return reverse;
}

uint32_t reverse_nibbles_recursive_counter(uint32_t n, unsigned int counter)
{
    if (counter == 8)
        return 0;

    uint32_t nibble = n & 0xF;
    uint32_t reverse = reverse_nibbles_recursive_counter(n >> 4, counter + 1);

    unsigned int pos = (7-counter)*4;
    return reverse | (nibble<<pos);
    
}

uint32_t reverse_nibbles_recursive(uint32_t n)
{
    return reverse_nibbles_recursive_counter(n,0);
}

int main()
{
    uint32_t n=0xA86FC102;
    printf("The number 0x%x becomes 0x%x after reversing the nibbles.\n", n, reverse_nibbles(n));
    printf("The number 0x%x becomes 0x%x after reversing the nibbles recursively.", n, reverse_nibbles_recursive(n));
    return 0;
}
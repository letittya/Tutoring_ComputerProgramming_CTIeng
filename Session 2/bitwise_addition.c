/*
Bitwise addition Write a function that adds two unsigned numbers, bit by bit, using the elementary school 
algorithm with carry (from LSB to MSB).

Example:
   1 0 1 1 + (11)
   0 1 0 1   (5)
------------------
 1 0 0 0 0   (16)

*/

#include <stdio.h>
#include <stdint.h>

// get bit ( 0 or 1) at position pos
unsigned int get_bit(unsigned int n, unsigned int pos)
{
    n = n & (1<<pos);
    n = n>>pos;
    return n;
}

// sum of a + b + carry
unsigned int sum(unsigned int bit_a, unsigned int bit_b, unsigned int carry)
{
    return bit_a ^ bit_b ^ carry;
}

// determine if we have a carry or not
 // 2 possible cases: both bits are 1 or one bit is 1, and carry is 1
unsigned int carry_bit(unsigned int bit_a, unsigned int bit_b, unsigned int carry)
{
    if( (bit_a & bit_b) == 1) return 1; // bitwise for if(bit_a==1 && bit_b==1)
    if( (((bit_a ^ bit_b) == 1) & carry) == 1) return 1; // bit a or b has to be 1 --> XOR 
    return 0;

}


unsigned int add(unsigned int a, unsigned int b)
{
    unsigned int result = 0;
    unsigned int carry = 0;
    unsigned int size=sizeof(a)*8;

    for (unsigned int i = 0; i < size; i++)
    {
        unsigned int bit_a = get_bit(a, i);
        unsigned int bit_b = get_bit(b, i);

        unsigned int sum_bit = sum(bit_a, bit_b, carry);
        unsigned int new_carry = carry_bit(bit_a, bit_b, carry);

        // put sum bit into the correct position in the result
        result = result | (sum_bit << i);

        carry = new_carry; // move carry to next bit
    }

    return result;
}

int main(void)
{
    unsigned int x = 11;   
    unsigned int y = 5;   

    unsigned int result = add(x, y);

    printf("Bitwise addition of %u and %u = %u\n", x, y, result);
    printf("Normal addition:                %u\n", x + y);

    return 0;
}
/*
Write a recursive function:

    int count_even_bits(unsigned int n);

that returns the number of bits equal to 1 in the even positions of x
(positions 0, 2, 4, 6, …).

You MUST use:
   - bitwise operators
   - recursion (no loops)

Example:
  x = 0b10110110 (0xB6)  → 2 ones in even positions
*/

#include<stdio.h>

int count_even_bits(unsigned int n)
{
    if(n==0)
        return 0;

    unsigned int bit=n&1;
    if(bit==1)
        return 1+count_even_bits(n>>2);
    return count_even_bits(n>>2);
}

int count_odd_bits(unsigned int n)
{
    return count_even_bits(n>>1);
}

int main()
{
    unsigned int n=0xB6;
    printf("The number %x has %d bits equal set in even positions\n",n,count_even_bits(n));
     printf("The number %x has %d bits equal set in odd positions\n",n,count_odd_bits(n));
    return 0;
}
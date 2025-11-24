/*
Given an unsigned int x, we allow two operations:

  1) Flip the least significant bit (LSB):
        new_x = x ^ 1
  2) Append a new nibble (4 bits) equal to the XOR of all nibbles of x.

Write a recursive function:
        void generate(unsigned int x, int k);
which prints ALL values reachable from x using EXACTLY k operations.

  - If k == 0, print x 

Examples: x=0x5A3 k=2. 
Step 1: 0x5A2, 0x5A3C   ( because 5^A^3=C)
Step 2: 0x5A3, 0x5A2D, 0x5A3D, 0x5A3C0

*/

#include<stdio.h>
#include<stdint.h>

unsigned int XOR_nibble(unsigned int n){
    if (n==0)
        return 0;

    unsigned nibble = n&0xF;
    return nibble ^ XOR_nibble(n>>4);
}

void k_changes(unsigned int n, unsigned int k)
{
    if(k==0)
    {
        printf("%x ",n);
        return;
    }

    unsigned int flipped_bit = n^1;
    unsigned int add_nibble = (n<<4)|XOR_nibble(n);

    k_changes(flipped_bit,k-1);
    k_changes(add_nibble,k-1);
}

int main()
{
    k_changes(0x5A3,2);
    return 0;
}
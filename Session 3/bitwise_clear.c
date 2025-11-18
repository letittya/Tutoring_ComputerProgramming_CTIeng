/*

Implement a function that receives two uint64_t values and sets onto 0 all the bytes from the second argument 
which are found among the bytes of the first argument, regardless of the order, returning the result. 
Also, provide an adequate main() function.

*/

#include<stdint.h>
#include<stdio.h>

unsigned int get_byte(uint64_t n, unsigned int pos)
{
    n = n & ( (uint64_t) 0xFF << (pos*8));
    n = n >> (pos*8);
    return n;
}

uint64_t clear_byte(uint64_t n, unsigned int pos)
{
    n = n & ~((uint64_t)0xFF << (pos*8));   // we cast to uint64_t because 0xFF is by deafult -> int so it is on 32 bits
    return n;
}

uint64_t clear_function(uint64_t a, uint64_t b)
{
    for(unsigned int i=0; i<8; i++) // goes through the bytes of a
    {
        unsigned int byte_a=get_byte(a,i);
        for(unsigned int j=0; j<8; j++)
        {
            unsigned int byte_b=get_byte(b,j);
            if(byte_a == byte_b)
            {
                b = clear_byte(b,j);
            }

        }
    }

    return b;
}


int main()
{
    uint64_t a=0xABCD1289FA, b=0xAFFA8811AB11;
    printf("The nr %llx became %llx ", b, clear_function(a,b));
    return 0;
}
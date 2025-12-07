/*

Implement a function void packBytes(char t[], unsigned n, unsigned long v[], unsigned cap); 
which takes an array of bytes (t) together with the number of elements (n) and packs groups of four 
consecutive elements from t into elements of v, without exceeding the capacity (cap). Pad elements with 0x0 if needed.

I.e. 0xAB, 0x12, 0xCD, 0xDE, 0x3A -> 0xAB12CDDE, 0x3A000000

*/

#include <stdio.h>
#include<math.h>

unsigned long set_byte(unsigned long n, unsigned char val, unsigned pos) 
{
    return n | ((unsigned long)val << (pos * 8));
}

void packBytes(char t[], unsigned n, unsigned long v[], unsigned cap) 
{
    unsigned i_t = 0;
    unsigned i_v = 0;

    while (i_t < n && i_v < cap) 
    {
        unsigned long packed = 0;

        for (int j = 0; j < 4; j++) 
        {
            if (i_t < n) 
            {
                unsigned pos = 3 - j;
                packed = set_byte(packed, t[i_t], pos);
                i_t++;
            } else 
            {
                break;
            }
        }

        v[i_v] = packed;
        i_v++;
    }
}

int main() {
    char raw_bytes[] = {0xAB, 0x12, 0xCD, 0xDE, 0x3A};
    unsigned long packed_values[10];
    unsigned count = 5;
    unsigned capacity = 10;

    packBytes(raw_bytes, count, packed_values, capacity);

    int items_filled = (int)ceil((double)count / 4.0);

    for (int i = 0; i < items_filled; i++) 
    {
        printf("0x%lX\n", packed_values[i]);
    }

    return 0;
}
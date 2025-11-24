/*
Write a function that reads ONE hex digit and prints its 4-bit binary form.

Base16 ---> Base10 ---> Base2

Input: F 
Output: 1111 

Input: 9 
Output: 1001

*/

#include<stdio.h>
#include<ctype.h>

int hex_to_val(int c)
{
    if (isdigit(c))
        return c - '0';

    c = toupper(c);
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;

    return -1;  
}

void print_binary(int value)
{
    for (int i = 3; i >= 0; i--) 
    {
        int bit = (value >> i) & 1;
        putchar(bit + '0');
    }
}

void run()
{
    int c = getchar();
    int val = hex_to_val(c);

    if (val < 0)
        return;     

    print_binary(val);
}

int main()
{
    run();
    return 0;
}
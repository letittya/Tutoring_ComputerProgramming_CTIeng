/*

Write a C program that implements the following functions using bitwise operators:

1. Check if a number is even or odd
2. Turn ON a specific bit
3. Turn OFF a specific bit
4. Toggle a specific bit
5. Check if a specific bit is set

*/

#include<stdio.h>

int even_or_odd(int n)
{
    return n & 1;
}

int bit_on(int n, int pos)
{
    int nr = n | (1<<pos);
    return nr;
}

int bit_off(int n, int pos)
{
    int nr = n & ~(1<<pos);
    return nr;
}

int bit_toggle(int n, int pos)
{
    int nr = n ^ (1<<pos);
    return nr;
}

int is_bit_set(int n, int pos)
{
    int nr = n & (1<<pos);
    return nr;
}

int main()
{
    int n=10, pos=0, pos2=1;
    //1
    printf("The number %d is ",n);
    if(even_or_odd(n)) printf("odd \n");
    else printf("even \n");

    //2
    printf("The number %d became %d after turning on bit on position %d\n",n, bit_on(n,pos),pos);

    //3
    printf("The number %d became %d after turning off bit on position %d\n",n, bit_off(n,pos2),pos2);

    //4
    printf("The number %d became %d after toggling bit on position %d\n",n, bit_toggle(n,pos2),pos2);
    printf("The number %d became %d after toggling bit on position %d\n",n, bit_toggle(n,pos),pos);

    //5
    printf("The number %d has position %d ",n, pos2);
    if(is_bit_set(n,pos2)) printf("set \n");
    else printf("not set \n");
}
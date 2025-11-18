/*

Compute the following functions recursively:
1. Print numbers from 1 to n 
2. Sum of digits of a number
3. Check if a number is prime

*/

#include <stdio.h>
#include<math.h>

void print_nr (int n)
{
    if(n==0) return;
    print_nr(n-1);
    printf("%d ",n);
}

int sum_of_digits(int n)
{
    if(n==0) return 0;
    return (n%10) + sum_of_digits(n/10);
}

int is_prime(int n, int d)
{
    if (n < 2)  return 0;               // not prime
    if (d * d > n)  return 1;               // no divisor found -> prime
    if (n % d == 0)  return 0;               // divisor found -> not prime

    return is_prime(n, d + 1);
}


int main()
{
    int n=5,m=6;
    //1
    printf("1. Print nr from 1 to %d: \n ",n);
    print_nr(n);

    //2
    printf("\n2. Sum of digits of %d is %d \n",m,sum_of_digits(m));

    //3
    is_prime(n,2)==0? printf("3. The number %d is not prime\n",n) : printf("3. The number %d is prime\n",n);
    is_prime(m,2)==0? printf("3. The number %d is not prime\n",m) : printf("3. The number %d is prime\n",m);


    return 0;
}
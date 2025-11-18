/*

A number can be changed in two ways: either append the maximum digit, or append the sum of its digits, modulo 10 (as a least significant digit).
Write a function that takes a positive k and prints all numbers which can be obtained from an unsigned long number (also a parameter) 
by making exactly k changes.

Do the same problem but instead append either the number of digits modulo 10 or the number of odd digits. 

*/

#include<stdio.h>


//first version

unsigned int sum_digits(unsigned long int n)
{
    if(n==0) 
        return 0;

    return (n%10) + sum_digits(n/10);
}

unsigned int max_digit(unsigned long int n, unsigned int current_max)
{
    if( n == 0 ) 
        return current_max;

    unsigned int digit = n % 10;
    if(digit>current_max) return max_digit(n/10,digit);
    return max_digit(n/10, current_max);

}

void k_changes(unsigned long int n, unsigned int k)
{
    if(k==0)
    {
        printf(" %d ",n);
        return;
    }
    
    unsigned int max_d=max_digit(n,0);
    unsigned int sum=sum_digits(n)%10;

    k_changes(n*10+max_d,k-1);  // be careful to use k-1 not k-- or --k
    k_changes(n*10+sum,k-1);

}


// second version 

unsigned int nr_of_digits(unsigned long int n)
{
    if(n==0) return 0;
    return 1 + nr_of_digits(n/10);
}

unsigned int nr_of_odd_digits(unsigned long int n)
{
    if(n==0) return 0;
    if((n%10)%2 ==0) return nr_of_odd_digits(n/10);
    return 1 + nr_of_odd_digits(n/10);
}

void k_changes_2(unsigned long int n, unsigned int k)
{
    if(k==0)
    {
        printf(" %d ",n);
        return;
    }
    
    unsigned int digits=nr_of_digits(n);
    unsigned int odd=nr_of_odd_digits(n);
    k_changes_2(n*10+digits,k-1);
    k_changes_2(n*10+odd,k-1);

}

int main()
{
    k_changes(123,3);
    printf("\n");
    k_changes_2(123,3);
    return 0;
}
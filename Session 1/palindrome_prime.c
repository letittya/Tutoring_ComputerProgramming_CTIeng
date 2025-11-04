/*

Given an integer n, return the biggest prime palindrome smaller than or equal to n.

Input: n = 6
Output: 5

Input: n = 105
Output: 101

*/
#include <math.h>
#include <stdio.h>

int prime(unsigned n)
{
   if ( n<2) return 0;
   for ( int i=2; i<= sqrt(n) ; i++)
   {
    if (n % i ==0) return 0;
   }  
   
   return 1;
}

int palindrome ( int nr)
{
    int nr2=nr;
    int reverse=0;

    while (nr!=0)
    {
        reverse = reverse *10 + nr%10;
        nr=nr /10;
    }

    if(nr2==reverse) return 1;
    return 0;
}

int primePalindrome(int n) {
    
    for ( int i = n; i>=0; i--)
    {
        if ( palindrome(i) == 1 && prime(i) == 1) return i;
    }

    return 0;
}


int main()
{
   printf("%d ", primePalindrome(6));

    return 0;
}
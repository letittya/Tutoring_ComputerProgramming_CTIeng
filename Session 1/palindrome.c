/*

Given an unsigned integer x, return true if x is a palindrome, and false otherwise.

Example 1:

Input: x = 121
Output: true
Explanation: 121 reads as 121 from left to right and from right to left.

*/

#include <stdbool.h>
#include <stdio.h>

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

int main()
{
    printf(palindrome(1221) ? "true" : "false"); // print using conditional operator 
    return 0;
}
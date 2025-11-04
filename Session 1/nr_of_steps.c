/*
Given an integer num, return the number of steps to reduce it to zero.

In one step, if the current number is even, you have to divide it by 2, otherwise, you have to subtract 1 from it.

Input: num = 8
Output: 4
Explanation: 
Step 1) 8 is even; divide by 2 and obtain 4. 
Step 2) 4 is even; divide by 2 and obtain 2. 
Step 3) 2 is even; divide by 2 and obtain 1. 
Step 4) 1 is odd; subtract 1 and obtain 0.

*/

#include <stdio.h>

int number_to_0(int nr)
{
    unsigned int steps=0;
    while ( nr != 0)
    {
        steps++;
        if( nr % 2 == 0) // check if it's even
        {
            nr=nr/2;
        }
        else 
        {
            nr--;
        }
    }

    return steps;
}

int main()
{

    printf("Number of steps is %d. \n", number_to_0(9));
    return 0;
}
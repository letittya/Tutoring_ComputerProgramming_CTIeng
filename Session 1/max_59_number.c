/*

You are given a positive unsigned integer num consisting only of digits 5 and 9.

Return the maximum number you can get by changing at most one digit (5 becomes 9, and 9 becomes 5).

Input: num = 9995
Output: 9999
Explanation: Changing the last digit 5 to 9 results in the maximum number.

*/

#include <stdio.h>

int maximum59Number (int num) {
    int nr=num, pos=1, best =0;

    while (num!=0)
    {

        if( num % 10 == 5)
        {
            best=pos;
        }

        pos=pos*10;
        num=num/10;
    }


    if( best == 0) return nr;
    return ( nr + best*4);  // because 9-5=4
  
}

int main()
{
    printf ("%d ", maximum59Number(99999));
    return 0;
}
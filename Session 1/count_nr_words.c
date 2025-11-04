/*

Implement a function that reads characters from standard input until EOF and prints, for each line, the number of words and the number of positive numbers encountered.

A word is defined as a sequence of letters (a–z, A–Z), separated by at least 1 space.
A positive number is defined as a sequence of digits, separated by at least 1 space.

The first and last words or numbers in a line might not have leading or trailing separators.

Test the function with relevant data. (You only have to submit the source file, not the test files.)

*/

#include<stdio.h>
#include<ctype.h>

void count()
{
    int c, state=0;
    int words=0, nr=0;

    while( (c=getchar()) != EOF)
    {
        
        if( state == 0) // state we start from
        {
            if (isdigit(c))
            {
                state = 2;
            }
            else if(isalpha(c))
            {
                state = 1;
            }
        }
        else if (state == 1) // state that checks if it's a word
        {
            if (isalpha(c)) state = 1;
            else if(isspace(c))
            {
                words++;
                state =0;
            }
            else state =3;
        }

        else if (state == 2) // state that checks if it's a number
        {
            if (isdigit(c)) state = 2;
            else if(isspace(c))
            {
                nr++;
                state =0;
            }
            else state =3;  
        }

        else if (state ==3) // garbage state, the only way of getting out is to encounter a space 
        {
            if(isspace(c))
            {
                state = 0;
            }
        }

        if ( c== '\n') // print the counters when we get to a newline
        {
            printf("Nr of words %d and number of numbers %d \n", words,nr);
            words=0;
            nr=0;
            state = 0; 
        }

    }

    // make sure the last line also gets taken into account, even if we do not explicitly have a \n
    if (state==1) words++;
    else if (state ==2) nr++;
    printf(" \n Nr of words %d and number of numbers %d \n", words,nr);
}

int main()
{

    count();
    return 0;
}
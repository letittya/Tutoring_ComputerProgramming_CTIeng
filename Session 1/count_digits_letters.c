/*

Write a C program that reads characters from the keyboard one by one, until the user presses Enter (newline character '\n').
Your program should count and display how many of the entered characters are:
-letters (both uppercase and lowercase)
-digits (0–9)
-other characters (punctuation marks, spaces, symbols, etc.)

*/

#include <stdio.h>
#include <ctype.h>

void count ()
{
    unsigned int letters=0, digits=0, others=0, c;
    while ( (c = getchar()) != '\n')
    {
        if ( isdigit(c)) digits++; // another version could be: if(c>='0' && c<='9')
        else if ( isalpha(c)) letters++; // another version could be: if((c>='a' && c<='z') || (c>='A' && c<='Z'))
        else others ++;
    }

    printf ("Nr of letters %d, nr of digits %d, and the rest %d \n", letters, digits, others);
}

int main()
{
    count();
    return 0;
}
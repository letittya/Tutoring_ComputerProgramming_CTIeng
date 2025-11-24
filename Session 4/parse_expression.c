/*

An expression is either a single digit or has the form (expr1, expr2). The value of a single digit is the digit itself. 
The value of an expression of the form (expr1, expr2) is (value(expr1) + value(expr2)) % 10. 

Write a function that reads such an expression from standard input character by character and returns its value, 
or returns -1 if the input is not a valid expression. 

For example, the expression (7,(8,4)) has the value 9 because (8 + 4) % 10 = 2 and (7 + 2) % 10 = 9.

*/

#include<stdio.h>
#include<ctype.h>

int parse()
{
    int c=getchar();

    if(c==EOF) return -1;

    if( isdigit(c))
    {
        return c - '0';
    }

    else if ( c=='(')
    {
        int left = parse();
        if(left==-1)
            return -1;

        c=getchar();
        if( c!=',')
            return -1;

        int right = parse();
        if(right==-1)
            return -1;

        c=getchar();
        if( c!=')')
            return -1;

        return (left + right) % 10;
    }

    return -1;
}

int main()
{
    int value=parse();
    
    int c=getchar();
     if (c != EOF) {
            printf("The value of the expression is -1");
        } else {
            printf("The value of the expression is %d", value);
        }
    return 0;
}
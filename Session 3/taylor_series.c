/*

Write functions that compute the Taylor series for exponential and sin for a given value of x. 
Stop when the current term becomes smaller than a given value (e.g. 1e-6).

*/

#include <stdio.h>
#include <math.h>

unsigned long long int factorial(unsigned long int n)
{
    if(n<=1)
        return 1;
    
    return n * factorial(n-1);
}

double taylor_exp(double x, unsigned long int n)
{
    double term = pow(x,n)/ factorial(n);

    if(fabs(term) < 1e-6)
        return term;

    return term + taylor_exp(x,n+1);
}

double taylor_exp_wrapper(double x)
{
    return taylor_exp(x,0);
}

int main()
{
    double x=3.25;
    printf("The exponention of %f is %f\n and the actual value is %f",x,taylor_exp_wrapper(x),exp(x));

}


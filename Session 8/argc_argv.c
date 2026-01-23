#include<stdio.h>

int main(int argc, char *argv[])
{
    printf("Nr of arguments is %d\n",argc);
    for(int i=0; i<argc; i++)
    {
        printf(" Argument #%d is %s\n",i,argv[i]);
    }
    return 0;
}
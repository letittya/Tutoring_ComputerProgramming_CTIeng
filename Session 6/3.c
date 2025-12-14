#include <stdio.h>

int main() {
    int x = 3;
    int* p = &x;
    *p = 5;
    int** q = &p;
    int*** r = &q;

    printf("%d %d %d", *p, **q, ***r);
    
    return 0;
}













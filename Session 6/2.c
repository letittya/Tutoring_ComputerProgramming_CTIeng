#include <stdio.h>

int main() {
    int a = 10;
    int *p = &a;
    
    *p = 5;
    
    printf("%d\n", *p);
    
    return 0;
}




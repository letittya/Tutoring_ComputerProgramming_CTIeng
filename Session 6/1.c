#include <stdio.h>

int main() {
    char x = 10;
    char *p = &x;
    
    printf("%d \n", sizeof(*p));
    
    return 0;
}



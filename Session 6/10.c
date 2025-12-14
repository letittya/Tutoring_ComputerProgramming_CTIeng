#include <stdio.h>

int main() {
    int x[] = {1, 2};

    int *p = x;
    int  **pp = &p;
    int ***ppp = &pp;

    printf("%d\n", (*((**&*ppp) + 1)));

    return 0;
}



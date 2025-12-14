#include<stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int *p = arr;

    printf("%d ", *(p + 2)); 
    
    p++; 
    printf("%d\n", *(p + 3)); 
    
    return 0;
}



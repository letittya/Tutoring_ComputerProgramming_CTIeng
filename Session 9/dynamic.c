#include <stdio.h>
#include <stdlib.h> // for dynamic allocation & qsort

int compare_ints(const void *a, const void *b) {
    int *int_a = (int *)a; // cast void* to int* and dereference
    int *int_b = (int *)b;
    if(*int_a < *int_b) return -1;
    else if (*int_a > *int_b)return 1;
    return 0;
}

int main() {
    // 1. malloc example
    // allocates space for 3 integers. content is garbage
    printf("malloc (3 ints)\n");
    int *arr_m = malloc(3 * sizeof(int));
    
    if (arr_m == NULL) return 1; // always check for null!

    // manually assign values
    arr_m[0] = 5;
    arr_m[1] = 45;
    arr_m[2] = 2;

    for (int i = 0; i < 3; i++) {
        printf("arr_m[%d] = %d\n", i, arr_m[i]);
    }

    // 2. calloc example
    // allocates space for 3 ints AND initializes them to 0.
    printf("\ncalloc (3 ints)\n");
    int *arr_c = calloc(3, sizeof(int));
    
    if (arr_c == NULL) return 1;

    // printing immediately to prove they are 0
    for (int i = 0; i < 3; i++) {
        printf("arr_c[%d] = %d\n", i, arr_c[i]);
    }

    // 3. realloc example
    // resize 'arr_m' from 3 integers to 5 integers.
    printf("\nrealloc (resize arr_m to 5 ints)\n");
    
    // important: use a temporary pointer in case realloc fails!
    int *temp = realloc(arr_m, 5 * sizeof(int));
    
    if (temp == NULL) {
        printf("realloc failed!\n");
        free(arr_m); // original memory is still valid, so free it
        return 1;
    }
    arr_m = temp; // update the main pointer

    // assign values to the new slots
    arr_m[3] = 13;
    arr_m[4] = 11;

    for (int i = 0; i < 5; i++) {
        printf("arr_m[%d] = %d\n", i, arr_m[i]);
    }

    // 4. qsort example
    printf("\nqsort (sorting arr_m)\n");
    
    // arguments: array, number of elements, size of one element, compare function
    qsort(arr_m, 5, sizeof(int), compare_ints);

    for (int i = 0; i < 5; i++) {
        printf("arr_m[%d] = %d\n", i, arr_m[i]);
    }

    // 5. cleanup
    free(arr_m);
    free(arr_c);

    return 0;
}
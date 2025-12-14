#include <stdio.h>
#include <stdint.h>

int main() {
    uint16_t var_1 = 1;
    uint32_t var_2 = 1;

    uint16_t *pv1 = &var_1;
    uint32_t *pv2 = &var_2;

    printf("%ld ", sizeof(var_1));
    printf("%ld \n", sizeof(var_2));

    printf("%ld ", sizeof(pv1));
    printf("%ld\n", sizeof(pv2));

    return 0;
}





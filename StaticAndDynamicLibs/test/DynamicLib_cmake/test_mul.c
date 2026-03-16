#include <stdio.h>
#include "include/mul.h"

int main() {
    int a = 10, b = 5;
    printf("%d * %d = %d\n", a, b, mul(a, b));
    return 0;
}
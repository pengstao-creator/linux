#include <stdio.h>
#include "include/sub.h"

int main() {
    int a = 10, b = 5;
    printf("%d - %d = %d\n", a, b, sub(a, b));
    return 0;
}
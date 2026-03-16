#include <stdio.h>
#include "include/sub.h"
#include "include/div.h"

int main() {
    int a = 10, b = 5;
    printf("%d - %d = %d\n", a, b, sub(a, b));
    printf("%d / %d = %d\n", a, b, divide(a, b));
    return 0;
}
#include <stdio.h>
#include "../src/ds/array.h"

int main() {
    Array_int array = Array_new_int();
    int n;

    printf("Enter a number n:\n");
    scanf("%d", &n);

    printf("Enter n numbers:");
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        Array_append_int(x, array);
    }

    Array_print_int("%d", array);

    Array_free(&array);
}
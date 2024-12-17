#include <stdio.h>
#include "../src/ds/list.h"

int main() {
    List_int list = List_new_int();
    int n;

    printf("Enter a number n:\n");
    scanf("%d", &n);

    printf("Enter n numbers:");
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        List_append_int(x, list);
    }

    List_print_int("%d", list);
}
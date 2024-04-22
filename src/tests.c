#include <stdio.h>

#include "ds/list.h"

int main() {
    list *l = list_int_new();
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        list_append_int(l, x);
    }

    printf(": ");

    LIST_FOREACH_INT(x, l) {
        printf("%d ", *x);
    }
    printf("\n");

    list_destroy(l);

    return 0;
}
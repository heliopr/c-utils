#include <stdio.h>

#include "ds/list.h"

int main() {
    list *l = list_char_new();

    int a = 10;
    printf("%d\n", list_append_char(l, a));
    a = 12;
    printf("%d\n", list_append_char(l, a));
    a = 11;
    printf("%d\n", list_append_char(l, a));
    a = -5;
    printf("%d\n", list_append_char(l, a));
    a = -6;
    printf("%d\n", list_prepend_char(l, a));

    a = 37;
    printf("%d\n", list_insert_char(l, a, 3));
    printf("%d\n", list_insert_char(l, a, 10));
    printf("%d\n", list_insert_char(l, a, -1));

    printf("%d\n", list_remove(l, 1));

    printf("LALA %d\n", list_get_char(l, 3));

    //printf("%d %d %d\n", l->size, l->allocated, l->element_size);
    
    LIST_FOREACH_CHAR(i, l) {
        printf("%d ", *i);
    }
    printf("\n");

    list_destroy(l);

    return 0;
}
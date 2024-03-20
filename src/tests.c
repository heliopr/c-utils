#include <stdio.h>

#include "list.h"

int main() {
    list_t *l = list_new(sizeof(int));

    int a = 10;
    printf("%d\n", list_add(l, &a));
    a = 12;
    printf("%d\n", list_add(l, &a));
    a = 11;
    printf("%d\n", list_add(l, &a));
    a = -5;
    printf("%d\n", list_add(l, &a));
    a = -6;
    printf("%d\n", list_add(l, &a));

    a = 37;
    printf("%d\n", list_insert(l, &a, 3));

    printf("%d\n", list_remove(l, 1));

    //printf("%d %d %d\n", l->size, l->allocated, l->element_size);
    
    for (int i = 0; i < l->size; i++) {
        printf("%d ", ((int*)l->p)[i]);
    }
    printf("\n");

    return 0;
}
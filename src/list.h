#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct list
{
    void *p;
    size_t size, allocated, element_size;
} list_t;


list_t *list_new(size_t element_size) {
    list_t *l = (list_t*)malloc(sizeof(list_t));
    l->size = 0;
    l->allocated = 1;
    l->element_size = element_size;
    l->p = malloc(element_size);

    return l;
}

bool list_realloc(list_t *l) {
    if (l == NULL) return false;

    l->p = realloc(l->p, l->allocated*l->element_size);

    if (l->p == NULL) return false;
    return true;
}

bool list_insert(list_t *l, const void *e, int pos) {
    if (l == NULL || e == NULL || pos < 0 || pos > l->size) return false;

    if (l->size == l->allocated) {
        l->allocated *= 2;
        if (!list_realloc(l)) return false;
    }

    memcpy(l->p+((pos+1)*l->element_size), l->p+(pos*l->element_size), l->element_size*(l->size-pos));
    memcpy(l->p+(pos*l->element_size), e, l->element_size);
    l->size++;
    return true;
}

bool list_add(list_t *l, const void *e) {
    return list_insert(l, e, l->size);
}

bool list_remove(list_t *l, int pos) {
    if (l == NULL || pos < 0 || pos >= l->size) return false;

    memcpy(l->p+(pos*l->element_size), l->p+((pos+1)*l->element_size), l->element_size*(l->size-pos-1));
    l->size--;

    if (l->size == l->allocated/2) {
        l->allocated /= 2;
        if (!list_realloc(l)) return false;
    }

    return true;
}

void *list_get(list_t *l, int pos) {
    if (l == NULL || l->p == NULL) return NULL;
    return l->p+(pos*l->element_size);
}

#endif
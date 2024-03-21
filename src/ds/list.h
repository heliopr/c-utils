#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#define LIST_FOREACH(e, l) for(void *e = l->p; (e-l->p) < (l->size*l->element_size); e = e + l->element_size)
#define LIST_FOREACH_CHAR(e, l) for(char *e = l->p; (e-((char*)l->p)) < l->size; e++)
#define LIST_FOREACH_INT(e, l) for(int *e = l->p; (e-((int*)l->p)) < l->size; e++)
#define LIST_FOREACH_FLOAT(e, l) for(float *e = l->p; (e-((float*)l->p)) < l->size; e++)
#define LIST_FOREACH_DOUBLE(e, l) for(double *e = l->p; (e-((double*)l->p)) < l->size; e++)
#define LIST_FOREACH_UCHAR(e, l) for(unsigned char *e = l->p; (e-((unsigned char*)l->p)) < l->size; e++)
#define LIST_FOREACH_UINT(e, l) for(unsigned int *e = l->p; (e-((unsigned int*)l->p)) < l->size; e++)
#define LIST_FOREACH_UFLOAT(e, l) for(unsigned float *e = l->p; (e-((unsigned float*)l->p)) < l->size; e++)
#define LIST_FOREACH_UDOUBLE(e, l) for(unsigned double *e = l->p; (e-((unsigned double*)l->p)) < l->size; e++)


typedef struct list
{
    void *p;
    size_t size, allocated, element_size;
} list;


list *list_new(size_t element_size) {
    list *l = (list*)malloc(sizeof(list));
    if (l == NULL) return NULL;

    l->size = 0;
    l->allocated = 1;
    l->element_size = element_size;
    l->p = malloc(element_size);

    if (l->p == NULL) {
        free(l);
        return NULL;
    }

    return l;
}

bool list_realloc(list *l) {
    if (l == NULL) return false;

    l->p = realloc(l->p, l->allocated*l->element_size);

    if (l->p == NULL) return false;
    return true;
}

bool list_insert(list *l, const void *e, size_t pos) {
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

bool list_append(list *l, const void *e) {
    return list_insert(l, e, l->size);
}

bool list_prepend(list *l, const void *e) {
    return list_insert(l, e, 0);
}

bool list_remove(list *l, size_t pos) {
    if (l == NULL || pos < 0 || pos >= l->size) return false;

    memcpy(l->p+(pos*l->element_size), l->p+((pos+1)*l->element_size), l->element_size*(l->size-pos-1));
    l->size--;

    if (l->size == l->allocated/2) {
        l->allocated /= 2;
        if (!list_realloc(l)) return false;
    }

    return true;
}

void *list_get(list *l, size_t pos) {
    if (l == NULL || l->p == NULL) return NULL;
    return l->p+(pos*l->element_size);
}

void list_destroy(list *l) {
    if (l == NULL) return;

    free(l->p);
    free(l);
}



list *list_int_new() { return list_new(sizeof(int)); }

bool list_insert_int(list *l, int i, size_t pos) { return list_insert(l, &i, pos); }

bool list_append_int(list *l, int i) { return list_append(l, &i); }

bool list_prepend_int(list *l, int i) { return list_prepend(l, &i); }

int list_get_int(list *l, size_t pos) { return *((int*)list_get(l, pos)); }



list *list_float_new() { return list_new(sizeof(float)); }

bool list_insert_float(list *l, float i, size_t pos) { return list_insert(l, &i, pos); }

bool list_append_float(list *l, float i) { return list_append(l, &i); }

bool list_prepend_float(list *l, float i) { return list_prepend(l, &i); }

float list_get_float(list *l, size_t pos) { return *((float*)list_get(l, pos)); }



list *list_double_new() { return list_new(sizeof(double)); }

bool list_insert_double(list *l, double i, size_t pos) { return list_insert(l, &i, pos); }

bool list_append_double(list *l, double i) { return list_append(l, &i); }

bool list_prepend_double(list *l, double i) { return list_prepend(l, &i); }

double list_get_double(list *l, size_t pos) { return *((double*)list_get(l, pos)); }



list *list_char_new() { return list_new(sizeof(char)); }

bool list_insert_char(list *l, char i, size_t pos) { return list_insert(l, &i, pos); }

bool list_append_char(list *l, char i) { return list_append(l, &i); }

bool list_prepend_char(list *l, char i) { return list_prepend(l, &i); }

char list_get_char(list *l, size_t pos) { return *((char*)list_get(l, pos)); }

#endif
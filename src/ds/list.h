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

bool list_set(list *l, const void *e, size_t pos) {
    if (l == NULL || e == NULL || pos < 0 || pos > l->size) return false;

    memcpy(l->p+(pos*l->element_size), e, l->element_size);
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

void _list_mergesubs(list *l, size_t p, size_t q, size_t r, bool (*cmp)(void*, void*)) {
    size_t e_size = l->element_size;
    size_t n1 = q-p+1;
    size_t n2 = r-q;

    void *L = malloc(n1 * e_size);
    void *M = malloc(n2 * e_size);

    for (size_t i = 0; i < n1; i++)
        memcpy(L+(i*e_size), list_get(l, p + i), e_size);
    for (size_t j = 0; j < n2; j++)
        memcpy(M+(j*e_size), list_get(l, q+1+j), e_size);

    size_t i, j, k;
    i = 0;
    j = 0;
    k = p;

    while (i < n1 && j < n2) {
        if (cmp(L+(i*e_size), M+(j*e_size))) {
            list_set(l, L+(i*e_size), k);
            i++;
        } else {
            list_set(l, M+(j*e_size), k);
            j++;
        }
        k++;
    }

    while (i < n1) {
        list_set(l, L+(i*e_size), k);
        i++;
        k++;
    }

    while (j < n2) {
        list_set(l, M+(j*e_size), k);
        j++;
        k++;
    }

    free(L);
    free(M);
}

void _list_mergesort(list *l, size_t i, size_t j, bool (cmp)(void*, void*)) {
    if (i < j) {
        size_t m = i + (j - i) / 2;

        _list_mergesort(l, i, m, cmp);
        _list_mergesort(l, m + 1, j, cmp);
        _list_mergesubs(l, i, m, j, cmp);
    }
}

void list_sort(list *l, bool (cmp)(void*, void*)) {
    _list_mergesort(l, 0, l->size-1, cmp);
}

void list_destroy(list *l) {
    if (l == NULL) return;

    free(l->p);
    free(l);
}



list *list_int_new() { return list_new(sizeof(int)); }
bool list_insert_int(list *l, int e, size_t pos) { return list_insert(l, &e, pos); }
bool list_set_int(list *l, int e, size_t pos) { return list_set(l, &e, pos); }
bool list_append_int(list *l, int e) { return list_append(l, &e); }
bool list_prepend_int(list *l, int e) { return list_prepend(l, &e); }
int list_get_int(list *l, size_t pos) { return *((int*)list_get(l, pos)); }
bool list_cmp_int(void *x, void *y) { return *((int*)x) <= *((int*)y); }
bool list_revcmp_int(void *x, void *y) { return *((int*)x) >= *((int*)y); }



list *list_float_new() { return list_new(sizeof(float)); }
bool list_insert_float(list *l, float e, size_t pos) { return list_insert(l, &e, pos); }
bool list_set_float(list *l, float e, size_t pos) { return list_set(l, &e, pos); }
bool list_append_float(list *l, float e) { return list_append(l, &e); }
bool list_prepend_float(list *l, float e) { return list_prepend(l, &e); }
float list_get_float(list *l, size_t pos) { return *((float*)list_get(l, pos)); }
bool list_cmp_float(void *x, void *y) { return *((float*)x) <= *((float*)y); }
bool list_revcmp_float(void *x, void *y) { return *((float*)x) >= *((float*)y); }


list *list_double_new() { return list_new(sizeof(double)); }
bool list_insert_double(list *l, double e, size_t pos) { return list_insert(l, &e, pos); }
bool list_set_double(list *l, double e, size_t pos) { return list_set(l, &e, pos); }
bool list_append_double(list *l, double e) { return list_append(l, &e); }
bool list_prepend_double(list *l, double e) { return list_prepend(l, &e); }
double list_get_double(list *l, size_t pos) { return *((double*)list_get(l, pos)); }
bool list_cmp_double(void *x, void *y) { return *((double*)x) <= *((double*)y); }
bool list_revcmp_double(void *x, void *y) { return *((double*)x) >= *((double*)y); }


list *list_char_new() { return list_new(sizeof(char)); }
bool list_insert_char(list *l, char e, size_t pos) { return list_insert(l, &e, pos); }
bool list_set_char(list *l, char e, size_t pos) { return list_set(l, &e, pos); }
bool list_append_char(list *l, char e) { return list_append(l, &e); }
bool list_prepend_char(list *l, char e) { return list_prepend(l, &e); }
char list_get_char(list *l, size_t pos) { return *((char*)list_get(l, pos)); }
bool list_cmp_char(void *x, void *y) { return *((char*)x) <= *((char*)y); }
bool list_revcmp_char(void *x, void *y) { return *((char*)x) >= *((char*)y); }

#endif
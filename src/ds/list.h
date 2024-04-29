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

list *list_new(size_t element_size);
bool list_realloc(list *l);
bool list_insert(list *l, const void *e, size_t pos);
bool list_set(list *l, const void *e, size_t pos);
bool list_append(list *l, const void *e);
bool list_prepend(list *l, const void *e);
bool list_remove(list *l, size_t pos);
void *list_get(list *l, size_t pos);
void _list_mergesubs(list *l, size_t p, size_t q, size_t r, bool (*cmp)(void*, void*));
void _list_mergesort(list *l, size_t i, size_t j, bool (cmp)(void*, void*));
void list_sort(list *l, bool (cmp)(void*, void*));
void list_destroy(list *l);



list *list_int_new();
bool list_insert_int(list *l, int e, size_t pos);
bool list_set_int(list *l, int e, size_t pos);
bool list_append_int(list *l, int e);
bool list_prepend_int(list *l, int e);
int list_get_int(list *l, size_t pos);
bool list_cmp_int(void *x, void *y);
bool list_revcmp_int(void *x, void *y);


list *list_float_new();
bool list_insert_float(list *l, float e, size_t pos);
bool list_set_float(list *l, float e, size_t pos);
bool list_append_float(list *l, float e);
bool list_prepend_float(list *l, float e);
float list_get_float(list *l, size_t pos);
bool list_cmp_float(void *x, void *y);
bool list_revcmp_float(void *x, void *y);


list *list_double_new();
bool list_insert_double(list *l, double e, size_t pos);
bool list_set_double(list *l, double e, size_t pos);
bool list_append_double(list *l, double e);
bool list_prepend_double(list *l, double e);
double list_get_double(list *l, size_t pos);
bool list_cmp_double(void *x, void *y);
bool list_revcmp_double(void *x, void *y);


list *list_char_new();
bool list_insert_char(list *l, char e, size_t pos);
bool list_set_char(list *l, char e, size_t pos);
bool list_append_char(list *l, char e);
bool list_prepend_char(list *l, char e);
char list_get_char(list *l, size_t pos);
bool list_cmp_char(void *x, void *y);
bool list_revcmp_char(void *x, void *y);

#endif
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#ifndef DS_LIST_H
#define DS_LIST_H

#define LIST_IMPL(type) \
    typedef List List_##type;\
    \
    List_##type List_new_##type() {\
        return List_new(sizeof(type));\
    }\
    \
    type List_get_##type(size_t index, List_##type list) {\
        if (list == NULL) return 0;\
        if (index >= list->size) return 0;\
        return ((type*)list->p)[index];\
    }\
    \
    void List_append_##type(type value, List_##type list) {\
        if (list == NULL) return;\
        _List_incrementSize(list);\
        ((type*)list->p)[list->size-1] = value;\
    }

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
typedef long long longlong;

typedef struct List {
    size_t size;
    size_t allocated;
    size_t elementSize;
    void *p;
} *List;


static void _List_doubleSize(List list);
static void _List_incrementSize(List list);


List List_new(size_t elementSize);
void List_free(List list);
void List_append(const void *value, List list);
void List_appendPtr(const void *ptr, List list);
void *List_get(size_t index, List list);


List List_new(size_t elementSize) {
    void *p = malloc(elementSize * 1);
    if (p == NULL) return NULL;

    List list = malloc(sizeof(struct List));
    if (list == NULL) {
        free(p);
        return NULL;
    }

    list->size = 0;
    list->elementSize = elementSize;
    list->allocated = 1;
    list->p = p;
    return list;
}

void List_free(List list) {
    if (list == NULL) return;

    free(list->p);
    list->p = NULL;
    free(list);
}

void List_append(const void *value, List list) {
    if (value == NULL) return;
    if (list == NULL) return;

    _List_incrementSize(list);
    memcpy(list->p+((list->size-1)*list->elementSize), value, list->elementSize);
}

void *List_get(size_t index, List list) {
    if (list == NULL) return NULL;
    if (list->p == NULL) return NULL;
    if (index >= list->size) return NULL;
    return list->p + (index * list->elementSize);
}


static void _List_doubleSize(List list) {
    size_t newSize = list->allocated * 2;
    void *p = realloc(list->p, newSize * list->elementSize);
    if (p == NULL) return;

    list->allocated = newSize;
    list->p = p;
}

static void _List_incrementSize(List list) {
    list->size++;
    if (list->size >= list->allocated) {
        _List_doubleSize(list);
    }
}


// number implementations
LIST_IMPL(char)
LIST_IMPL(short)
LIST_IMPL(int)
LIST_IMPL(float)
LIST_IMPL(double)
LIST_IMPL(long)
LIST_IMPL(longlong)

// unsigned implementations
LIST_IMPL(uchar)
LIST_IMPL(ushort)
LIST_IMPL(uint)
LIST_IMPL(ulong)
LIST_IMPL(ulonglong)


#endif
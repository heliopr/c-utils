#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#ifndef DS_LIST_H
#define DS_LIST_H

#define LIST_IMPL(T) \
    typedef List List_##T;\
    \
    List_##T List_new_##T() {\
        return List_new(sizeof(T));\
    }\
    \
    T List_get_##T(size_t index, List_##T list) {\
        if (list == NULL) return 0;\
        if (index >= list->size) return 0;\
        return ((T*)list->p)[index];\
    }\
    \
    void List_append_##T(T value, List_##T list) {\
        if (list == NULL) return;\
        _List_incrementSize(list);\
        ((T*)list->p)[list->size-1] = value;\
    }\
    \
    void List_prepend_##T(T value, List_##T list) {\
        if (list == NULL) return;\
        T *p = (T*)list->p;\
        _List_incrementSize(list);\
        if (list->size > 1) {\
            size_t i = list->size-1;\
            while (1) {\
                p[i+1] = p[i];\
                if (i == 0) break;\
                i--;\
            }\
        }\
        p[0] = value;\
    }\
    void List_insert_##T(T value, size_t index, List_##T list) {\
        if (list == NULL) return;\
        if (index > list->size) return;\
        size_t size = list->size;\
        _List_incrementSize(list);\
        T *p = (T*)list->p;\
        if (size > 0) {\
            size_t i = size-1;\
            while (1) {\
                p[i+1] = p[i];\
                if (i == index) break;\
                i--;\
            }\
        }\
        p[index] = value;\
    }\
    \
    void List_print_##T(const char *format, List_##T list) {\
        if (list == NULL) return;\
        printf("List{");\
        T *p = (T*)list->p;\
        for (size_t i = 0; i < list->size; i++) {\
            printf(format, p[i]);\
            if (i < list->size-1) printf(", ");\
        }\
        printf("}\n");\
    }\
    \
    List_##T List_map_##T(T (*mapFun)(T), List_##T list) {\
        if (list == NULL) return NULL;\
        if (mapFun == NULL) return NULL;\
        List_##T newList = List_new_##T();\
        T *p = (T*)list->p;\
        for (size_t i = 0; i < list->size; i++) {\
            T mappedVal = (*mapFun)(p[i]);\
            List_append_##T(mappedVal, newList);\
        }\
        return newList;\
    }

#define LIST_GET(T, index, list) (*((T*)List_get(index, list)))
#define LIST_PTR_IND(index, list) (list->p+((index)*list->elementSize))

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
void List_prepend(const void *value, List list);
void *List_get(size_t index, List list);
void List_insert(const void *value, size_t index, List list);


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
    memcpy(LIST_PTR_IND(list->size-1, list), value, list->elementSize);
}

void List_appendPtr(const void *ptr, List list) {
    List_append(&ptr, list);
}

void List_prepend(const void *value, List list) {
    if (value == NULL) return;
    if (list == NULL) return;

    List_insert(value, 0, list);
}

void List_prependPtr(const void *ptr, List list) {
    List_prepend(&ptr, list);
}

void *List_get(size_t index, List list) {
    if (list == NULL) return NULL;
    if (list->p == NULL) return NULL;
    if (index >= list->size) return NULL;
    return list->p + (index * list->elementSize);
}

void List_insert( const void *value, size_t index, List list) {
    if (list == NULL) return;
    if (index > list->size) return;

    size_t size = list->size;
    _List_incrementSize(list);
    memcpy(LIST_PTR_IND(index+1, list), LIST_PTR_IND(index, list), (size-index)*list->elementSize);
    memcpy(LIST_PTR_IND(index, list), value, list->elementSize);
}


static void _List_doubleSize(List list) {
    size_t newSize = list->allocated * 2;
    void *p = realloc(list->p, newSize * list->elementSize);
    if (p == NULL) return;

    list->allocated = newSize;
    list->p = p;
}

static void _List_incrementSize(List list) {
    if (list->size >= list->allocated) {
        _List_doubleSize(list);
    }
    list->size++;
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
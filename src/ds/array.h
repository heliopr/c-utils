#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#ifndef DS_ARRAY_H
#define DS_ARRAY_H

#define ARRAY_IMPL(T) \
    typedef Array Array_##T;\
    \
    Array_##T Array_new_##T() {\
        return Array_new(sizeof(T));\
    }\
    \
    T Array_get_##T(size_t index, Array_##T array) {\
        if (array == NULL) return 0;\
        if (index >= array->size) return 0;\
        return ((T*)array->p)[index];\
    }\
    \
    void Array_append_##T(T value, Array_##T array) {\
        if (array == NULL) return;\
        _Array_incrementSize(array);\
        ((T*)array->p)[array->size-1] = value;\
    }\
    \
    void Array_prepend_##T(T value, Array_##T array) {\
        if (array == NULL) return;\
        T *p = (T*)array->p;\
        _Array_incrementSize(array);\
        if (array->size > 1) {\
            size_t i = array->size-1;\
            while (1) {\
                p[i+1] = p[i];\
                if (i == 0) break;\
                i--;\
            }\
        }\
        p[0] = value;\
    }\
    void Array_insert_##T(T value, size_t index, Array_##T array) {\
        if (array == NULL) return;\
        if (index > array->size) return;\
        size_t size = array->size;\
        _Array_incrementSize(array);\
        T *p = (T*)array->p;\
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
    void Array_print_##T(const char *format, Array_##T array) {\
        if (array == NULL) return;\
        printf("Array{");\
        T *p = (T*)array->p;\
        for (size_t i = 0; i < array->size; i++) {\
            printf(format, p[i]);\
            if (i < array->size-1) printf(", ");\
        }\
        printf("}\n");\
    }\
    \
    Array_##T Array_map_##T(T (*mapFun)(T), Array_##T array) {\
        if (array == NULL) return NULL;\
        if (mapFun == NULL) return NULL;\
        Array_##T newArray = Array_new_##T();\
        T *p = (T*)array->p;\
        for (size_t i = 0; i < array->size; i++) {\
            T mappedVal = (*mapFun)(p[i]);\
            Array_append_##T(mappedVal, newArray);\
        }\
        return newArray;\
    }\
    Array_##T Array_filter_##T(bool (*filter)(T), Array_##T array) {\
        if (array == NULL) return NULL;\
        if (filter == NULL) return NULL;\
        Array_##T newArray = Array_new_##T();\
        T *p = (T*)array->p;\
        for (size_t i = 0; i < array->size; i++) {\
            T val = p[i];\
            if (filter(val)) {\
                Array_append_##T(val, newArray);\
            }\
        }\
        return newArray;\
    }\
    void Array_remove_##T(size_t index, Array_##T array) {\
        if (array == NULL) return;\
        if (index >= array->size) return;\
        T *p = (T*)array->p;\
        for (size_t i = index; i < array->size-1; i++) {\
            p[i] = p[i+1];\
        }\
        _Array_decreaseSize(array);\
    }

#define ARRAY_GET(T, index, array) (*((T*)Array_get(index, array)))
#define ARRAY_PTR_IND(index, array) (array->p+((index)*array->elementSize))

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
typedef long long longlong;

typedef struct Array {
    size_t size;
    size_t allocated;
    size_t elementSize;
    void *p;
} *Array;


static void _Array_realloc(size_t newSize, Array array);
static void _Array_doubleSize(Array arra);
static void _Array_halfSize(Array array);
static void _Array_incrementSize(Array array);
static void _Array_decreaseSize(Array array);


Array Array_new(size_t elementSize);
void Array_free(Array *array);
void Array_append(const void *value, Array array);
void Array_appendPtr(const void *ptr, Array array);
void Array_prepend(const void *value, Array array);
void *Array_get(size_t index, Array array);
void Array_insert(const void *value, size_t index, Array array);


Array Array_new(size_t elementSize) {
    void *p = malloc(elementSize * 1);
    if (p == NULL) return NULL;

    Array array = (Array)malloc(sizeof(struct Array));
    if (array == NULL) {
        free(p);
        return NULL;
    }

    array->size = 0;
    array->elementSize = elementSize;
    array->allocated = 1;
    array->p = p;
    return array;
}

void Array_free(Array *arrayP) {
    if (arrayP == NULL) return;
    Array array = *arrayP;
    if (array == NULL) return;


    free(array->p);
    array->p = NULL;
    free(array);
    *arrayP = NULL;
}

void Array_prealloc(size_t elements, Array array) {
    if (array == NULL) return;
    if (elements == 0) return;
    if (array->size > 0 || array->allocated > 1) return;
    _Array_realloc(elements, array);
}

void Array_append(const void *value, Array array) {
    if (value == NULL) return;
    if (array == NULL) return;

    _Array_incrementSize(array);
    memcpy(ARRAY_PTR_IND(array->size-1, array), value, array->elementSize);
}

void Array_appendPtr(const void *ptr, Array array) {
    Array_append(&ptr, array);
}

void Array_prepend(const void *value, Array array) {
    if (value == NULL) return;
    if (array == NULL) return;

    Array_insert(value, 0, array);
}

void Array_prependPtr(const void *ptr, Array array) {
    Array_prepend(&ptr, array);
}

void *Array_get(size_t index, Array array) {
    if (array == NULL) return NULL;
    if (array->p == NULL) return NULL;
    if (index >= array->size) return NULL;
    return ARRAY_PTR_IND(index, array);
}

void Array_insert( const void *value, size_t index, Array array) {
    if (array == NULL) return;
    if (index > array->size) return;

    size_t size = array->size;
    _Array_incrementSize(array);
    memcpy(ARRAY_PTR_IND(index+1, array), ARRAY_PTR_IND(index, array), (size-index)*array->elementSize);
    memcpy(ARRAY_PTR_IND(index, array), value, array->elementSize);
}


static void _Array_realloc(size_t newSize, Array array) {
    void *p = realloc(array->p, newSize * array->elementSize);
    if (p == NULL) return;

    array->allocated = newSize;
    array->p = p;
}

static void _Array_doubleSize(Array array) {
    _Array_realloc(array->allocated*2, array);
}

static void _Array_halfSize(Array array) {
    _Array_realloc(array->allocated/2, array);
}

static void _Array_incrementSize(Array array) {
    if (array->size >= array->allocated) {
        _Array_doubleSize(array);
    }
    array->size++;
}

static void _Array_decreaseSize(Array array) {
    if (array->size-1 == array->allocated/2) {
        _Array_halfSize(array);
    }
    array->size--;
}


// number implementations
ARRAY_IMPL(char)
ARRAY_IMPL(short)
ARRAY_IMPL(int)
ARRAY_IMPL(float)
ARRAY_IMPL(double)
ARRAY_IMPL(long)
ARRAY_IMPL(longlong)

// unsigned implementations
ARRAY_IMPL(uchar)
ARRAY_IMPL(ushort)
ARRAY_IMPL(uint)
ARRAY_IMPL(ulong)
ARRAY_IMPL(ulonglong)


#endif
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#ifndef _DS_ARRAY_H
#define _DS_ARRAY_H

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
            for (int i = size; i > index; i--) {\
                p[i] = p[i-1];\
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
    Array_##T Array_map_##T(T (*mapFun)(T, size_t), Array_##T array) {\
        if (array == NULL) return NULL;\
        if (mapFun == NULL) return NULL;\
        Array_##T newArray = Array_new_##T();\
        Array_prealloc(array->allocated, newArray);\
        T *p = (T*)array->p;\
        for (size_t i = 0; i < array->size; i++) {\
            T mappedVal = (*mapFun)(p[i], i);\
            Array_append_##T(mappedVal, newArray);\
        }\
        return newArray;\
    }\
    Array_##T Array_filter_##T(bool (*filter)(T), Array_##T array) {\
        if (array == NULL) return NULL;\
        if (filter == NULL) return NULL;\
        Array_##T newArray = Array_new_##T();\
        Array_prealloc(array->allocated, newArray);\
        T *p = (T*)array->p;\
        for (size_t i = 0; i < array->size; i++) {\
            T val = p[i];\
            if (filter(val)) {\
                Array_append_##T(val, newArray);\
            }\
        }\
        _Array_optimizeAllocation(newArray);\
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


void _Array_realloc(size_t newAllocation, Array array);
void _Array_doubleSize(Array array);
void _Array_halfSize(Array array);
void _Array_incrementSize(Array array);
void _Array_decreaseSize(Array array);
void _Array_optimizeAllocation(Array array);


Array Array_new(size_t elementSize);
Array Array_clone(Array array);
void Array_free(Array *array);
void Array_prealloc(size_t elements, Array array);
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

Array Array_clone(Array array) {
    if (array == NULL) return NULL;
    Array clone = Array_new(array->elementSize);
    if (clone == NULL) return NULL;

    Array_prealloc(array->allocated, clone);
    clone->size = array->size;
    memcpy(clone->p, array->p, array->size * array->elementSize);

    return clone;
}

void Array_free(Array *arrayP) {
    if (arrayP == NULL) return;
    Array array = *arrayP;
    if (array == NULL) {
        free(arrayP);
        return;
    }

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


void _Array_realloc(size_t newAllocation, Array array) {
    if (newAllocation == 0) newAllocation = 1;
    void *p = realloc(array->p, newAllocation * array->elementSize);
    if (p == NULL) return;

    array->allocated = newAllocation;
    array->p = p;
}

void _Array_doubleSize(Array array) {
    _Array_realloc(array->allocated*2, array);
}

void _Array_halfSize(Array array) {
    _Array_realloc(array->allocated/2, array);
}

void _Array_incrementSize(Array array) {
    if (array->size >= array->allocated) {
        _Array_doubleSize(array);
    }
    array->size++;
}

void _Array_decreaseSize(Array array) {
    if (array->size-1 == array->allocated/2) {
        _Array_halfSize(array);
    }
    array->size--;
}

void _Array_optimizeAllocation(Array array) {
    if (array->size > array->allocated/2) return;

    size_t size = array->size;
    size_t allocated = array->allocated;
    while (1) {
        size_t new = allocated / 2;
        if (new > size && new > 0) allocated = new;
        else break;
    }

    if (allocated == 0) allocated = 1;
    _Array_realloc(allocated, array);
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
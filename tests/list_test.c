#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "../src/ds/array.h"

int mult(int x) {
    return x*2;
}

bool filterTest(int x) {
    return x%2 == 0;
}

void testArray() {
    printf("Test 1\n");
    {
        Array list = Array_new(sizeof(int));
        assert(list != NULL);
        assert(list->p != NULL);
        assert(list->elementSize == sizeof(int));

        int x = 10;
        Array_prepend(&x, list);
        assert(list->size == 1);
        assert(list->allocated == 1);
        assert(*((int*)Array_get(0, list)) == x);
        assert(ARRAY_GET(int, 0, list) == x);

        x = -500;
        Array_insert(&x, 1, list);
        assert(list->size == 2);
        assert(list->allocated == 2);

        x = 100;
        Array_prepend(&x, list);
        assert(list->size == 3);
        assert(list->allocated == 4);
        assert(*((int*)Array_get(0, list)) == x);

        Array_print_int("%d", list);

        Array_free(list);
    }

    printf("Test 2\n");
    {
        Array_int list = Array_new_int();
        Array_append_int(10, list);
        Array_append_int(-5, list);
        Array_append_int(8, list);
        Array_append_int(3, list);
        Array_append_int(35000, list);

        assert(Array_get_int(0, list) == 10);
        assert(Array_get_int(1, list) == -5);
        assert(Array_get_int(2, list) == 8);
        assert(Array_get_int(3, list) == 3);
        assert(Array_get_int(4, list) == 35000);
        assert(list->size == 5);
        assert(list->allocated == 8);

        Array_print_int("%d", list);

        Array_free(list);
    }

    printf("Test 3\n");
    {
        typedef struct teste
        {
            int a;
            int b;
        } teste_t;
        
        Array list = Array_new(sizeof(teste_t*));
        assert(list != NULL);

        teste_t x = {5, 3}, y = {1, 1};
        Array_appendPtr(&x, list);
        Array_prependPtr(&y, list);
        assert(list->size == 2);
        assert(list->allocated == 2);

        assert(*((void**)Array_get(1, list)) == &x);
        assert(*((void**)Array_get(0, list)) == &y);
        assert(ARRAY_GET(teste_t*, 1, list) == &x);
        assert(ARRAY_GET(teste_t*, 0, list) == &y);

        Array_print_long("%p", list);

        Array_free(list);
    }

    printf("Test 4\n");
    {
        Array_int list = Array_new_int();

        int num = 256;
        int arr[num];
        arr[0] = 0;
        Array_append_int(0, list);
        for (int i = 1; i < num; i++) {
            int val = i+arr[i-1];;
            arr[i] = val;
            Array_append_int(val, list);
        }

        assert(list->size == num);
        assert(list->allocated == pow(2, ceil(log2(num))));

        for (int i = 0; i < num; i++) {
            assert(Array_get_int(i, list) == arr[i]);
        }

        Array_free(list);
    }

    printf("Test 5\n");
    {
        Array_int list = Array_new_int();

        Array_insert_int(5, 0, list);
        assert(list->size == 1);
        assert(list->allocated == 1);
        assert(Array_get_int(0, list) == 5);

        Array_insert_int(4, 0, list);
        assert(list->size == 2);
        assert(list->allocated == 2);
        assert(Array_get_int(0, list) == 4);
        assert(Array_get_int(1, list) == 5);

        Array_insert_int(978, 1, list);
        Array_insert_int(-3, 1, list);
        Array_insert_int(-1, 3, list);
        assert(list->size == 5);
        assert(list->allocated == 8);

        int x = 100;
        Array_prepend_int(x, list);
        assert(list->size == 6);
        assert(list->allocated == 8);
        assert(Array_get_int(0, list) == x);

        Array_print_int("%d", list);

        Array_free(list);
    }

    printf("Test 6\n");
    {
        Array_double list = Array_new_double();

        double x = 10870;
        double y = 1;
        int i = 0;
        Array_append_double(y, list);
        i++;
        while (fabs(x-(y*y)) > 0.0001) {
            y = (y + (x/y))/2;
            Array_append_double(y, list);
            i++;
        }
        assert(list->size == i);
        assert(Array_get_double(list->size-1, list) == y);

        Array_print_double("%f", list);

        Array_free(list);
    }

    printf("Test 7\n");
    {
        Array_float list = Array_new_float();

        int n = 10;
        for (int i = 0; i < n; i++) {
            Array_append_int(i, list);
        }

        Array_int doubled = Array_map_int(mult, list);
        assert(doubled->size == list->size);

        Array_print_int("%d", doubled);

        Array_free(doubled);
        Array_free(list);
    }

    printf("Test 8\n");
    {
        Array_int list = Array_new_int();

        int n = 18;
        for (int i = 0; i < n; i++) {
            Array_append_int(i, list);
        }

        Array_int filtered = Array_filter_int(filterTest, list);

        assert(list->size == n);
        assert(filtered->size == n/2 + (n%2==0?0:1));

        Array_print_int("%d", list);
        Array_print_int("%d", filtered);

        Array_free(list);
        Array_free(filtered);
    }

    printf("Test 9\n");
    {
        Array_int list = Array_new_int();

        for (int i = 0; i < 9; i++) {
            Array_append_int(i, list);
        }
        assert(list->allocated == 16);

        Array_remove_int(0, list);
        assert(list->size == 8);
        assert(list->allocated == 8);

        Array_print_int("%d", list);

        Array_free(list);
    }
}
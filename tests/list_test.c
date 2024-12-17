#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "../src/ds/list.h"

int mult(int x) {
    return x*2;
}

void testList() {
    printf("Test 1\n");
    {
        List list = List_new(sizeof(int));
        assert(list != NULL);
        assert(list->p != NULL);
        assert(list->elementSize == sizeof(int));

        int x = 10;
        List_prepend(&x, list);
        assert(list->size == 1);
        assert(list->allocated == 1);
        assert(*((int*)List_get(0, list)) == x);
        assert(LIST_GET(int, 0, list) == x);

        x = -500;
        List_insert(&x, 1, list);
        assert(list->size == 2);
        assert(list->allocated == 2);

        x = 100;
        List_prepend(&x, list);
        assert(list->size == 3);
        assert(list->allocated == 4);
        assert(*((int*)List_get(0, list)) == x);

        List_print_int("%d", list);

        List_free(list);
    }

    printf("Test 2\n");
    {
        List_int list = List_new_int();
        List_append_int(10, list);
        List_append_int(-5, list);
        List_append_int(8, list);
        List_append_int(3, list);
        List_append_int(35000, list);

        assert(List_get_int(0, list) == 10);
        assert(List_get_int(1, list) == -5);
        assert(List_get_int(2, list) == 8);
        assert(List_get_int(3, list) == 3);
        assert(List_get_int(4, list) == 35000);
        assert(list->size == 5);
        assert(list->allocated == 8);

        List_print_int("%d", list);

        List_free(list);
    }

    printf("Test 3\n");
    {
        typedef struct teste
        {
            int a;
            int b;
        } teste_t;
        
        List list = List_new(sizeof(teste_t*));
        assert(list != NULL);

        teste_t x = {5, 3}, y = {1, 1};
        List_appendPtr(&x, list);
        List_prependPtr(&y, list);
        assert(list->size == 2);
        assert(list->allocated == 2);

        assert(*((void**)List_get(1, list)) == &x);
        assert(*((void**)List_get(0, list)) == &y);
        assert(LIST_GET(teste_t*, 1, list) == &x);
        assert(LIST_GET(teste_t*, 0, list) == &y);

        List_print_long("%p", list);

        List_free(list);
    }

    printf("Test 4\n");
    {
        List_int list = List_new_int();

        int num = 256;
        int arr[num];
        arr[0] = 0;
        List_append_int(0, list);
        for (int i = 1; i < num; i++) {
            int val = i+arr[i-1];;
            arr[i] = val;
            List_append_int(val, list);
        }

        assert(list->size == num);
        assert(list->allocated == pow(2, ceil(log2(num))));

        for (int i = 0; i < num; i++) {
            assert(List_get_int(i, list) == arr[i]);
        }

        List_free(list);
    }

    printf("Test 5\n");
    {
        List_int list = List_new_int();

        List_insert_int(5, 0, list);
        assert(list->size == 1);
        assert(list->allocated == 1);
        assert(List_get_int(0, list) == 5);

        List_insert_int(4, 0, list);
        assert(list->size == 2);
        assert(list->allocated == 2);
        assert(List_get_int(0, list) == 4);
        assert(List_get_int(1, list) == 5);

        List_insert_int(978, 1, list);
        List_insert_int(-3, 1, list);
        List_insert_int(-1, 3, list);
        assert(list->size == 5);
        assert(list->allocated == 8);

        int x = 100;
        List_prepend_int(x, list);
        assert(list->size == 6);
        assert(list->allocated == 8);
        assert(List_get_int(0, list) == x);

        List_print_int("%d", list);
        List_print_int("%d", List_map_int(mult, list));

        List_free(list);
    }
}
#include <stdio.h>
#include <assert.h>
#include "../src/ds/list.h"

void testList() {
    printf("Test 1\n");
    {
        List list = List_new(sizeof(int));
        assert(list != NULL);
        assert(list->p != NULL);
        assert(list->elementSize == sizeof(int));

        int x = 10;
        List_append(&x, list);
        assert(list->size == 1);
        assert(list->allocated == 2);
        assert(*((int*)List_get(0, list)) == x);
        assert(LIST_GET(int, 0, list) == x);

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
        List_appendPtr(&y, list);
        assert(list->size == 2);
        assert(list->allocated == 4);

        assert(*((void**)List_get(0, list)) == &x);
        assert(*((void**)List_get(1, list)) == &y);
        assert(LIST_GET(teste_t*, 0, list) == &x);

        assert(LIST_GET(teste_t*, 0, list) == &x);
        assert(LIST_GET(teste_t*, 1, list) == &y);

        List_free(list);
    }
}
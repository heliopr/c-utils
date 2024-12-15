#include <stdio.h>
#include <assert.h>
#include "../src/ds/list.h"

void testList() {
    {
        List list = {0};
        List_init(sizeof(int), &list);
        assert(list.p != NULL);
        assert(list.elementSize == sizeof(int));

        int x = 5;
        List_append(&x, &list);
        assert(list.size == 1);
        assert(list.allocated == 1);
        assert(*((int*)List_get(0, &list)) == x);

        List_free(&list);
        assert(list.p == NULL);
    }

    {
        List list = List_new_int();
        List_append_int(10, &list);
        List_append_int(-5, &list);
        List_append_int(8, &list);
        List_append_int(3, &list);

        assert(List_get_int(0, &list) == 10);
        assert(List_get_int(1, &list) == -5);
        assert(List_get_int(2, &list) == 8);
        assert(List_get_int(3, &list) == 3);
        assert(List_get_int(4, &list) == -1);
        assert(list.size == 4);
    }
}
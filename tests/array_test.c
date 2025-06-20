#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include "../src/array.h"


int mult(int x, size_t i) {
    return x*2;
}

bool filterTest(int x) {
    return x%2 == 0;
}

void testArray() {
    printf("Test 1\n");
    {
        Array array = Array_new(sizeof(int));
        assert(array != NULL);
        assert(array->p != NULL);
        assert(array->elementSize == sizeof(int));

        int x = 10;
        Array_prepend(&x, array);
        assert(array->size == 1);
        assert(array->allocated == 1);
        assert(*((int*)Array_get(0, array)) == x);
        assert(ARRAY_GET(int, 0, array) == x);

        x = -500;
        Array_insert(&x, 1, array);
        assert(array->size == 2);
        assert(array->allocated == 2);

        x = 100;
        Array_prepend(&x, array);
        assert(array->size == 3);
        assert(array->allocated == 4);
        assert(*((int*)Array_get(0, array)) == x);

        Array_print_int("%d", array);

        Array_free(&array);
        assert(array == NULL);
    }

    printf("Test 2\n");
    {
        Array_int array = Array_new_int();
        Array_append_int(10, array);
        Array_append_int(-5, array);
        Array_append_int(8, array);
        Array_append_int(3, array);
        Array_append_int(35000, array);

        assert(Array_get_int(0, array) == 10);
        assert(Array_get_int(1, array) == -5);
        assert(Array_get_int(2, array) == 8);
        assert(Array_get_int(3, array) == 3);
        assert(Array_get_int(4, array) == 35000);
        assert(array->size == 5);
        assert(array->allocated == 8);

        Array_print_int("%d", array);

        Array_free(&array);
        assert(array == NULL);
    }

    printf("Test 3\n");
    {
        typedef struct teste
        {
            int a;
            int b;
        } teste_t;
        
        Array array = Array_new(sizeof(teste_t*));
        assert(array != NULL);

        teste_t x = {5, 3}, y = {1, 1};
        Array_appendPtr(&x, array);
        Array_prependPtr(&y, array);
        assert(array->size == 2);
        assert(array->allocated == 2);

        assert(*((void**)Array_get(1, array)) == &x);
        assert(*((void**)Array_get(0, array)) == &y);
        assert(ARRAY_GET(teste_t*, 1, array) == &x);
        assert(ARRAY_GET(teste_t*, 0, array) == &y);

        Array_print_long("%p", array);

        Array_free(&array);
        assert(array == NULL);
    }

    printf("Test 4\n");
    {
        Array_int array = Array_new_int();

        int num = 256;
        int arr[num];
        arr[0] = 0;
        Array_append_int(0, array);
        for (int i = 1; i < num; i++) {
            int val = i+arr[i-1];;
            arr[i] = val;
            Array_append_int(val, array);
        }

        assert(array->size == num);
        assert(array->allocated == pow(2, ceil(log2(num))));

        for (int i = 0; i < num; i++) {
            assert(Array_get_int(i, array) == arr[i]);
        }

        Array_free(&array);
        assert(array == NULL);
    }

    printf("Test 5\n");
    {
        Array_int array = Array_new_int();

        Array_insert_int(5, 0, array);
        assert(array->size == 1);
        assert(array->allocated == 1);
        assert(Array_get_int(0, array) == 5);

        Array_insert_int(4, 0, array);
        assert(array->size == 2);
        assert(array->allocated == 2);
        assert(Array_get_int(0, array) == 4);
        assert(Array_get_int(1, array) == 5);

        Array_insert_int(978, 1, array);
        Array_insert_int(-3, 1, array);
        Array_insert_int(-1, 3, array);
        assert(array->size == 5);
        assert(array->allocated == 8);

        int x = 100;
        Array_prepend_int(x, array);
        assert(array->size == 6);
        assert(array->allocated == 8);
        assert(Array_get_int(0, array) == x);

        Array_print_int("%d", array);

        Array_free(&array);
        assert(array == NULL);
    }

    printf("Test 6\n");
    {
        Array_double array = Array_new_double();

        double x = 10870;
        double y = 1;
        int i = 0;
        Array_append_double(y, array);
        i++;
        while (fabs(x-(y*y)) > 0.0001) {
            y = (y + (x/y))/2;
            Array_append_double(y, array);
            i++;
        }
        assert(array->size == i);
        assert(Array_get_double(array->size-1, array) == y);

        Array_print_double("%f", array);

        Array_free(&array);
        assert(array == NULL);
    }

    printf("Test 7\n");
    {
        Array_float array = Array_new_float();

        int n = 10;
        for (int i = 0; i < n; i++) {
            Array_append_int(i, array);
        }

        Array_int doubled = Array_map_int(mult, array);
        assert(doubled->size == array->size);

        Array_print_int("%d", doubled);

        Array_free(&doubled);
        Array_free(&array);
        assert(array == NULL);
        assert(doubled == NULL);
    }

    printf("Test 8\n");
    {
        Array_int array = Array_new_int();

        int n = 18;
        for (int i = 0; i < n; i++) {
            Array_append_int(i, array);
        }

        Array_int filtered = Array_filter_int(filterTest, array);

        assert(array->size == n);
        assert(filtered->size == n/2 + (n%2==0?0:1));
        assert(filtered->allocated*2 >= filtered->size);

        Array_print_int("%d", array);
        Array_print_int("%d", filtered);

        Array_free(&array);
        Array_free(&filtered);
        assert(array == NULL);
        assert(filtered == NULL);
    }

    printf("Test 9\n");
    {
        Array_int array = Array_new_int();

        for (int i = 0; i < 9; i++) {
            Array_append_int(i, array);
        }
        assert(array->allocated == 16);

        Array_remove_int(0, array);
        assert(array->size == 8);
        assert(array->allocated == 8);

        Array_print_int("%d", array);

        Array_free(&array);
        assert(array == NULL);
    }

    printf("Test 10\n");
    {
        Array_int array = Array_new_int();
        Array_prealloc(8, array);
        assert(array->allocated == 8);

        for (int i = 0; i < 8; i++) {
            Array_append_int(i, array);
            assert(array->size == i+1);
            assert(array->allocated == 8);
        }

        Array_append_int(-100, array);
        assert(array->size == 9);
        assert(array->allocated == 16);

        Array_free(&array);
        assert(array == NULL);
    }

    printf("Test 11\n");
    {
        srand(time(NULL));
        Array_int array = Array_new_int();
        
        int n = 20;
        for (int i = 0; i < n; i++) Array_append_int(rand() % 100, array);

        Array_int clone = Array_clone(array);
        assert(clone != array);
        assert(clone->size == array->size);
        assert(clone->allocated == array->allocated);
        assert(clone->p != array->p);

        for (int i = 0; i < n; i++) assert(Array_get_int(i, array) == Array_get_int(i, clone));

        Array_remove_int(4, clone);
        assert(Array_get_int(4, clone) == Array_get_int(5, array));
        assert(clone->size+1 == array->size);

        Array_free(&array);
        Array_free(&clone);
        assert(array == NULL);
        assert(clone == NULL);
    }

    printf("Test 12\n");
    {
        clock_t start = clock();
        
        for (int i = 0; i < 1024; i++) {
            Array_int array = Array_new_int();
            Array_prealloc(256, array);
            for (int i = 0; i < 256; i++) {
                Array_append(&i, array);
            }
            Array_free(&array);
            assert(array == NULL);
        }

        double dt = (double)(clock()-start)/CLOCKS_PER_SEC;
        printf("Time: %fs\n", dt);
    }

    printf("Test 13\n");
    {
        Array_int array = Array_new_int();
        _Array_optimizeAllocation(array);
        Array_prealloc(32, array);

        for (int i = 0; i < 13; i++) Array_append_int(5, array);

        for (int i = 0; i < 2; i++) Array_append_int(5, array);

        assert(array->allocated == 32);

        _Array_optimizeAllocation(array);

        assert(array->size == 15);
        assert(array->allocated == 16);

        int size = array->size;
        for (int i = 0; i < size; i++) {
            Array_remove_int(0, array);
        }
        assert(array->size == 0);
        assert(array->allocated == 1);

        _Array_optimizeAllocation(array);
        assert(array->size == 0);
        assert(array->allocated == 1);

        Array_print_int("%d", array);

        Array_free(&array);
    }

    printf("Test 14\n");
    {
        typedef struct test {
            int x, y;
        } test_t;
        Array array = Array_new(sizeof(test_t));

        test_t a = {1, 2}, b = {3, 4};
        Array_append(&b, array);
        Array_append(&a, array);

        assert(array->allocated == 2);
        assert(array->size == 2);
        assert(array->elementSize == sizeof(test_t));

        test_t a2, b2;
        a2 = ARRAY_GET(test_t, 1, array);
        b2 = ARRAY_GET(test_t, 0, array);
        printf("a = test_t{x=%d, y=%d}, b = test_t{x=%d, y=%d}\n", a2.x, a2.y, b2.x, b2.y);

        assert(a.x == a2.x);
        assert(a.y == a2.y);
        assert(b.x == b2.x);
        assert(b.y == b2.y);

        a.x = -100;
        assert(a2.x == 1);
        assert(a2.x != a.x);

        Array_free(&array);
    }
}
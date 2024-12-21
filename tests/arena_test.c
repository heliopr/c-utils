#include <stdio.h>
#include <assert.h>
#include "../src/arena.h"

void testArena() {
    printf("Test 1\n");
    {
        Arena arena = Arena_new();
        assert(arena != NULL);
        assert(arena->p != NULL);

        void *p = Arena_alloc(4, arena);
        assert(p != NULL);

        Arena_free(&arena);
    }

    printf("Test 2\n");
    {
        ARENA({
            int *p = Arena_alloc(arena, 4);
            *p = 10877671;
            int *p2 = Arena_alloc(arena, 100);
            *p2 = -8573;

            assert(arena->size == 128);
            assert(arena->offset == 104);
            assert(*p == 10877671);
            assert(*p2 == -8573);
        });
    }
}
#include <stdlib.h>
#include <stdio.h>

#ifndef _ARENA_H
#define _ARENA_H

#define ARENA(code) ({ Arena arena = Arena_new(); (code); Arena_free(&arena); })

typedef struct Arena {
    size_t size;
    size_t offset;
    void *p;
} *Arena;


void *_Arena_grow(size_t size, Arena arena);

Arena Arena_new();
void *Arena_alloc(size_t size, Arena arena);
void Arena_free(Arena *arenaP);


Arena Arena_new() {
    Arena arena = (Arena)malloc(sizeof(struct Arena));
    if (arena == NULL) return NULL;

    void *p = malloc(1);
    if (p == NULL) return NULL;

    arena->offset = 0;
    arena->size = 1;
    arena->p = p;
    return arena;
}

void *Arena_alloc(size_t size, Arena arena) {
    if (arena == NULL) return NULL;
    if (arena->p == NULL) return NULL;
    if (size == 0) return NULL;

    return _Arena_grow(size, arena);
}

void Arena_free(Arena *arenaP) {
    if (arenaP == NULL) return;
    Arena arena = *arenaP;
    if (arena == NULL) {
        free(arenaP);
        return;
    }

    free(arena->p);
    arena->p = NULL;
    free(arena);
    *arenaP = NULL;
}

void *_Arena_grow(size_t size, Arena arena) {
    size_t oldOffset = arena->offset;
    size_t newOffset = arena->offset + size;
    size_t newSize = arena->size;
    while (newOffset > newSize) {
        newSize *= 2;
    }

    void *p = realloc(arena->p, newSize);
    if (p == NULL) return NULL;

    arena->offset = newOffset;
    arena->size = newSize;
    arena->p = p;
    return arena->p + oldOffset;
}

#endif
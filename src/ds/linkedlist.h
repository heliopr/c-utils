#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct llnode {
    void *data;
    struct llnode *next;
} llnode;

typedef struct linkedlist {
    llnode *first;
    size_t size, element_size;
} linkedlist;

linkedlist *linkedlist_new(size_t element_size);
bool linkedlist_insert_after(linkedlist *ll, const void *e, llnode *node);
bool linkedlist_insert_at(linkedlist *ll, const void *e, size_t pos);
bool linkedlist_prepend(linkedlist *ll, const void *e);
bool linkedlist_append(linkedlist *ll, const void *e);
bool linkedlist_remove(linkedlist *ll, llnode *node);
llnode *linkedlist_get(linkedlist *ll, size_t pos);
llnode *linkedlist_find(linkedlist *ll, const void *e); 
size_t linkedlist_find_pos(linkedlist *ll, const void *e);

#endif
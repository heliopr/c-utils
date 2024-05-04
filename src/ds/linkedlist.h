#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct llnode {
    void *data;
    struct llnode *next;
} llnode;

typedef struct llist {
    llnode *first;
    size_t size, element_size;
} llist;

llist *llist_new(size_t element_size);
bool llist_insert_after(llist *ll, const void *e, llnode *node);
bool llist_insert_at(llist *ll, const void *e, size_t pos);
bool llist_prepend(llist *ll, const void *e);
bool llist_append(llist *ll, const void *e);
bool llist_remove(llist *ll, llnode *node);
llnode *llist_get(llist *ll, size_t pos);
llnode *llist_find(llist *ll, const void *e); 
size_t llist_find_pos(llist *ll, const void *e);

#endif
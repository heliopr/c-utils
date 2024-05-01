#include "linkedlist.h"

#include <string.h>

llist *llist_new(size_t element_size) {
    llist *ll = (llist*)malloc(sizeof(llist));
    if (ll == NULL) return NULL;

    ll->element_size = element_size;
    ll->size = 0;
    ll->first = NULL;
    return ll;
}

bool llist_insert(llist *ll, const void *e, llnode *node) {
    if (ll == NULL || e == NULL || node == NULL) return false;

    llnode *new_node = malloc(sizeof(llnode));
    new_node->data = malloc(ll->element_size);
    memcpy(new_node->data, e, ll->element_size);

    llnode *next = node->next;
    node->next = new_node;
    new_node->next = next;
    return true;
}

llnode *llist_get(llist *ll, size_t pos) {
    
}
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

llnode *llist_new_node(const void *e, size_t element_size) {
    if (e == NULL) return NULL;

    llnode *new_node = malloc(sizeof(llnode));
    if (new_node == NULL) return NULL;

    new_node->data = malloc(element_size);
    if (new_node->data == NULL) return NULL;

    memcpy(new_node->data, e, element_size);

    return new_node;
}

void llist_free_node(llnode *node) {
    free(node->data);
    free(node);
}

bool llist_insert_after(llist *ll, const void *e, llnode *node) {
    if (ll == NULL || e == NULL || node == NULL) return false;

    llnode *new_node = llist_new_node(e, ll->element_size);
    llnode *next = node->next;
    node->next = new_node;
    new_node->next = next;
    ll->size++;
    return true;
}

bool llist_insert_at(llist *ll, const void *e, size_t pos) {
    if (ll == NULL || e == NULL || pos < 0 || pos > ll->size) return false;

    if (pos > 0) {
        llnode *node = llist_get(ll, pos-1);
        if (node == NULL) return false;
        return llist_insert_after(ll, e, node);
    }
    else if (pos == 0) {
        llnode *new_node = llist_new_node(e, ll->element_size);
        if (new_node == NULL) return false;
        new_node->next = ll->first;
        ll->first = new_node;
        ll->size++;
        return true;
    }

    return false;
}

bool llist_prepend(llist *ll, const void *e) {
    if (ll == NULL || e == NULL) return false;
    return llist_insert_at(ll, e, 0);
}

bool llist_append(llist *ll, const void *e) {
    if (ll == NULL || e == NULL) return false;
    return llist_insert_at(ll, e, ll->size);
}

// untested stupid approach
bool llist_remove(llist *ll, llnode *node) {
    if (ll == NULL || node == NULL) return false;

    if (ll->first == node) {
        ll->first = node->next;
    }
    else {
        llnode *last = ll->first;
        for (int i = 1; i < ll->size; i++) {
            if (last->next == node) {
                last->next = node->next;
                break;
            }
            last = last->next;
            if (last == NULL) return false;
        }
    }

    llist_free_node(node);
    ll->size--;
    return true;
}

llnode *llist_get(llist *ll, size_t pos) {
    if (ll == NULL || pos < 0 || pos >= ll->size) return NULL;

    llnode *node = ll->first;
    for (int i = 0; i <= pos; i++) {
        if (node == NULL) return NULL;

        if (i == pos)
            return node;
        
        if (node->next == NULL) return NULL;
        node = node->next;
    }

    return NULL;
}
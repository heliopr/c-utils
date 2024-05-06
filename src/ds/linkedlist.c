#include "linkedlist.h"

#include <string.h>
#include <stdint.h>

linkedlist *linkedlist_new(size_t element_size) {
    linkedlist *ll = (linkedlist*)malloc(sizeof(linkedlist));
    if (ll == NULL) return NULL;

    ll->element_size = element_size;
    ll->size = 0;
    ll->first = NULL;
    return ll;
}

llnode *linkedlist_new_node(const void *e, size_t element_size) {
    if (e == NULL) return NULL;

    llnode *new_node = malloc(sizeof(llnode));
    if (new_node == NULL) return NULL;

    new_node->data = malloc(element_size);
    if (new_node->data == NULL) return NULL;

    memcpy(new_node->data, e, element_size);

    return new_node;
}

void linkedlist_free_node(llnode *node) {
    free(node->data);
    free(node);
}

bool linkedlist_insert_after(linkedlist *ll, const void *e, llnode *node) {
    if (ll == NULL || e == NULL || node == NULL) return false;

    llnode *new_node = linkedlist_new_node(e, ll->element_size);
    llnode *next = node->next;
    node->next = new_node;
    new_node->next = next;
    ll->size++;
    return true;
}

bool linkedlist_insert_at(linkedlist *ll, const void *e, size_t pos) {
    if (ll == NULL || e == NULL || pos < 0 || pos > ll->size) return false;

    if (pos > 0) {
        llnode *node = linkedlist_get(ll, pos-1);
        if (node == NULL) return false;
        return linkedlist_insert_after(ll, e, node);
    }
    else if (pos == 0) {
        llnode *new_node = linkedlist_new_node(e, ll->element_size);
        if (new_node == NULL) return false;
        new_node->next = ll->first;
        ll->first = new_node;
        ll->size++;
        return true;
    }

    return false;
}

bool linkedlist_prepend(linkedlist *ll, const void *e) {
    if (ll == NULL || e == NULL) return false;
    return linkedlist_insert_at(ll, e, 0);
}

bool linkedlist_append(linkedlist *ll, const void *e) {
    if (ll == NULL || e == NULL) return false;
    return linkedlist_insert_at(ll, e, ll->size);
}

bool linkedlist_remove(linkedlist *ll, llnode *node) {
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

    linkedlist_free_node(node);
    ll->size--;
    return true;
}

llnode *linkedlist_get(linkedlist *ll, size_t pos) {
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

llnode *linkedlist_find(linkedlist *ll, const void *e) {
    if (ll == NULL || e == NULL) return NULL;

    llnode *node = ll->first;
    for (int i = 0; i < ll->size; i++) {
        if (node == NULL) break;

        if (memcmp(node->data, e, ll->element_size) == 0)
            return node;

        if (node->next == NULL) return NULL;
        node = node->next;
    }

    return NULL;
}

size_t linkedlist_find_pos(linkedlist *ll, const void *e) {
    if (ll == NULL || e == NULL) return SIZE_MAX;

    llnode *node = ll->first;
    for (int i = 0; i < ll->size; i++) {
        if (node == NULL) break;

        if (memcmp(node->data, e, ll->element_size) == 0)
            return i;

        if (node->next == NULL) break;
        node = node->next;
    }

    return SIZE_MAX;
}
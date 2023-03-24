#ifndef __LL_H__
#define __LL_H__

typedef struct ll_t ll_t;

// Insert an element to a linked list.
//
// list may be NULL, in which case a new linked list will be created.
//
// Returns the list that results from inserting the element.
ll_t *ll_insert(ll_t *list, int v);

// Get the value at index idx.
//
// val will contain the value at index idx, if idx is a valid index.
//
// Returns 0 if idx outside the range of elements in the list.
int ll_at(ll_t *list, int idx, int *val);

// Print elements in the given list.
void ll_print(ll_t *list);

// Free the given linked list.
void ll_free(ll_t *list);

#endif

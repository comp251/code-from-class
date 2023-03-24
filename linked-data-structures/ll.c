#include "ll.h"

#include <stdio.h>
#include <stdlib.h>

// More Java-y ☕️
struct ll_node {
  int value;
  struct ll_node *next;
};

struct ll {
  struct ll_node *head;
  struct ll_node *tail;
  int n_elements;
  char *name_of_list;
};
// ☕️

// C-y 🌊
struct ll_t {
  int value;
  struct ll_t *next;
};

// Insert an element to a linked list.
//
// list may be NULL, in which case a new linked list will be created.
//
// Returns the list that results from inserting the element.
ll_t *ll_insert(ll_t *list, int v) {
  // when we insert an element, we will always insert it at the head.
  ll_t *new_node = malloc(sizeof(ll_t));
  new_node->value = v;
  // 1. point to old head; if list is NULL, next is NULL.
  new_node->next = list;
  // 2. this is the new head
  return new_node;
}

// Get the value at index idx.
//
// val will contain the value at index idx, if idx is a valid index.
//
// Returns 0 if idx outside the range of elements in the list.
int ll_at(ll_t *list, int idx, int *val) {
  ll_t *cur = list; // current location in the list; start at head
  if (idx < 0) {
    return 0;
  }
  int i = 0;
  while (cur && i < idx) {
    cur = cur->next;
    i++;
  }
  if (!cur) {
    // i was too large
    return 0;
  }
  *val = cur->value;
  return 1;
  /*
  // 🤮
  for (int i = 0, cur = list; cur && i < idx; i++, cur = cur->next) { }
  */
}

// Print elements in the given list.
void ll_print(ll_t *list) {
  printf("[");
  for (ll_t *cur = list; cur; cur = cur->next) {
    printf("%d%s", cur->value, cur->next ? ", " : "");
  }
  /* alternatively...
  ll_t *cur = list;
  while (cur) {
    printf("%d%s", cur->value, cur->next ? ", " : "");
    cur = cur->next;
  }
  */
  printf("]\n");
}

// Free the given linked list.
void ll_free(ll_t *list) {
  // starting at the head, free each node.
  ll_t *cur = list;
  while (cur) {
    // remember the next node
    ll_t *tmp = cur->next;
    // free the current node
    free(cur);
    // advance cur
    cur = tmp;
  }
}

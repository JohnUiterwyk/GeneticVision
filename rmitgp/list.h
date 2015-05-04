
#ifndef _LIST_H_
#define _LIST_H_

typedef struct lists
{
    int index;
    struct lists *parent;
    struct lists *child;
} list;

/* A custom doubly linked list implemenation */

/* Insert an element X into the list at location specified by NODE */
void insert (list *node, int x);

/* Delete the node NODE from the list */
list* del (list *node);

#endif

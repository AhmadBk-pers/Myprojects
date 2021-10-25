/******************************************************************************
* List Utils, Created For testing list functions without a list struct
* - Implementation File
*
* Author: Fania Volkov
* Approved by:---
*
* ILRD OL110, Ramat Gan
*
*******************************************************************************/

#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */
#include "node_utils.h"

/*O(n)
 creates a list with 5 nodes : e->d->c->b->a->end
 returns the head node of the list on success, or NULL on failure */
node_t *NodeUtilCreate()
{
    char *strs[] = {"a", "b", "c", "d", "e"};
    size_t i = 0;
    size_t len = sizeof(strs) / sizeof(*strs);
    node_t *new_list_head = (node_t *)malloc(sizeof(*new_list_head));

    if (!new_list_head)
    {
        return NULL;
    }

    new_list_head->data = strs[0];
    new_list_head->next = NULL;

    for (i = 1; i < len; ++i)
    {
        node_t *iter = NodeUtilAddBefore(new_list_head, strs[i]);

        if (!iter)
        {
            NodeUtilDestroy(new_list_head);
            return NULL;
        }

        new_list_head = iter;
    }
    /* returns a list : e->d->c->b->a->end*/
    return new_list_head;
}

/*O(n)
frees all memory allocated to all the nodes after 'head'*/
void NodeUtilDestroy(node_t *head)
{
    while (NULL != head)
    {
        head = NodeUtilRemove(head);
    }
}

/*O(1)
 Removes the given node from the list and returns it */
node_t *NodeUtilRemove(node_t *iter)
{
    node_t *next = NULL;

    assert(iter);

    next = NodeUtilGetNext(iter);

    if (!next)
    {
        free(iter);
        iter = NULL;
        return iter;
    }

    iter->data = NodeUtilGetData(next);
    iter->next = NodeUtilGetNext(next);

    free(next);
    next = NULL;

    return iter;
}

/*O(1)
 Creates and adds new node with 'data', before given one, and returns it
Returns NULL on failure */
node_t *NodeUtilAddBefore(node_t *iter, void *data)
{
    node_t *new_list_iter = NULL;

    assert(iter);

    new_list_iter = (node_t *)malloc(sizeof(*new_list_iter));
    if (!new_list_iter)
    {
        return NULL;
    }

    new_list_iter->data = iter->data;
    new_list_iter->next = iter->next;

    iter->next = new_list_iter;
    iter->data = data;

    return iter;
}


/*O(1)
 returns the node valid 'iter' points to */
node_t *NodeUtilGetNext(const node_t *iter)
{
    assert(iter);
    return iter->next;
}

/*O(1)
 returns the data stored in the node the valid 'iter' points to */
void *NodeUtilGetData(const node_t *iter)
{
    assert(iter);
    return iter->data;
}

/*O(n)
prints a list, starting with 'head', ending with a node pointing to NULL*/
void NodeUtilPrintSList(const node_t *head)
{
    assert(head);

    while (NULL != head)
    {
        printf("%s ->", (char *)NodeUtilGetData(head));
        head = NodeUtilGetNext(head);
    }

    printf("NULL\n");
}

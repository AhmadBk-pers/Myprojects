/******************************************************************************
* List Utils, Created For testing list functions without a list struct
* - API H File
*
* Author: Fania Volkov
* Approved by:---
*
* ILRD OL110, Ramat Gan
*
*******************************************************************************/

#ifndef __NODE_UTILS_ILRD_OL110_H__
#define __NODE_UTILS_ILRD_OL110_H__

#define __NODE_T__

typedef struct node
{
    void *data;
    struct node *next;
} node_t;

/*O(n)
 creates a list with 5 nodes : e->d->c->b->a->end
 returns the head node of the list on success, or NULL on failure */
node_t *NodeUtilCreate();

/*O(n)
frees all memory allocated to all the nodes after 'head'*/
void NodeUtilDestroy(node_t *head);

/*O(1)
 Removes the given node from the list and returns it */
node_t *NodeUtilRemove(node_t *iter);

/*O(1)
 Creates and adds new node with 'data', before given one, and returns it
Returns NULL on failure */
node_t *NodeUtilAddBefore(node_t *iter, void *data);


/*O(1)
 returns the node valid 'iter' points to */
node_t *NodeUtilGetNext(const node_t *iter);

/*O(1)
 returns the data stored in the node the valid 'iter' points to */
void *NodeUtilGetData(const node_t *iter);

/*O(n)
prints a list, starting with 'head', ending with a node pointing to NULL*/
void NodeUtilPrintSList(const node_t *head);


#endif /* __LIST_EXE_ILRD_OL110_H__ */

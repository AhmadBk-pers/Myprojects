/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      Shani
* Description   Doubly_Linked_List module
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/

#include <stdlib.h>	/*malloc free*/
#include <assert.h> /* assert*/

#include "dlist.h"


#define NODE_TO_P(node) (&(node))

typedef struct dl_node dl_node_t; 

struct dl_node
{
    dl_node_t *prev;
    dl_node_t *next;
    void *data;
};

struct dlist
{
    dl_node_t head;
    dl_node_t tail;
};


static dl_iter_t NodeToIter(dl_node_t *node)
{
	dl_iter_t iter;
	assert(node);
	iter.internal = node;
	
	return iter;
}

static dl_node_t *IterToNode(dl_iter_t iter)
{
	return iter.internal;
}

static const dl_iter_t INVALID_ITERATOR = {NULL};

dlist_t *DLCreate(void)
{
	dlist_t *dlist = (dlist_t *)malloc(sizeof(dlist_t));
	if (!(dlist))
    {
        return NULL;
    }
	
	dlist->tail.next = NULL;
	dlist->tail.prev = &(dlist->head);
	dlist->tail.data = NULL;
	
	dlist->head.next = &(dlist->tail);
	dlist->head.prev = NULL;
	dlist->head.data = NULL;
	
	return dlist;
}

void DLDestroy(dlist_t *dlist)
{
	
	assert(dlist);
	
	while(!DLIsEmpty(dlist))
    {
    	dl_node_t *node;
        node = dlist->head.next;
        dlist->head.next = node->next;
        
        node->next = NULL;
        node->prev = NULL;
        node->data = NULL;
     	free(node);
     	node = NULL;
    }
	
	free(dlist);
	dlist = NULL;
}

int DLIsEmpty(const dlist_t *dlist)
{
	assert(dlist);
	
	return DLIsIterEqual(DLBegin(dlist), DLEnd(dlist));
}

dl_iter_t DLBegin(const dlist_t *dlist)
{
	assert(dlist);
	
	return NodeToIter(dlist->head.next);
}

dl_iter_t DLEnd(const dlist_t *dlist)
{
	assert(dlist);
	
	return NodeToIter((dl_node_t *)&(dlist->tail));
}

dl_iter_t DLNext(dl_iter_t dl_iter)
{
	assert(IterToNode(dl_iter));
	
	return NodeToIter(IterToNode(dl_iter)->next);
}

dl_iter_t DLPrev(dl_iter_t dl_iter)
{
	assert(IterToNode(dl_iter));
	
	return NodeToIter(IterToNode(dl_iter)->prev);
}

size_t DLSize(const dlist_t *dlist)
{
	dl_iter_t iter = INVALID_ITERATOR;
	dl_iter_t iter_end = INVALID_ITERATOR;
	size_t count = 0;
	
	assert(dlist);
	
	iter_end = DLEnd(dlist);
	
	for (iter = DLBegin(dlist);
		!DLIsIterEqual(iter, iter_end);
		iter = DLNext(iter))
	{
		++count;
	}
	
	return count;
}

void *DLGetData(dl_iter_t dl_iter)
{
	assert(IterToNode(dl_iter));
	
	return IterToNode(dl_iter)->data;
}

void DLSetData(dl_iter_t dl_iter, void *data)
{
	assert(IterToNode(dl_iter));
	
	IterToNode(dl_iter)->data = data;
}

int DLIsIterEqual(dl_iter_t dl_i1, dl_iter_t dl_i2)
{
	assert(IterToNode(dl_i1));
	assert(IterToNode(dl_i2));
	
	return IterToNode(dl_i1) == IterToNode(dl_i2);
}

dl_iter_t DLInsert(dl_iter_t dl_iter, void *data)
{
	dl_node_t *current_node = IterToNode(dl_iter);
	dl_node_t *new_node = (dl_node_t *)malloc(sizeof(dl_node_t));
	
	assert(IterToNode(dl_iter));
	
	if (!new_node)
	{
		while((IterToNode(dl_iter)->next))
		{
			dl_iter = DLNext(dl_iter);
		}
		return dl_iter;
	}
	
	new_node->prev = current_node->prev;
	new_node->next = current_node;
	new_node->data = data;
	
	current_node->prev->next = new_node;
	current_node->prev = new_node;
	
	return NodeToIter(new_node);
}

dl_iter_t DLRemove(dl_iter_t dl_iter)
{
	dl_node_t *current_node = IterToNode(dl_iter);
	
	assert(IterToNode(dl_iter));
	
	dl_iter = DLNext(dl_iter);
	
	current_node->prev->next = current_node->next;
	current_node->next->prev = current_node->prev;
	
	free(current_node);
	current_node = NULL;
	
	return dl_iter;
}

dl_iter_t DLPushBack(dlist_t *dlist, void *data)
{
	assert(dlist);
	
	return DLInsert(DLEnd(dlist), data);
}

dl_iter_t DLPushFront(dlist_t *dlist, void *data)
{
	assert(dlist);
	
	return DLInsert(DLBegin(dlist), data);
}

void *DLPopBack(dlist_t *dlist)
{
	void *data = NULL;
	dl_iter_t removed_iter;
	
	assert(dlist);
	
	removed_iter = NodeToIter((IterToNode(DLEnd(dlist))->prev));
	data = DLGetData(removed_iter);
	DLRemove(removed_iter);
	
	return data;
}

void *DLPopFront(dlist_t *dlist)
{
	void *data = NULL;
	
	assert(dlist);
	
	data = DLGetData(DLBegin(dlist));
	DLRemove(DLBegin(dlist));
	
	return data;
}

void DLSplice(dl_iter_t dest, dl_iter_t src_from, dl_iter_t src_to)
{
	dl_node_t *from_node;
	dl_node_t *to_node;
	dl_node_t *dest_node;
	dl_node_t *fromprev_node;
	
	assert(IterToNode(dest));
	assert(IterToNode(src_from));
	assert(IterToNode(src_to));
	
	from_node = IterToNode(src_from);
	to_node = IterToNode(src_to);
	dest_node = IterToNode(dest);
	fromprev_node = from_node->prev;
	
	from_node->prev->next = to_node;
	
	dest_node->prev->next = from_node;
	from_node->prev = dest_node->prev;
	
	dest_node->prev = to_node->prev;
	to_node->prev->next = dest_node;
	
	to_node->prev =fromprev_node;
}

int DLForEach(dl_iter_t from, dl_iter_t to,int (*action)(void *data, void *param), void *param)
{
	int status = 0;
	
	assert(IterToNode(from));
	assert(IterToNode(to));
	assert(param);
	assert(action);

	while((!DLIsIterEqual(from, to)) && !status)
	{
		status = action(IterToNode(from)->data, param);
		from = DLNext(from);
	}
	
	return status;	
}

dl_iter_t DLFind(dl_iter_t from, dl_iter_t to, const void *data,int (*is_match)(const void *, const void *))
{
	assert(IterToNode(from));
	assert(IterToNode(to));
	assert(data);
	assert(is_match);
	
	while(!DLIsIterEqual(from, to))
	{
		if (is_match(data, DLGetData(from)))
		{
			break;
		}
		from = DLNext(from);
	}
	
	return from;
}

int DLMultiFind(dl_iter_t from, dl_iter_t to, dlist_t *dest,const void *data, int(*is_match)(const void *, const void *))
{
	assert(dest);
	assert(IterToNode(from));
	assert(IterToNode(to));
	assert(data);
	assert(is_match);
	
	while(!DLIsIterEqual(from, to))
	{
		if (is_match(data, DLGetData(from)))
		{
			if(DLIsIterEqual(DLEnd(dest), DLPushBack(dest, DLGetData(from))))
			{
				return 1;
			}
		}
		
		from = DLNext(from);
	}
	
	return 0;
}

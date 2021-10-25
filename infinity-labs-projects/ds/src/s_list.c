#include <stdlib.h>	/*malloc free*/
#include <assert.h> /* assert*/

#include "s_list.h"

#define NODE_P_TO_ITER(node_pointer) (node_pointer)
#define ITER_TO_NODE_P(iter) (iter)
#define FIND_END(iter) while(ITER_TO_NODE_P(iter)->next){ iter = SLNext(iter);}

typedef struct sl_node
{
    void *data;
    struct sl_node *next;
    
} sl_node_t;


struct slist 
{
    sl_node_t *head;
    sl_node_t *end;
};


slist_t *SLCreate()
{
	slist_t *list = (slist_t *)malloc(sizeof(slist_t));
	sl_node_t *end = (sl_node_t *)malloc(sizeof(sl_node_t));
	
	if (!(list && end))
    {
        free(end); end = NULL;
        free(list); list = NULL;
        return NULL;
    }
	
	end->next = NULL;
	end->data = &(list->end);
	
	list->head = end;
	list->end = end;
	
	return list;
}

void SLDestroy(slist_t *list)
{
	sl_iter_t iter = NULL;
	assert(list);
	
	while(!SLIsEmpty(list))
    {
        iter = SLBegin(list);
        SLRemove(iter);
    }
	
	free(list->end);
	list->end = NULL;

	free(list);
	list = NULL;
}

sl_iter_t SLBegin(const slist_t *list)
{
	assert(list);
	return NODE_P_TO_ITER(list->head);
}

sl_iter_t SLEnd(const slist_t *list)
{
	assert(list);
	return NODE_P_TO_ITER(list->end);
}

sl_iter_t SLNext(const sl_iter_t iter)
{
	assert(iter);
	return NODE_P_TO_ITER(iter->next);
}

int SLIterIsEqual(const sl_iter_t iter1, const sl_iter_t iter2)
{
	assert(iter1 && iter2);
	return (iter1 == iter2);
}


size_t SLCount(const slist_t *list)
{
	size_t count = 0;
	sl_iter_t iter = NULL;
    assert(list);
    
	iter = SLBegin(list);
    while (iter != SLEnd(list))
    {
        iter = SLNext(iter);
        count++;
    }

	return count;
}

int SLIsEmpty(const slist_t *list)
{
	assert(list);
    return SLBegin(list) == SLEnd(list);
}

void *SLGetValue(const sl_iter_t iter)
{
	assert(iter);
	return ITER_TO_NODE_P(iter)->data;
}

void SLSetValue(sl_iter_t iter, void *data)
{
	assert(iter);
	ITER_TO_NODE_P(iter)->data = data;
}

sl_iter_t SLAddAfter(sl_iter_t iter, void *data)
{
	return SLAddBefore(SLNext(iter), data);
}

sl_iter_t SLAddBefore(sl_iter_t iter, void *data)
{
	sl_node_t *current_node = NULL;
	sl_node_t *new_node = (sl_node_t *)malloc(sizeof(sl_node_t));
	
	assert(iter);
    if (!new_node)
    {
        FIND_END(iter); 
        return iter;
    }
    
    current_node = ITER_TO_NODE_P(iter);

    new_node->data = current_node->data;
    new_node->next = current_node->next;
    current_node->next = new_node;
    current_node->data = data;
    
    if(new_node->next == NULL)
    {
    	/*Updating the end member*/
    	*(sl_iter_t *)new_node->data = NODE_P_TO_ITER(current_node->next); 
    }
    
    return NODE_P_TO_ITER(current_node);
}

sl_iter_t SLRemoveAfter(sl_iter_t iter)
{
	assert(iter && SLNext(iter));
    return SLRemove(SLNext(iter));
}
sl_iter_t SLRemove(sl_iter_t iter)
{
	sl_node_t *removed_node = NULL, *current_node = NULL;
	
	assert(iter && SLNext(iter));
	current_node = ITER_TO_NODE_P(iter);
	removed_node = ITER_TO_NODE_P(SLNext(iter));
	
	current_node->data = removed_node->data;
	current_node->next = removed_node->next;
	
	free(removed_node);
	removed_node = NULL;
	
	if(current_node->next == NULL)
	{
		/*Updating the end member*/
		*(sl_iter_t *)current_node->data = NODE_P_TO_ITER(current_node);
	}
	
	return NODE_P_TO_ITER(current_node);
}

sl_iter_t SLFind(const slist_t *list, const void * data, int (*CompareTo)(const void *, const void *))
{
	sl_iter_t begin = SLBegin(list);
	sl_iter_t end = SLEnd(list);
	sl_iter_t iter = NULL;
	int status = 1;
	
	for (iter = begin;!SLIterIsEqual(iter, end) && status; iter = SLNext(iter))
	{
		status = CompareTo(iter->data, data);
		
		if (!status)
		{
			return iter;
		}
	}

	return end;
}

int SLForEach(sl_iter_t start, sl_iter_t end, int (*Action)(void * data, void *param), void *param)
{
	sl_iter_t iter = start;
	int status = 0;
	
	for (iter = start;!SLIterIsEqual(iter, end) && !status; iter = SLNext(iter))
	{
		status = Action(iter->data, param);
	}
	
	return status;
}

void SLAppend(slist_t *base,  slist_t *append)
{
	base->end->data = append->head->data;
	base->end->next = append->head->next;
	base->end = append->end;
	base->end->data = &(base->end);
	
	append->end = append->head;
	append->head->data = &(append->end);
	append->head->next = NULL;
	
}

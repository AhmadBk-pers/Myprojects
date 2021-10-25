#include <stdlib.h>	/*malloc free*/
#include <assert.h> /* assert*/

#include "s_list.h"
#include "queue.h"

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

struct queue
{
    slist_t *q_list;
};

queue_t *QCreate()
{
	queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
	
	if (!(queue))
    {
        free(queue); 
        queue = NULL;
        
        return NULL;
    }
    
	queue->q_list = SLCreate();
	
	if (!(queue->q_list))
    {
       	free(queue); 
        queue = NULL;
        
        return NULL;
    }
    
	return queue;
}

void QDestroy(queue_t *queue)
{
	assert(queue);
	
	SLDestroy(queue->q_list);
	
	free(queue); 
    queue = NULL;
}

int QIsEmpty(const queue_t *queue)
{
	assert(queue);
	
	return SLIsEmpty(queue->q_list);
}

size_t QGetSize(const queue_t *queue)
{
	assert(queue);
	
	return SLCount(queue->q_list);
}

int QEnqueue(queue_t *queue, void *data)
{
	assert(queue);
	
	return !(SLAddBefore(queue->q_list->end, data)->next);
}

void *QDequeue(queue_t *queue)
{
	void *data = NULL;
	assert(queue);
	
	data = queue->q_list->head->data;
	SLRemove(queue->q_list->head);
	
	return data;
}

void *QPeek(const queue_t *queue)
{
	assert(queue);
	
	return queue->q_list->head->data;
}

void QAppend(queue_t *base, queue_t *append)
{
	assert(base);
	assert(append);
	
	SLAppend(base->q_list, append->q_list);
}

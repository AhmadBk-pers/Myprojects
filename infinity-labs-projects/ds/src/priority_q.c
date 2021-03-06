/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      ---
* Description   Priority queue heap implimintation module
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/

#include <assert.h> /* assert() */
#include <stdlib.h> /* malloc() */

#include "priority_q.h"		/*Priority q API*/
#include "heap.h"

struct priority_q
{
    heap_t *heap;
};

pq_t *PQCreate(int (*prioritize)(const void *data1, const void *data2))
{
	pq_t *prior_q = (pq_t *)malloc(sizeof(pq_t));
	
	if(!(prior_q))
	{
		return NULL;
	}
	
	assert(prioritize);
	
	prior_q->heap = HeapCreate(prioritize);
	
	if(!(prior_q->heap))
	{
		free(prior_q);
		prior_q = NULL;
		
		return NULL;
	}
	
	return prior_q;
}

void PQDestroy(pq_t *prior_q)
{
	assert(prior_q);
	
	HeapDestroy(prior_q->heap);
	
	free(prior_q);
	prior_q = NULL;
}

int PQIsEmpty(const pq_t *prior_q)
{
	assert(prior_q);
	
	return HeapIsEmpty(prior_q->heap);
}

size_t PQSize(const pq_t *prior_q)
{
	assert(prior_q);
	
	return HeapSize(prior_q->heap);
}

int PQEnqueue(pq_t *prior_q, void *data)
{
	assert(prior_q);
	
	return HeapPush((prior_q->heap), data);
}

void *PQDequeue(pq_t *prior_q)
{
	assert(prior_q);
	
	return HeapPop(prior_q->heap);
}

void *PQPeek(const pq_t *prior_q)
{
	assert(prior_q);
	
	return HeapPeek(prior_q->heap);	
}

void *PQErase(pq_t *prior_q, const void *data)
{
	assert(prior_q);

	return HeapRemove(prior_q->heap, data);
}

void *PQEraseIf(pq_t *prior_q, const void *criteria, int (*is_match)(const void *data, const void *criteria))
{
	assert(prior_q);
	
	return HeapRemoveIf(prior_q->heap, criteria, is_match);
}

void PQClear(pq_t *prior_q)
{
	assert(prior_q);
	
	while(!PQIsEmpty(prior_q))
	{
		PQDequeue(prior_q);
	}
}

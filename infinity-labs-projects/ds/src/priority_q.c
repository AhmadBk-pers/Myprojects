/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      ---
* Description   Priority q module
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/

#include <assert.h> /* assert() */
#include <stdlib.h> /* malloc() */

#include "priority_q.h"
#include "sorted_list.h"

struct priority_q
{
    sr_list_t *srlist;
};

pq_t *PQCreate(int (*prioritize)(const void *data1, const void *data2))
{
	pq_t *prior_q = (pq_t *)malloc(sizeof(pq_t));
	
	if(!(prior_q))
	{
		return NULL;
	}
	
	assert(prioritize);
	
	prior_q->srlist = SortedLCreate(prioritize);
	
	if(!(prior_q->srlist))
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
	
	SortedLDestroy(prior_q->srlist);
	
	free(prior_q);
	prior_q = NULL;
}

int PQIsEmpty(const pq_t *prior_q)
{
	assert(prior_q);
	
	return SortedLIsEmpty(prior_q->srlist);
}

size_t PQSize(const pq_t *prior_q)
{
	assert(prior_q);
	
	return SortedLSize(prior_q->srlist);
}

int PQEnqueue(pq_t *prior_q, void *data)
{
	assert(prior_q);
	
	return SortedLIsIterEqual(SortedLEnd(prior_q->srlist), SortedLInsert((prior_q->srlist), data));
}

void *PQDequeue(pq_t *prior_q)
{
	assert(prior_q);
	
	return SortedLPopBack(prior_q->srlist);
}

void *PQPeek(const pq_t *prior_q)
{
	assert(prior_q);
	
	return SortedLGetData(SortedLPrev(SortedLEnd(prior_q->srlist)));	
}

void *PQErase(pq_t *prior_q, const void *data)
{
	sr_iter_t iter = {0};
	
	assert(prior_q);
	
	iter = SortedLFind(SortedLBegin(prior_q->srlist), SortedLEnd(prior_q->srlist), data, prior_q->srlist);
	
	if(!SortedLIsIterEqual(SortedLEnd(prior_q->srlist), iter))
	{
		void *return_data = SortedLGetData(iter);
		SortedLRemove(iter);
		
		return return_data;
	}
	else
	{
		return NULL;
	}
}

void *PQEraseIf(pq_t *prior_q, const void *criteria, int (*is_match)(const void *data, const void *criteria))
{
	sr_iter_t iter = {0};
	
	assert(prior_q);
	
	iter = SortedLFindIf(SortedLBegin(prior_q->srlist), SortedLEnd(prior_q->srlist), criteria, is_match);
	
	if(!SortedLIsIterEqual(SortedLEnd(prior_q->srlist), iter))
	{
		void *return_data = SortedLGetData(iter);
		SortedLRemove(iter);
		
		return return_data;
	}
	else
	{
		return NULL;
	}
}

void PQClear(pq_t *prior_q)
{
	assert(prior_q);
	
	while(!PQIsEmpty(prior_q))
	{
		PQDequeue(prior_q);
	}
}

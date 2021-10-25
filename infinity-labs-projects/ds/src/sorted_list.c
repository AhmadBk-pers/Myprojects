/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      Fania
* Description   Sorted_List module
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/

#include <assert.h> /* assert() */
#include <stdlib.h> /* malloc() */
#include "sorted_list.h"

#define GET_ITER(iter) (iter.dl_iter)
#define GET_NODE(iter) (iter.dl_iter.internal)

struct sorted_list
{
    dlist_t *dlist;
    int (*compare)(const void *d1, const void *d2);
};

sr_list_t *SortedLCreate(int (*compare)(const void *d1, const void *d2))
{
	sr_list_t *srlist = (sr_list_t *)malloc(sizeof(sr_list_t));
	if(NULL == srlist)
	{
		return NULL;
	}
	
	assert(compare);
	
	srlist->compare = compare;
	srlist->dlist = DLCreate();
	if(NULL == srlist->dlist)
	{
		free(srlist);
		srlist = NULL;
		
		return NULL;
	}
	
	return srlist;
}

void SortedLDestroy(sr_list_t *srlist)
{
	assert(srlist);
	
	DLDestroy(srlist->dlist);
	srlist->dlist = NULL;
	
	free(srlist);
	srlist = NULL;
}

void *SortedLGetData(sr_iter_t iter)
{
	assert(GET_NODE(iter));
	
	return DLGetData(GET_ITER(iter));
}

sr_iter_t SortedLBegin(const sr_list_t *srlist)
{
	sr_iter_t iter = {0};
	
	assert(srlist);
	
	iter.dl_iter = DLBegin(srlist->dlist);
	
#ifndef NDEBUG
    iter.origin_list = srlist;
#endif /* NDEBUG */
	
	return iter;
}

sr_iter_t SortedLEnd(const sr_list_t *srlist)
{
	sr_iter_t iter = {0};
	
	assert(srlist);
	
	iter.dl_iter = DLEnd(srlist->dlist);
	
#ifndef NDEBUG
    iter.origin_list = srlist;
#endif /* NDEBUG */
		
	return iter;
}

sr_iter_t SortedLNext(sr_iter_t iter)
{
	assert(GET_NODE(iter));
	
	iter.dl_iter = DLNext(iter.dl_iter);
	
	return iter;
}

sr_iter_t SortedLPrev(sr_iter_t iter)
{
	assert(GET_NODE(iter));
	
	iter.dl_iter = DLPrev(iter.dl_iter);
	
	return iter;
}

int SortedLIsIterEqual(sr_iter_t i1, sr_iter_t i2)
{
	assert(GET_NODE(i1));
	assert(GET_NODE(i2));
	
	return DLIsIterEqual(GET_ITER(i1), GET_ITER(i2));
}

size_t SortedLSize(const sr_list_t *srlist)
{
	assert(srlist);
	
	return DLSize(srlist->dlist);
}

int SortedLIsEmpty(const sr_list_t *srlist)
{
	assert(srlist);
	
	return DLIsEmpty(srlist->dlist);
}

sr_iter_t SortedLInsert(sr_list_t *srlist, void *data)
{
	sr_iter_t iter = {0}, end = {0};

	assert(srlist);
	
	iter = SortedLBegin(srlist);
	end = SortedLEnd(srlist);
	
	while(!SortedLIsIterEqual(iter, end) && ((srlist->compare(SortedLGetData(iter), data)) < 0))
	{
		iter = SortedLNext(iter);
	}
	
	iter.dl_iter = DLInsert(GET_ITER(iter), data);
	
#ifndef NDEBUG
    iter.origin_list = srlist;
#endif /* NDEBUG */
	
	return iter;
}

sr_iter_t SortedLRemove(sr_iter_t iter)
{
	assert(GET_NODE(iter));
	
	iter.dl_iter = DLRemove(GET_ITER(iter));
	
	return iter;
}

void *SortedLPopBack(sr_list_t *srlist)
{
	assert(srlist);
	
	return DLPopBack(srlist->dlist);
}

void *SortedLPopFront(sr_list_t *srlist)
{
	assert(srlist);
	
	return DLPopFront(srlist->dlist);
}

sr_iter_t SortedLFindIf(sr_iter_t from, sr_iter_t to, 
    const void *data, int (*is_match)(const void *, const void *))
{
	sr_iter_t iter = {0};
	
	assert(GET_NODE(from));
	assert(GET_NODE(to));
	assert(is_match);
    assert(from.origin_list == to.origin_list);
	
	iter.dl_iter = DLFind(GET_ITER(from), GET_ITER(to), data, is_match);
	
#ifndef NDEBUG
    iter.origin_list = from.origin_list;
#endif /* NDEBUG */
	
	return iter;
}
    
sr_iter_t SortedLFind(sr_iter_t from, sr_iter_t to, 
    const void *data, sr_list_t *srlist)
{
	assert(GET_NODE(from));
	assert(GET_NODE(to));
	assert(data);
	assert(srlist);
    assert(from.origin_list == to.origin_list);
	
	while(!SortedLIsIterEqual(from, to) && (srlist->compare(data, SortedLGetData(from))))
	{
		from = SortedLNext(from);
	}
	
	return from;
}

int SortedLForEach(sr_iter_t from, sr_iter_t to,
    int (*action)(void *data, void *param), void *param)
{
	assert(GET_NODE(from));
	assert(GET_NODE(to));
	assert(action);
	assert(param);
    assert(from.origin_list == to.origin_list);
	
	return DLForEach(GET_ITER(from), GET_ITER(to), action, param);
}

void SortedLMerge(sr_list_t *dest, sr_list_t *src)
{
	sr_iter_t src_iter = {0}, src_end = {0}, dest_iter = {0}, dest_end = {0}, from_iter = {0};

	assert(dest);
	assert(src);
	
	src_iter = SortedLBegin(src);
	src_end = SortedLEnd(src);
	dest_iter = SortedLBegin(dest);
	dest_end = SortedLEnd(dest);

	while(!SortedLIsIterEqual(dest_iter, dest_end))
	{
		if ((dest->compare(SortedLGetData(dest_iter), SortedLGetData(src_iter))) > 0)
		{
			from_iter = src_iter;
			
			while(((dest->compare(SortedLGetData(dest_iter), SortedLGetData(src_iter))) > 0) && !SortedLIsIterEqual(src_iter, src_end))
			{
				src_iter = SortedLNext(src_iter);
			}
			
			DLSplice(GET_ITER(dest_iter), GET_ITER(from_iter), GET_ITER(src_iter));
			
		}
		dest_iter = SortedLNext(dest_iter);
	}
	
	if(!SortedLIsIterEqual(src_iter, src_end))
	{
		DLSplice(GET_ITER(dest_end), GET_ITER(src_iter), GET_ITER(src_end));
	}
}

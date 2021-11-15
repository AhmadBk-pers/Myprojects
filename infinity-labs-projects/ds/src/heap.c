/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      ---
* Description   Heap modules
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/
#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "d_vector.h" /* heap vector */
#include "heap.h"     /* heap API*/

#define INITIAL_SIZE 3

struct heap
{
    int (*compare)(const void *, const void*); /* MIN or MAX heap */
    vector_t *vec;
};

struct vector
{
	void **base_ptr;
	size_t size;
	size_t capacity;
};


static size_t FloatMember(heap_t *heap, size_t index);
static void HeapSwap(heap_t *heap, size_t index1, size_t index2);
static int HeapCompare(heap_t *heap, size_t index1, size_t index2);
static void SinkMember(heap_t *heap, size_t index);
static size_t GetChildIndex(heap_t *heap, size_t index);
static void *HeapRemoveIndex(heap_t *heap, size_t index);
static size_t GetLeftChild(size_t index);
static size_t GetRightChild(size_t index);
static size_t GetParent(size_t index);


heap_t *HeapCreate(compare_t compare)
{
    heap_t *heap = NULL;

    assert(compare);

    heap = (heap_t *)malloc(sizeof(heap_t));
    if (NULL == heap)
    {
        return NULL;
    }

    heap->vec = DVectorCreate(INITIAL_SIZE);
    if (NULL == heap->vec)
    {
        free(heap);
        heap = NULL;

        return NULL;
    }

    heap->compare = compare;

    return heap;
}

void HeapDestroy(heap_t *heap)
{
    assert(heap);

    DVectorDestroy(heap->vec);
    
    free(heap);
    heap = NULL;
}

int HeapIsEmpty(const heap_t *heap)
{
    assert(heap);

    return 0 == HeapSize(heap);
}

size_t HeapSize(const heap_t *heap)
{
    assert(heap);

    return DVectorGetSize(heap->vec);
}

int HeapPush(heap_t *heap, void *data)
{
    size_t index = 0;

    assert(heap);
    assert(data);

    if (DVectorPushBack(heap->vec, data))
    {
        return 1;
    }

    index = HeapSize(heap) - 1;

    index = FloatMember(heap, index);

    return 0;
}

static void SinkMember(heap_t *heap, size_t index)
{
    size_t child_index = 0;

    assert(heap);

    child_index = GetChildIndex(heap, index);
    if (!child_index)
    {
        return;
    }

    if (HeapCompare(heap, child_index, index) > 0)
    {
        HeapSwap(heap, index, child_index);
        SinkMember(heap, child_index);
    }
}

static size_t GetChildIndex(heap_t *heap, size_t index)
{
    assert(heap);

    if (GetRightChild(index) >= HeapSize(heap))
    {
        if (GetLeftChild(index) >= HeapSize(heap))
        {
            return 0;
        }
        else
        {
            return index * 2 + 1;
        }
    }
    else
    {
        return (HeapCompare(heap, index * 2 + 1, index * 2 + 2) > 0) ? GetLeftChild(index) : GetRightChild(index);
    }
}

static size_t GetRightChild(size_t index)
{
    return (index * 2 + 2);
}

static size_t GetLeftChild(size_t index)
{
    return (index * 2 + 1);
}

static size_t GetParent(size_t index)
{
    return (index - 1) / 2;
}

static size_t FloatMember(heap_t *heap, size_t index)
{
    assert(heap);

    if ((index > 0) && HeapCompare(heap, index, GetParent(index)) > 0)
    {
        HeapSwap(heap, index, GetParent(index));
        return FloatMember(heap, GetParent(index));
    }

    return index;
}

static void HeapSwap(heap_t *heap, size_t index1, size_t index2)
{
    void *data = NULL;

    assert(heap);

    data = DVectorGet(heap->vec, index1);
    DVectorSet(heap->vec, index1, DVectorGet(heap->vec, index2));
    DVectorSet(heap->vec, index2, data);
}

static int HeapCompare(heap_t *heap, size_t index1, size_t index2)
{
    assert(heap);

    return heap->compare(DVectorGet(heap->vec, index1), DVectorGet(heap->vec, index2));
}

void *HeapPop(heap_t *heap)
{
    assert(heap);

    return HeapRemoveIndex(heap, 0);
}

static void *HeapRemoveIndex(heap_t *heap, size_t index)
{
    void *data = NULL;

    assert(heap);

    HeapSwap(heap, index, HeapSize(heap) - 1);
    
    data = DVectorPopBack(heap->vec);

    SinkMember(heap, index);

    return data;
}

void *HeapPeek(const heap_t *heap)
{
    assert(heap);
    
    return DVectorGet(heap->vec, 0);
}
                         
void *HeapRemove(heap_t *heap, const void *criteria)
{
    size_t index = 0, heap_size = 0;
    
	assert(heap);

    for (heap_size = HeapSize(heap); index < heap_size; index ++)
    {
        if (!heap->compare(criteria, DVectorGet(heap->vec, index)))
        {
            return HeapRemoveIndex(heap, index);
        }
    }	
	
    return NULL;
}

void *HeapRemoveIf(heap_t *heap, const void *criteria, int (*is_match)(const void *data, const void *criteria))
{	
    size_t index = 0, heap_size = 0;
    
	assert(heap);
    assert(is_match);

    for (heap_size = HeapSize(heap); index < heap_size; index ++)
    {
        if (is_match(criteria, DVectorGet(heap->vec, index)))
        {
            return HeapRemoveIndex(heap, index);
        }
    }	
	
    return NULL;
}

/*
void PrintHeap(heap_t *heap)
{
    int i = 0;

    for(i = 0; i < HeapSize(heap); i++)
    {
        printf("%d\t", *(int *)DVectorGet(heap->vec, i));

        if (i == 0 || i == 2 || i == 6 || i == 14 )
        {
            printf("\n");
        }
    }

    printf("\n");
}*/
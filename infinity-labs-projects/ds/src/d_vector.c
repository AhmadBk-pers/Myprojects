#include <stdlib.h>		/*malloc free*/
#include <assert.h>		/*assert*/
#include "d_vector.h"

#define GROWTHFACTOR 2

void StackCopy(void **dest_ptr, void **src_ptr, size_t n);

struct vector
{
	void **base_ptr;
	size_t size;
	size_t capacity;
};


vector_t *DVectorCreate(size_t capacity)
{
	vector_t *vector = (vector_t *)malloc(sizeof(vector_t));
	
	vector->base_ptr = malloc(capacity * sizeof(void *));
	vector->size = 0;
	vector->capacity = capacity;
	
	return vector;
}

void DVectorDestroy(vector_t *vector)
{
	free(vector->base_ptr);
	free(vector);
}

int DVectorPushBack(vector_t *vector, void *element)
{
	if (vector->size < vector->capacity)
	{
		vector->base_ptr[vector->size++] = element;
		return 0;
	}
	else
	{
		int status = DVectorReserve(vector, vector->capacity * GROWTHFACTOR);
		vector->base_ptr[vector->size++] = element;
		return status;
	}
	
}

void *DVectorPopBack(vector_t *vector)
{
	return vector->base_ptr[--vector->size];
}

void *DVectorGet(const vector_t *vector, size_t index)
{
	assert(index < vector->size);
	return vector->base_ptr[index];
}

void DVectorSet(vector_t *vector, size_t index, void *element)
{
	assert(index < vector->size);
	vector->base_ptr[index] = element;
}

size_t DVectorGetSize(const vector_t *vector)
{
	return vector->size;
}

size_t DVectorGetCapacity(const vector_t *vector)
{
	return vector->capacity;
}

int DVectorReserve(vector_t *vector, size_t new_capacity)
{
	void **temp_base_ptr = malloc(new_capacity * sizeof(void *));
	size_t min_copy = (new_capacity < vector->size) ? new_capacity : vector->size;
	
	if (temp_base_ptr)
	{
		StackCopy(temp_base_ptr, vector->base_ptr, min_copy);
		
		free(vector->base_ptr);
		
		vector->base_ptr = temp_base_ptr;
		
		vector->capacity = new_capacity;
		
		vector->size = min_copy;
		
		return 0;
	}
	
	return 1;
}

int DVectorShrinkToFit(vector_t *vector)
{
	return DVectorReserve(vector, vector->size);
}

void StackCopy(void **dest_ptr, void **src_ptr, size_t n)
{
	size_t i = 0;
	
	for (i = 0; i < n; i++)
	{
		dest_ptr[i] = src_ptr[i];
	}
}


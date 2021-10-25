/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      tzi
* Description   Fixed Size Allocator module
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/
#include <assert.h>     /* assert */

#include "fsa.h"

#define WORD_SIZE sizeof(size_t)

static size_t *GetSizeLocation(const fsa_t fsa)
{
	assert(fsa);
	
	return (size_t *)fsa + 1;
}

fsa_t FSAInit(void *mem_pool, size_t pool_size, size_t block_size)
{
	size_t alligned_block_words = ((WORD_SIZE - (block_size % WORD_SIZE)) + block_size) / WORD_SIZE;
	size_t count = 0;
	size_t blocks_num = (pool_size - (sizeof(void *) + sizeof(size_t)))/(alligned_block_words * WORD_SIZE);
	size_t *init_ptr = mem_pool;
	
	*init_ptr++ = (size_t)2;
	*init_ptr++ = blocks_num;
	
	for (count = 0; count < blocks_num - 1; count++)
	{
		*init_ptr = (2 + ((count + 1) * alligned_block_words));
		init_ptr = (size_t *)mem_pool + (*init_ptr);
	}
	
	*init_ptr = (size_t)0;
	
	return (fsa_t)mem_pool;
}

void *FSAAlloc(fsa_t fsa)
{
	size_t allocated_memory_offset = 0;
	size_t *allocated_memory = NULL;
	
	assert(fsa);
	
	allocated_memory_offset = (*(size_t *)fsa);
	
	if (allocated_memory_offset)
	{
		allocated_memory = (size_t *)fsa + allocated_memory_offset;
		*(size_t *)fsa = *allocated_memory;
		*GetSizeLocation(fsa) -= 1;
	}
	
	return allocated_memory;
}

void FSAFree(fsa_t fsa, void *block)
{
	assert(fsa);
	assert(block);
	
	*(size_t *)block = *(size_t *)fsa;
	*(size_t *)fsa = (size_t *)block - (size_t *)fsa;
	*GetSizeLocation(fsa) += 1;
}

size_t FSASuggestSize(size_t num_of_blocks, size_t block_size)
{
	return (sizeof(void *) + sizeof(size_t) + (((block_size / WORD_SIZE) + ((block_size % WORD_SIZE) != 0)) * num_of_blocks * WORD_SIZE));
}

size_t FSACountFree(const fsa_t fsa)
{
	assert(fsa);
	
	return *GetSizeLocation(fsa);
}

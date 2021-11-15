/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      Ron
* Description   Variable Size Allocator module
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/

#include <assert.h> /* assert */
#include <limits.h> /* __WORDSIZE, CHAR_BIT */
#include "vsa.h"


struct vsa
{
	size_t size;
};

struct block
{
	long size;
	
#ifndef NDEBUG
	long flag;
#endif /* NDEBUG */
};

typedef struct block block_t;


static const size_t g_WORD_SIZE = __WORDSIZE / CHAR_BIT;
static const int FLAG  = 0xDEADBEAF;


static size_t GetFreeBlockOffset(vsa_t *vsa, size_t bytes);
static size_t LocalDefrag(vsa_t *vsa, size_t offset);

static size_t AllignUpToWord(size_t size);
static size_t AllignDownToWord(size_t size);
static long Absolute(long num);
static long Max(long a, long b);
static size_t GetTotalCells(vsa_t *vsa);

int BlockIsFree(block_t *block);
void BlockSetFree(block_t *block);


vsa_t *VSAInit(void *pool_memory, size_t pool_size)
{
	vsa_t *vsa = NULL;
	pool_size = AllignDownToWord(pool_size);
	
	assert(pool_memory != NULL);
	assert(pool_size >= g_WORD_SIZE);
	
	if (pool_size >= g_WORD_SIZE + sizeof(block_t))
	{
		block_t *block = NULL;
		
		vsa = (vsa_t *)pool_memory;
		vsa->size = pool_size;
		
		block = (block_t *)(vsa + 1);
		block->size = pool_size - g_WORD_SIZE;
	}
	
	return vsa;
}


void *VSAAlloc(vsa_t *vsa, size_t bytes)
{
	size_t offset = 0;
	block_t *block = NULL;
	
	assert(vsa != NULL);
	
	bytes = AllignUpToWord(bytes) + sizeof(block_t);
	offset = GetFreeBlockOffset(vsa, bytes);
	
	if (0 == offset)
	{
		return NULL;
	}
	
	block = (block_t *)(vsa + offset);
	
	/* case of taking just part of free block - update next free */
	if ((long)bytes < block->size)
	{
		block_t *next_free = (block_t *)(vsa + offset + bytes / g_WORD_SIZE);
		
		next_free->size = block->size - bytes;
	}
	
	block->size = bytes * (-1);
#ifndef NDEBUG
	block->flag = FLAG;
#endif /* NDEBUG */
	
	return (void*)(vsa + offset + sizeof(block_t) / g_WORD_SIZE);
}


static size_t GetFreeBlockOffset(vsa_t *vsa, size_t bytes)
{
	size_t total_size = 0;
	size_t offset = 0;
	
	assert (vsa != NULL);
	
	total_size = GetTotalCells(vsa);
	offset += sizeof(vsa) / g_WORD_SIZE;
	
	while (offset < total_size)
	{
		size_t curr = 0;
		block_t *block = NULL;
		
		block = (block_t *)(vsa + offset);
		curr = block->size; /* size before defrag */
		
		if (block->size >= 0 && curr < bytes)
		{
			LocalDefrag(vsa, offset);
			curr = block->size; /* size after defrag */
		}
		
		if (block->size >= 0 && curr >= bytes)
		{
			return offset;
		}
		
		offset += Absolute(curr) / g_WORD_SIZE;
	}
	
	return 0;
}


void VSAFree(void *block)
{
	assert(!BlockIsFree(block));
	assert( FLAG == ((block_t *)((size_t)block - sizeof(block_t)))->flag );
	
	BlockSetFree(block);
}


size_t VSALargestBlockAvailable(vsa_t *vsa)
{
	long max = 0;
	size_t total_size = 0;
	size_t offset = 0;
	
	assert(vsa != NULL);
	
	total_size = GetTotalCells(vsa);
	offset = sizeof(vsa) / g_WORD_SIZE;
	
	while (offset < total_size)
	{
		long curr = 0;
		
		LocalDefrag(vsa, offset);
		
		curr = ((block_t *)(vsa + offset))->size;
		max = Max(max, curr);
		
		offset += Absolute(curr) / g_WORD_SIZE;
	}
	
	return (0 == max) ? 0 : max - sizeof(block_t);
}


static size_t LocalDefrag(vsa_t *vsa, size_t offset)
{
	size_t origin_offset = offset;
	size_t total_size = GetTotalCells(vsa);
	long free_space_to_add = 0;
	
	offset += ((block_t *)(vsa + offset))->size / g_WORD_SIZE;
	
	while (offset < total_size)
	{
		long curr = ((block_t *)(vsa + offset))->size;
		
		if (curr <= 0)
		{
			break;
		}
		
		free_space_to_add += curr;
		offset += curr / g_WORD_SIZE;
	}
	
	((block_t *)(vsa + origin_offset))->size += free_space_to_add;
	
	return offset;
}




static size_t AllignUpToWord(size_t size)
{
	return (size % g_WORD_SIZE) ? size + g_WORD_SIZE - (size % g_WORD_SIZE) : size;
}


static size_t AllignDownToWord(size_t size)
{
	return size - (size % g_WORD_SIZE);
}


static long Absolute(long num)
{
	return (num < 0) ? (num * (-1)) : num;
}


static long Max(long a, long b)
{
	return (a > b) ? a : b;
}


static size_t GetTotalCells(vsa_t *vsa)
{
	return vsa->size / g_WORD_SIZE - 1;
}


int BlockIsFree(block_t *block)
{
	return ( (block_t *)((size_t)block - sizeof(block_t)) )->size >= 0;
}


void BlockSetFree(block_t *block)
{
	( (block_t *)((size_t)block - sizeof(block_t)) )->size *= (-1);
}






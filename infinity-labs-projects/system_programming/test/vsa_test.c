#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include "vsa.h"


#define _RED_ printf("\033[1;31m")
#define _GREEN_ printf("\033[1;32m")
#define _YELLOW_ printf("\033[1;33m")
#define _PURPLE_ printf("\033[1;35m")
#define _CYAN_ printf("\033[1;36m")
#define _WHITE_ printf("\033[0m")
#define PRINT_POOL(pool, pool_size) /*PrintPool(pool, pool_size)*/


void TestInitiatedFsa(void);
void TestDirtyFsa(void);
void TestVsaFollowingFrees(void);
void TestFsaDebugMode(void);
void TestVsaEmpty(void);


static void PrintPool(vsa_t *pool, size_t pool_size);
static size_t AllignUpToWord(size_t size);
static size_t AllignDownToWord(size_t size);
static size_t ManageSize(void);


void TestVsaInit(void *pool, size_t pool_size);
void TestVsaAllocAndFree(void *pool, size_t pool_size);
void TestVsaFreeMuchBlocks(void *pool, size_t pool_size);
void TestVsaDebugAllocAndFree(void *pool, size_t pool_size);
void *TestSomeAlloc(vsa_t *vsa, size_t bytes, long val, size_t prev_frees);
void TestSomeFree(vsa_t *vsa, void *block, size_t exp_max_free);


void PrintResultsInt (int, int);
void PrintResultsLong (char*, size_t, size_t);


static const size_t WORD_SIZE = sizeof(void*);


int main()
{
#ifdef NDEBUG
	TestInitiatedFsa();
	TestDirtyFsa();
	TestVsaFollowingFrees();
#endif /* if NDEBUG */

#ifndef NDEBUG
	TestFsaDebugMode();
#endif /* if not NDEBUG */

	TestVsaEmpty();
	
	printf("\n");
	return 0;
}



void *TestSomeAlloc(vsa_t *vsa, size_t bytes, long val, size_t prev_frees)
{
	void *block = VSAAlloc(vsa, bytes);
	size_t exp_frees = prev_frees - AllignUpToWord(bytes) - ManageSize();
	*(size_t*)block = (size_t)val;
	PrintResultsLong("free_bytes", VSALargestBlockAvailable(vsa), exp_frees);
	
	return block;
}


void TestSomeFree(vsa_t *vsa, void *block, size_t exp_max_free)
{
	VSAFree(block);
	PrintResultsLong("free_bytes", VSALargestBlockAvailable(vsa), exp_max_free);
}


void TestVsaInit(void *pool, size_t pool_size)
{
	vsa_t *vsa = NULL;
	vsa = VSAInit(pool, pool_size);
	PrintResultsLong("free_bytes", VSALargestBlockAvailable(vsa), 0);
	PRINT_POOL(pool, pool_size);
}


void TestVsaAllocAndFree(void *pool, size_t pool_size)
{
	vsa_t *vsa = NULL;
	void *block2 = NULL, *block3 = NULL;
	size_t size = AllignDownToWord(pool_size);
	size_t s0 = 0, s1 = 0, s2 = 0, s3 = 0, s4 = 0;
	
	/* Init */
	vsa = VSAInit(pool, pool_size);
	
	PRINT_POOL(pool, pool_size);
	s0 = size - WORD_SIZE - ManageSize();
	PrintResultsLong("free_bytes", VSALargestBlockAvailable(vsa), s0);
	
	/* Alloc */
	TestSomeAlloc(vsa, 10, 1, s0);
	s1 = s0 - AllignUpToWord(10) - ManageSize();
	
	block2 = TestSomeAlloc(vsa, 5, 2, s1);
	s2 = s1 - AllignUpToWord(5) - ManageSize();
	
	block3 = TestSomeAlloc(vsa, 20, 3, s2);
	s3 = s2 - AllignUpToWord(20) - ManageSize();
	
	TestSomeAlloc(vsa, 10, 4, s3);
	s4 = s3 - AllignUpToWord(10) - ManageSize();
	
	PRINT_POOL(pool, pool_size);
	
	/* Free */
	PrintResultsLong("free_bytes", VSALargestBlockAvailable(vsa), 16);
	
	printf("free(1):\n");
	TestSomeFree(vsa, block2, s4);
	PRINT_POOL(pool, pool_size);
	
	printf("free(2):\n");
	TestSomeFree(vsa, block3, s3);
	PRINT_POOL(pool, pool_size);
	
	/* inner Alloc */
	printf("alloc:\n");
	block2 = VSAAlloc(vsa, 40);
	*(size_t*)block2 = (size_t)9;
	PRINT_POOL(pool, pool_size);
	
	printf("\nfind biggest:\n");
	PrintResultsLong("free_bytes", VSALargestBlockAvailable(vsa), s4);
	PRINT_POOL(pool, pool_size);
}


void TestVsaFreeMuchBlocks(void *pool, size_t pool_size)
{
	vsa_t *vsa = NULL;
	size_t size = AllignDownToWord(pool_size);
	
	void *block[7] = {0};
	size_t s[7] = {0};
	
	size_t fix_bytes = 16;
	int i = 0;
	
	/* Init */
	vsa = VSAInit(pool, pool_size);
	
	PRINT_POOL(pool, pool_size);
	s[0] = size - WORD_SIZE - ManageSize();
	PrintResultsLong("free_bytes", VSALargestBlockAvailable(vsa), s[0]);
	
	/* Alloc */
	for (i = 0; i < 6; i++)
	{
		block[i + 1] = TestSomeAlloc(vsa, fix_bytes, i + 1, s[i]);
		s[i + 1] = s[i] - AllignUpToWord(fix_bytes) - ManageSize();
	}
	
	/* Free */
	printf("\nbefore free:");
	PRINT_POOL(pool, pool_size);
	
	i = 2;
	printf("\nfree(%d):\n", i);
	s[7 - i] = s[8 - i] + fix_bytes;
	TestSomeFree(vsa, block[i], s[7 - i]);
	
	for (i = 3; i < 6; i++)
	{
		printf("\nfree(%d):\n", i);
		s[7 - i] = s[8 - i] + fix_bytes + WORD_SIZE;
		TestSomeFree(vsa, block[i], s[7 - i]);
		PRINT_POOL(pool, pool_size);
	}
	
	/* inner Alloc */
	printf("alloc:\n");
	block[2] = TestSomeAlloc(vsa, fix_bytes, 9, s[2]);
	PRINT_POOL(pool, pool_size);
	
	printf("free(6):\n");
	TestSomeFree(vsa, block[6], s[2]);
	PRINT_POOL(pool, pool_size);
}


void TestVsaDebugAllocAndFree(void *pool, size_t pool_size)
{
	vsa_t *vsa = NULL;
	void *block2 = NULL, *block3 = NULL;
	size_t size = AllignDownToWord(pool_size);
	size_t s0 = 0, s1 = 0, s2 = 0, s3 = 0, s4 = 0;
	
	/* Init */
	vsa = VSAInit(pool, pool_size);
	
	s0 = size - WORD_SIZE - ManageSize();
	PrintResultsLong("free_bytes", VSALargestBlockAvailable(vsa), s0);
	PRINT_POOL(pool, pool_size);
	
	/* Alloc */
	printf("start alloc:\n");
	TestSomeAlloc(vsa, 10, 1, s0);
	s1 = s0 - AllignUpToWord(10) - ManageSize();
	PRINT_POOL(pool, pool_size);
	
	block2 = TestSomeAlloc(vsa, 5, 2, s1);
	s2 = s1 - AllignUpToWord(5) - ManageSize();
	PRINT_POOL(pool, pool_size);
	
	block3 = TestSomeAlloc(vsa, 10, 3, s2);
	s3 = s2 - AllignUpToWord(10) - ManageSize();
	PRINT_POOL(pool, pool_size);
	
	TestSomeAlloc(vsa, 10, 4, s3);
	s4 = s3 - AllignUpToWord(10) - ManageSize();
	PRINT_POOL(pool, pool_size);
	
	/* Free */
	printf("free(1):\n");
	TestSomeFree(vsa, block2, 8);
	PRINT_POOL(pool, pool_size);
	
	printf("free(2):\n");
	TestSomeFree(vsa, block3, 40);
	PRINT_POOL(pool, pool_size);
	
	/* inner Alloc */
	printf("alloc:\n");
	block2 = VSAAlloc(vsa, 20);
	*(size_t*)block2 = (size_t)9;
	PRINT_POOL(pool, pool_size);
	
	PrintResultsLong("free_bytes", VSALargestBlockAvailable(vsa), s4);
	printf("\nfind biggest:\n");
	PRINT_POOL(pool, pool_size);
}



void TestInitiatedFsa()
{
	void *pool = NULL;
	size_t pool_size = 129;
	
	_PURPLE_;
	printf("\nTest - VSA (initiated)\n");
	_WHITE_;
	
	pool = calloc(pool_size, sizeof(char));
	
	TestVsaAllocAndFree(pool, pool_size);
	
	free(pool);
}


void TestDirtyFsa()
{
	void *pool = NULL;
	size_t pool_size = 129;
	
	_PURPLE_;
	printf("\nTest - VSA (not initiated)\n");
	_WHITE_;
	
	pool = malloc(pool_size * sizeof(char));
	
	TestVsaAllocAndFree(pool, pool_size);
	
	free(pool);
}


void TestVsaFollowingFrees()
{
	void *pool = NULL;
	size_t pool_size = 160;
	
	_PURPLE_;
	printf("\nTest - VSA following free blocks\n");
	_WHITE_;
	
	pool = calloc(pool_size, sizeof(char));
	
	TestVsaFreeMuchBlocks(pool, pool_size);
	
	free(pool);
}


void TestFsaDebugMode()
{
	void *pool = NULL;
	size_t pool_size = 149;
	
	_PURPLE_;
	printf("\nTest - VSA - Debug Mode\n");
	_WHITE_;
	
	pool = calloc(pool_size, sizeof(char));
	
	TestVsaDebugAllocAndFree(pool, pool_size);
	
	free(pool);
}


void TestVsaEmpty()
{
	void *pool = NULL;
	size_t pool_size = WORD_SIZE + WORD_SIZE;
	
#ifndef NDEBUG
	pool_size += WORD_SIZE;
#endif /* if not NDEBUG */
	
	_PURPLE_;
	printf("\nTest - VSA empty\n");
	_WHITE_;
	
	pool = calloc(pool_size, sizeof(char));
	
	TestVsaInit(pool, pool_size);
	
	free(pool);
}




static void PrintPool(vsa_t *pool, size_t pool_size)
{
	const size_t WORD_SIZE = 8;
	size_t i = 0;
	
	_YELLOW_;
	printf("%ld ", *(long*)pool);
	_WHITE_;
	(*(long**)&pool)++;
	
	for(; i < (pool_size / WORD_SIZE) - 1; i++)
	{
		long val = *(long*)pool;
		
		if (0xDEADBEAF == val)
		{
			_CYAN_;
			printf("%s ", "@@@");
			_WHITE_;
		}
		else
		{
			printf("%ld ", val);
		}
		
		(*(long**)&pool)++;
	}
	
	printf("\n\n");
}


static size_t AllignUpToWord(size_t size)
{
	return (size % WORD_SIZE) ? size + WORD_SIZE - (size % WORD_SIZE) : size;
}


static size_t AllignDownToWord(size_t size)
{
	return size - (size % WORD_SIZE);
}


static size_t ManageSize()
{
	size_t size = WORD_SIZE;
	
#ifndef NDEBUG
      size += WORD_SIZE;
#endif /* NDEBUG */
	
	return size;
}








void PrintResultsInt (int res, int expect)
{
	if (res == expect)
	{
		_GREEN_;
	}
	else
	{
		_RED_;
	}
	printf ("result: %d , expect: %d\n", res, expect);
	
	_WHITE_;
}


void PrintResultsLong (char *title, size_t res, size_t expect)
{
	if (res == expect)
	{
		_GREEN_;
	}
	else
	{
		_RED_;
	}
	printf ("%s: %ld , expect: %ld\n", title, res, expect);
	
	_WHITE_;
}


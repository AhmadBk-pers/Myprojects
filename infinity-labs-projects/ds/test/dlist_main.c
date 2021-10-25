/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      Shani
* Description   Doubly_Linked_List module
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/

# include <stdio.h> /* printf */
# include "dlist.h"


void TestDLCreateAndDestroy(void);
void TestDLInsertAndRemove(void);
void TestDLPushPopBackAndFront(void);
void TestDLFind(void);
void TestDLForEach(void);
void TestDLMultyFind(void);
void TestDLSplice(void);
void TestDLEmpty(void);


void TestArrayDLInsert(dlist_t*, int*, size_t);
void TestArrayDLRemove(dlist_t*, int*, size_t);
void TestSomeDLPeek(dl_iter_t, int);
void PrintList(dlist_t*, int*, size_t);


int IsMatch(const void*, const void*);
int IsModolu(const void*, const void*);
int IncAndPrint(void*, void*);
int PrintAster(void*, void*);


void PrintResultsInt (int, int);
void PrintResultsLong (char*, size_t, size_t);


int main()
{
	TestDLCreateAndDestroy();
	TestDLInsertAndRemove();
	TestDLPushPopBackAndFront();
	TestDLFind();
	TestDLForEach();
	TestDLMultyFind();
	TestDLSplice();
	
	printf("\n");
	return 0;
}



void TestArrayDLInsert(dlist_t *dlist, int *arr, size_t size)
{
	size_t i = 0;
	dl_iter_t iter = DLEnd(dlist);
	
	for (; i < size; i++)
	{
		iter = DLInsert(iter, (void*)(long)arr[i]);
		iter = DLNext(iter);
	}
}


void TestArrayDLRemove(dlist_t *dlist, int *arr, size_t size)
{
	size_t i = 0;
	dl_iter_t iter = DLBegin(dlist);
	
	for (; i < size; i++)
	{
		TestSomeDLPeek(iter, arr[i]);
		iter = DLRemove(iter);
	}
}


void TestSomeDLPeek(dl_iter_t iter, int expect)
{
	int result = (int)(long)DLGetData(iter);
	PrintResultsInt(result, expect);
}


void PrintList(dlist_t *dlist, int *expect, size_t size)
{
	size_t i = 0;
	
	for (; i < size; i++)
	{
		int result = (int)(long)DLPopFront(dlist);
		PrintResultsInt(result, expect[i]);
	}
}





void TestDLCreateAndDestroy()
{
	dlist_t *dlist = NULL;
	
	printf("\nTest - dlist Create & Destroy ...");
	
	dlist = DLCreate();
	DLDestroy(dlist);
	dlist = NULL;
	
	printf (" Passed!\n");
}


void TestDLInsertAndRemove()
{
	dlist_t *dlist = NULL;
	dl_iter_t iter;
	int values[] = {1,2,3,4};
	
	printf("\nTest - DL_List Insert & Remove\n");
	
	dlist = DLCreate();
	
	TestArrayDLInsert(dlist, values, 4);
	
	PrintResultsLong("size", DLSize(dlist), 4);
	PrintResultsLong("is_empty", DLIsEmpty(dlist), 0);
	
	TestArrayDLRemove(dlist, values, 4);
	
	PrintResultsLong("size", DLSize(dlist), 0);
	PrintResultsLong("is_empty", DLIsEmpty(dlist), 1);
	
	iter = DLInsert(DLBegin(dlist), (void*)(long)5);
	DLSetData(iter, (void*)(long)8);
	TestSomeDLPeek(iter, 8);
	
	DLDestroy(dlist);
	dlist = NULL;
}


void TestDLPushPopBackAndFront()
{
	dlist_t *dlist = NULL;
	void *val[8] = {0};
	size_t i = 0;
	
	printf("\nTest - DL_List Push & Pop - Back & Front\n");
	
	dlist = DLCreate();
	
	DLPushBack(dlist, (void*)(long)8);
	DLPushBack(dlist, (void*)(long)2);
	DLPushBack(dlist, (void*)(long)1);
	DLPushFront(dlist, (void*)(long)7);
	DLPushFront(dlist, (void*)(long)4);
	DLPushFront(dlist, (void*)(long)3);
	
	PrintResultsLong("size", DLSize(dlist), 6);
	
	val[1] = DLPopBack(dlist);
	val[2] = DLPopBack(dlist);
	val[3] = DLPopFront(dlist);
	val[4] = DLPopFront(dlist);
	
	DLPushBack(dlist, (void*)(long)5);
	DLPushFront(dlist, (void*)(long)6);
	
	val[5] = DLPopBack(dlist);
	val[6] = DLPopFront(dlist);
	
	for (i = 1; i < 7; i++)
	{
		PrintResultsInt((int)(long)val[i], i);
	}
	
	PrintResultsLong("size", DLSize(dlist), 2);
	
	DLDestroy(dlist);
	dlist = NULL;
}

void TestDLFind()
{
	dlist_t *dlist = NULL;
	dl_iter_t iter;
	dl_iter_t iters[10] = {0};
	size_t i = 0;
	
	printf("\nTest - DL_List Find\n");
	dlist = DLCreate();
	
	/* Insert */
	for (i = 0; i < 10; i++)
	{
		iters[i] = DLPushBack(dlist, (void*)i);
	}
	
	/* Find */
	iter = DLFind(iters[0], DLEnd(dlist),
					(void*)(long)5, IsMatch);
	TestSomeDLPeek(iter, 5);
	
	iter = DLFind(iters[4], iters[8], (void*)(long)4, IsMatch);
	TestSomeDLPeek(iter, 4);
	
	iter = DLFind(iters[4], iters[8], (void*)(long)8, IsMatch);
	TestSomeDLPeek(iter, 8);
	
	iter = DLFind(iters[4], iters[7], (void*)(long)9, IsMatch);
	TestSomeDLPeek(iter, 7);
	
	DLDestroy(dlist);
	dlist = NULL;
}

void TestDLForEach()
{
	dlist_t *dlist = NULL;
	dl_iter_t iters[10] = {0};
	size_t values[10] = {0};
	size_t i = 0;
	int error = 0;
	
	printf("\nTest - DL_List For Each\n");
	dlist = DLCreate();
	
	/* Insert */
	for (i = 0; i < 10; i++)
	{
		values[i] = i;
		iters[i] = DLPushBack(dlist, (size_t*)&values[i]);
	}
	
	/* For-each :
		increment by 2 all values in range & print them */
	error = DLForEach(iters[4], iters[8], IncAndPrint,
											(size_t*)2);
	PrintResultsLong("\nerror_value", error, 0);
	
	for (i = 4; i < 8; i++)
	{
		PrintResultsInt(*(int*)DLGetData(iters[i]), i + 2);
	}
	
	error = DLForEach(iters[4], iters[8], PrintAster, (void*)3);
	PrintResultsLong("\nerror_value", error, 1);
	
	DLDestroy(dlist);
	dlist = NULL;
}

void TestDLMultyFind()
{
	dlist_t *dlist = NULL, *res_list = NULL;
	size_t i = 0;
	int error = 0;
	
	printf("\nTest - DL_List Multy Find\n");
	dlist = DLCreate();
	res_list = DLCreate();
	
	/* Insert */
	for (i = 0; i < 100; i++)
	{
		DLPushBack(dlist, (void*)i);
	}
	
	/* Find */
	error = DLMultiFind(DLBegin(dlist), DLEnd(dlist), res_list,
                (void*)(long)18, IsModolu);
	
	PrintResultsLong("error_value", error, 0);
	
	/* new list contains only numbers div by 18 */
	for (i = 0; i < 100; i += 18)
	{
		int data = (int)(long)DLPopFront(res_list);
		
		PrintResultsInt(data, i);
	}
	
	DLDestroy(dlist);
	dlist = NULL;
	
	DLDestroy(res_list);
	res_list = NULL;
}


void TestDLSplice()
{
	dlist_t *base = NULL, *append = NULL;
	dl_iter_t iters_base[8] = {0};
	dl_iter_t iters_append[8] = {0};
	int vals_base_expect[] = {0,1,2,13,14,15,3,4,5,6,7};
	int vals_append_expect[] = {10,11,12,16,17};
	size_t i = 0;
	
	printf("\nTest - DL_List Splice\n");
	
	base = DLCreate();
	append = DLCreate();
	
	for (i = 0; i < 8; i++)
	{
		iters_base[i] = DLPushBack(base, (void*)i);
		iters_append[i] = DLPushBack(append, (void*)(i + 10));
	}
	
	PrintResultsLong("base size", DLSize(base), 8);
	PrintResultsLong("append size", DLSize(append), 8);
	
	DLSplice(iters_base[3], iters_append[3], iters_append[6]);
	
	PrintResultsLong("base size", DLSize(base), 11);
	PrintResultsLong("append size", DLSize(append), 5);
	
	PrintList(base, vals_base_expect, DLSize(base));
	PrintList(append, vals_append_expect, DLSize(append));
	
	DLDestroy(append);
	append = NULL;
	
	DLDestroy(base);
	base = NULL;
}

int IsMatch(const void *e1, const void *e2)
{
	return (e1 == e2);
}

int IsModolu(const void *e1, const void *e2)
{
	int is_modolu = !(((int)(long)e2) % ((int)(long)e1));
	return is_modolu;
}

int IncAndPrint(void *data, void *param)
{
	*(size_t*)data += (size_t)param;
	printf(" %ld ", *(size_t*)data);
	return 0;
}

int PrintAster(void *data, void *param)
{
	int error = 0;
	size_t i = 0;
	(void)data;
	
	for (; i < (size_t)param; i++)
	{
		printf("*");
		if (2 == i)
		{
			error = 1; /* return error */
			break;
		}
	}
	
	return error;
}

void PrintResultsInt (int res, int expect)
{
	if (res == expect)
	{
		printf("\033[1;32m"); /* green - equals */
	}
	else
	{
		printf("\033[1;31m"); /* red - different */
	}
	printf ("result: %d , expect: %d\n", res, expect);
	
	printf("\033[0m"); /* reset color */
}

void PrintResultsLong (char *title, size_t res, size_t expect)
{
	if (res == expect)
	{
		printf("\033[1;32m"); /* green - equals */
	}
	else
	{
		printf("\033[1;31m"); /* red - different */
	}
	printf ("%s: %ld , expect: %ld\n", title, res, expect);
	
	printf("\033[0m"); /* reset color */
}


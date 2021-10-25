/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      ---
* Description   Tests Sorted_List module 
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/
#include <stdio.h> /*printf*/
#include <limits.h> /*INT_MAX*/
#include "sorted_list.h"

int compare(const void *data1, const void *data2);
void TestInsertRemoveSRList();
void PrintSRList(sr_list_t *sr_list);
void TestPopSRList();
void TestRListMerge();
void TestFind();

int main()
{
	TestInsertRemoveSRList();
	TestPopSRList();
	TestRListMerge();
	TestFind();
	
	return 0;
}

int compare(const void *data1, const void *data2)
{
	if ((int *)(long)data1 > (int *)(long)data2)
	{
		return 1;
	}
	else if ((int *)(long)data1 < (int *)(long)data2)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

void PrintSRList(sr_list_t *sr_list)
{
	sr_iter_t iter, end;
	
	iter = SortedLBegin(sr_list);
	end = SortedLEnd(sr_list);
	
	while (!SortedLIsIterEqual(iter, end))
	{
		printf("%d ", (int)(long)SortedLGetData(iter));
		iter = SortedLNext(iter);
	}
	
	printf("\n");
}

void TestInsertRemoveSRList()
{
	sr_list_t *sr_list = SortedLCreate(compare);
	sr_iter_t sr_iter = SortedLEnd(sr_list);
	
	printf("\nTest - Insert and Remove\n");
	printf("is empty = %d\n", SortedLIsEmpty(sr_list));
	
	sr_iter = SortedLInsert(sr_list, (int *)(long)10);
	sr_iter = SortedLInsert(sr_list, (int *)(long)20);
	
	PrintSRList(sr_list);
	printf("Size of list: %ld\n", SortedLSize(sr_list));
	
	sr_iter = SortedLInsert(sr_list, (int *)(long)4);
	sr_iter = SortedLInsert(sr_list, (int *)(long)-514);
	sr_iter = SortedLInsert(sr_list, (int *)(long)4);
	
	PrintSRList(sr_list);
	sr_iter = SortedLRemove(sr_iter);
	sr_iter = SortedLRemove(sr_iter);
	
	PrintSRList(sr_list);
	printf("Size of list: %ld\n", SortedLSize(sr_list));		
	printf("is empty = %d\n", SortedLIsEmpty(sr_list));
	
	SortedLDestroy(sr_list);
	sr_list = NULL;
}

void TestPopSRList()
{
	sr_list_t *sr_list = SortedLCreate(compare);
	
	printf("\nTest - Pop Functions\n");
	
	SortedLInsert(sr_list, (int *)(long)10);
	SortedLInsert(sr_list, (int *)(long)20);
	SortedLInsert(sr_list, (int *)(long)4);
	SortedLInsert(sr_list, (int *)(long)514);
	
	PrintSRList(sr_list);
	
	SortedLPopBack(sr_list);
	SortedLPopBack(sr_list);
	
	PrintSRList(sr_list);
	
	SortedLPopFront(sr_list);
	
	PrintSRList(sr_list);
	
	SortedLDestroy(sr_list);
	sr_list = NULL;
}

void TestRListMerge()
{
	sr_list_t *src = SortedLCreate(compare);
	sr_list_t *dest = SortedLCreate(compare);
	
	printf("\nTest - Merge Function\n");
	
	SortedLInsert(src, (int *)(long)1);
	SortedLInsert(src, (int *)(long)50);
	SortedLInsert(src, (int *)(long)80);
	SortedLInsert(src, (int *)(long)2);
	
	PrintSRList(src);
	
	SortedLInsert(dest, (int *)(long)10);
	SortedLInsert(dest, (int *)(long)20);
	SortedLInsert(dest, (int *)(long)40);
	SortedLInsert(dest, (int *)(long)100);
	
	PrintSRList(dest);
	
	SortedLMerge(dest, src);

	PrintSRList(dest);
	PrintSRList(src);
	
	SortedLDestroy(src);
	SortedLDestroy(dest);
}

void TestFind()
{
	sr_list_t *sr_list = SortedLCreate(compare);
	sr_iter_t sr_iter;
	sr_iter_t sr_iter_end;
	
	printf("\nTest - Find Function\n");
	
	SortedLInsert(sr_list, (int *)(long)10);
	SortedLInsert(sr_list, (int *)(long)20);
	SortedLInsert(sr_list, (int *)(long)4);
	SortedLInsert(sr_list, (int *)(long)514);
	
	sr_iter = SortedLBegin(sr_list);
	sr_iter_end = SortedLEnd(sr_list);
	
	sr_iter = SortedLFind(sr_iter, sr_iter_end, (int *)(long)20, sr_list);
	
	printf("the value that found is: %d\n", (int)(long)SortedLGetData(sr_iter));
	
	SortedLDestroy(sr_list);
}
	

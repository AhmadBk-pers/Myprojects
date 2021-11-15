/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      ---
* Description   Heap modules test
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/

#include <stdio.h> /* printf */

#include "heap.h"  /* API    */



void HeaderColor(char *string);
void Yellow();
void Red(void);
void Green(void);
void ResetColor(void);
void TestExpectedINTS(int actual, int expected, const char *func_name);

void InitIntArr(int *arr, size_t size);
int CompareInts(const void *d1, const void *d2);
int IsMatchInt(const void *d1, const void *d2);

void TestUnit1();
void TestUnit2();
void TestUnit3();


int main()
{
    TestUnit1();
    TestUnit2();
    TestUnit3();

    return 0;
}

void TestUnit3()
{
    heap_t *heap = HeapCreate(CompareInts);
    int i = 0, size = 20, not_found = 100;
    int arr[20];
    InitIntArr(arr, size);

    HeaderColor("Unit 3");

    for (i = 0; i < size; i++)
    {
        HeapPush(heap, &arr[i]);
    }

    TestExpectedINTS(*(int *)HeapPop(heap), 19, "Pop 19");
    TestExpectedINTS(*(int *)HeapPop(heap), 18, "Pop 18");
    TestExpectedINTS(*(int *)HeapPop(heap), 17, "Pop 17");
    TestExpectedINTS(*(int *)HeapPop(heap), 16, "Pop 16");
    
    TestExpectedINTS(*(int *)HeapRemoveIf(heap, &arr[10], IsMatchInt), arr[10], "Remove IF");
    TestExpectedINTS(*(int *)HeapRemoveIf(heap, &arr[0], IsMatchInt), arr[0], "Remove IF");
    TestExpectedINTS(*(int *)HeapRemoveIf(heap, &arr[4], IsMatchInt), arr[4], "Remove IF");
    TestExpectedINTS(*(int *)HeapRemoveIf(heap, &arr[15], IsMatchInt), arr[15], "Remove IF");
    TestExpectedINTS((size_t)HeapRemoveIf(heap, &not_found, IsMatchInt), 0, "Remove IF- Not Found");

    TestExpectedINTS(*(int *)HeapPop(heap), 14, "Pop");

    TestExpectedINTS(*(int *)HeapRemove(heap, &arr[7]), arr[7], "Remove");
    TestExpectedINTS(*(int *)HeapRemove(heap, &arr[3]), arr[3], "Remove");
    TestExpectedINTS(*(int *)HeapRemove(heap, &arr[9]), arr[9], "Remove");
    TestExpectedINTS(*(int *)HeapRemove(heap, &arr[1]), arr[1], "Remove");
    TestExpectedINTS((size_t)HeapRemove(heap, &not_found), 0, "Remove- Not Found");

    TestExpectedINTS(*(int *)HeapPop(heap), 13, "Pop");

    HeapDestroy(heap);
}

void TestUnit2()
{
    heap_t *heap = HeapCreate(CompareInts);
    int i = 0, size = 20;
    int arr[20];
    InitIntArr(arr, size);

    HeaderColor("Unit 2");

    TestExpectedINTS(HeapSize(heap), 0, "Size");

    for (i = size - 1; i >= 0; i--)
    {
        HeapPush(heap, &arr[i]);
    }

    TestExpectedINTS(HeapIsEmpty(heap), 0, "Is Empty");
    TestExpectedINTS(HeapSize(heap), size, "Size");
    TestExpectedINTS(*(int *)HeapPeek(heap), size - 1, "Peek");

    HeapDestroy(heap);
}

void TestUnit1()
{
    heap_t *heap = HeapCreate(CompareInts);

    HeaderColor("Unit 1");

    TestExpectedINTS(HeapIsEmpty(heap), 1, "Is Empty");

    HeapDestroy(heap);
}

int IsMatchInt(const void *d1, const void *d2)
{
    return (*(int *)d1 == *(int *)d2);
}

int CompareInts(const void *d1, const void *d2)
{
	return *(int *)d1 - *(int *)d2;
}

void InitIntArr(int *arr, size_t size)
{
	size_t i = 0;

	for (; i < size; i++)
	{
		arr[i] = i;
	}
}

void TestExpectedINTS(int actual, int expected, const char *func_name)
{
	if (actual != expected)
	{
		Red();
		printf("Result: %d \n", actual);
	}
	else
	{
		Green();
	}
	
	printf("%s\n", func_name);
	ResetColor();
}

void HeaderColor(char *string)
{
	Yellow();
	printf("\n%s \n", string);
	ResetColor();
}

void Yellow()
{
	printf("\033[0;33m");
}

void Red() 
{
	printf("\033[1;31m");
}

void Green() 
{
	printf("\033[0;32m");
}

void ResetColor()
{
	printf("\033[0m");
}

/*Reviewer: Ron*/

#include <stdio.h> /* printf */
#include "d_vector.h"


void TestVectorExist();
void TestVectorReserve();
void TestVectorFewPushes();
void TestVectorSet();
void TestVectorShrink();
void TestVectorOverPush();
void TestVectorUnderReserve();
void TestVectorEmpty();
void TestVectorExtreme();


void FillVector(vector_t*, size_t);


int main()
{
	TestVectorExist();
	TestVectorReserve();
	TestVectorFewPushes();
	TestVectorSet();
	TestVectorOverPush();
	TestVectorUnderReserve();
	TestVectorShrink();
	TestVectorEmpty();
	TestVectorExtreme();
	
	printf("\n");
	return 0;
}



void TestVectorExist()
{
	vector_t *vec = DVectorCreate(5);
	DVectorDestroy(vec);
	vec = NULL;
}


void TestVectorReserve()
{
	vector_t *vec = DVectorCreate(2);
	
	printf("\nTest - Vector Reserve\n");
	
	DVectorReserve(vec, 70);
	
	FillVector(vec, 65);
	
	printf("size: %ld, capacity: %ld\n", DVectorGetSize(vec), DVectorGetCapacity(vec));
	
	DVectorDestroy(vec);
	vec = NULL;
}


void TestVectorFewPushes()
{
	vector_t *vec = DVectorCreate(5);
	int x1 = 1, x2 = 2, x3 = 3;
	int y1, y2, y3;
	
	printf("\nTest - Vector Push & Pop\n");
	
	printf("size: %ld, capacity: %ld\n", DVectorGetSize(vec), DVectorGetCapacity(vec));
	
	DVectorPushBack(vec, &x1);
	DVectorPushBack(vec, &x2);
	DVectorPushBack(vec, &x3);
	
	printf("size: %ld, capacity: %ld\n", DVectorGetSize(vec), DVectorGetCapacity(vec));
	
	y1 = *(int*)DVectorPopBack(vec);
	y2 = *(int*)DVectorPopBack(vec);
	y3 = *(int*)DVectorPopBack(vec);
	
	printf("y1: %d, y2: %d, y3: %d\n", y1, y2, y3);
	
	printf("size: %ld, capacity: %ld\n", DVectorGetSize(vec), DVectorGetCapacity(vec));
	
	DVectorDestroy(vec);
	vec = NULL;
}


void TestVectorSet()
{
	vector_t *vec = DVectorCreate(5);
	int x = 0;
	
	printf("\nTest - Vector Set\n");
	
	FillVector(vec, 4);
	
	x = (int)(size_t)DVectorGet(vec, 2);
	printf("x before set: %d\n", x);
	
	DVectorSet(vec, 2, (void*)(long)80);
	
	x = (int)(size_t)DVectorGet(vec, 2);
	printf("x after set: %d\n", x);
	
	DVectorDestroy(vec);
	vec = NULL;
}


void TestVectorShrink()
{
	vector_t *vec = DVectorCreate(5);
	
	
	DVectorDestroy(vec);
	vec = NULL;
}


void TestVectorOverPush()
{
	vector_t *vec = DVectorCreate(5);
	size_t size = 0, capacity = 0;
	int x = 0;
	
	printf("\nTest - Vector Over Push\n");
	
	FillVector(vec, 13);
	
	size = DVectorGetSize(vec);
	capacity = DVectorGetCapacity(vec);
	x = (int)(size_t)DVectorPopBack(vec);
	
	printf("size: %ld, capacity: %ld, x: %d\n", size, capacity, x);
	
	DVectorDestroy(vec);
	vec = NULL;
}


void TestVectorUnderReserve()
{
	vector_t *vec = DVectorCreate(20);
	size_t size = 0, capacity = 0;
	int x = 0;
	
	printf("\nTest - Vector Under Reserve\n");
	
	FillVector(vec, 20);
	
	DVectorReserve(vec, 4);
	
	size = DVectorGetSize(vec);
	capacity = DVectorGetCapacity(vec);
	x = (int)(size_t)DVectorPopBack(vec);
	
	printf("size: %ld, capacity: %ld, x: %d\n", size, capacity, x);
	
	DVectorDestroy(vec);
	vec = NULL;
}


void TestVectorEmpty()
{
	vector_t *vec = DVectorCreate(0);
	
	
	DVectorDestroy(vec);
	vec = NULL;
}


void TestVectorExtreme()
{
	vector_t *vec = DVectorCreate(1000000);
	
	
	DVectorDestroy(vec);
	vec = NULL;
}





void FillVector(vector_t *vector, size_t size)
{
	size_t i = 0;
	
	for (i = 0; i < size; i++)
	{
		DVectorPushBack(vector, (void*)i);
	}
}







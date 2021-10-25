#include <stdio.h>	/*printf*/
#include "testcolors.h"

#include "stack.h"

void TestStack(size_t capacity, int object, int test_object);
void TestStackLIFO(size_t capacity);
void TestStackFull(size_t capacity);

int main()
{
	int object = 2, test_object = 2, capacity = 7;
	TestStack(capacity, object, test_object);
	TestStackLIFO(capacity);
	TestStackFull(capacity);
	
	return 0;
}

void CheckResult(unsigned int real_result, unsigned int result, char *test_name)
{
	if (real_result == result)
	{
		green();
		printf("The function %s passed the test\n", test_name);
		reset();
	}
	else 
	{
		red();
		printf("The function %s failed the test\n", test_name);
		reset();
	}
}

void TestStack(size_t capacity, int object, int test_object)
{
	size_t size = -5, IsEmpty = 1, capacity_test = 0;
	stack_t *stack = StackCreate(capacity);
	
	IsEmpty = StackIsEmpty(stack);
	CheckResult(1, IsEmpty, "StackIsEmpty");
	
	StackPush(stack, &object);
	test_object = *(int *)StackPop(stack);
	
	CheckResult( object,  test_object, "Push and Pop");
	
	StackPush(stack, &object);
	StackPush(stack, &object);
	StackPush(stack, &object);
	
	test_object = *(int *)StackPeek(stack);
	CheckResult( object,  test_object, "Peak");
	
	size = StackSize(stack);
	CheckResult( 3,  size, "size");
	
	IsEmpty = StackIsEmpty(stack);
	CheckResult( 0,  IsEmpty, "StackIsEmpty");
	
	StackPop(stack);
	StackPop(stack);
	StackPop(stack);
	
	IsEmpty = StackIsEmpty(stack);
	CheckResult( 1,  IsEmpty, "StackIsEmpty");
	
	capacity_test = StackCapacity(stack);
	CheckResult( capacity,  capacity_test, "StackCapacity");
	
	StackDestroy(stack);
	
}

void TestStackLIFO(size_t capacity)
{
	stack_t *stack = StackCreate(capacity);
	
	int arr[5] = {1, 2, 3, 4, 5}, i = 0;
	
	for (i = 0; i < 5; i++)
	{
		StackPush(stack, &arr[i]);
	}
	
	for (i = 0; i < 5; i++)
	{
		CheckResult(*(int *)StackPop(stack),  arr[4 - i], "LIFO");
	}
	
	StackDestroy(stack);

}

void TestStackFull(size_t capacity)
{
	stack_t *stack = StackCreate(capacity);
	
	int arr[] = {1, 2, 3, 4, 5, 6, 7}, i = 0;
	
	for (i = 0; i < (int)capacity; i++)
	{
		StackPush(stack, &arr[i]);
	}
	
	for (i = 0; i < (int)capacity; i++)
	{
		CheckResult(*(int *)StackPop(stack),  arr[6 - i], "LIFO");
	}
	
	StackDestroy(stack);

}


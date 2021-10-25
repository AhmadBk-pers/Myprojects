#include <stdlib.h> /* malloc*/
# include <assert.h> /*assert*/
#include "stack.h"

struct stack
{
	void **base_ptr;
	size_t top_index;
	size_t capacity;
};

stack_t *StackCreate(size_t capacity)
{	
	stack_t *stack;
	assert (capacity > 0);
	stack = (stack_t *)malloc(sizeof(stack_t));
	stack->base_ptr = (void **)malloc(sizeof(void *) * (capacity));
	stack->top_index = 0;
	stack->capacity = capacity;
	
	return stack;
}

void StackDestroy(stack_t *stack)
{
	free(stack->base_ptr);
	stack->base_ptr = NULL;
	free(stack);
	stack = NULL;
}

void *StackPop(stack_t *stack)
{
	assert (0 != stack->top_index);
	return stack->base_ptr[--stack->top_index];
}

void StackPush(stack_t *stack, void *object)
{
	assert (stack->capacity != stack->top_index);
	stack->base_ptr[stack->top_index++] = object;
}

void *StackPeek(const stack_t *stack)
{
	return stack->base_ptr[stack->top_index - 1];
}

size_t StackSize(const stack_t *stack)
{
	return stack->top_index;
}

int StackIsEmpty(const stack_t *stack)
{
	return !(stack->top_index);
}

size_t StackCapacity(const stack_t *stack)
{
	return stack->capacity;
}



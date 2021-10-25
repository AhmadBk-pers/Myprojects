#ifndef __STACK_H__
#define __STACK_H__

/*
	OL 109
	25/8/2021
	
	version: 3
*/

#include <stddef.h> /* size_t */

typedef struct stack stack_t;

stack_t *StackCreate(size_t capacity);

void StackDestroy(stack_t *stack);

void *StackPop(stack_t *stack);

void StackPush(stack_t *stack, void *object);

void *StackPeek(const stack_t *stack);

size_t StackSize(const stack_t *stack);

int StackIsEmpty(const stack_t *stack);

size_t StackCapacity(const stack_t *stack);


#endif /* __STACK_H__ guard */

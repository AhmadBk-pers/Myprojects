#ifndef __STACK_INT_H__
#define __STACK_INT_H__

#include <stddef.h> /* size_t */

typedef struct stack
/*{
    size_t capacity;
    size_t size;
    void **stack_element;
}*/stack_t;
/********************* ~FUNctions~ **********************/

/* Create new stack of given capacity */
stack_t *StackCreate(size_t capacity);

/* destroy the whole stack,  */
void StackDestroy(stack_t *stack);

/* add an element to the top of the stack */
void StackPush(stack_t *stack, int elem);

/* removes top element from the stack */
void StackPop(stack_t *stack);

/* returns last element */
int StackPeek(const stack_t *stack);

/* return number of elements in stack */
size_t StackSize(const stack_t *stack);

/* return stack capacity */
size_t StackCapacity(const stack_t *stack);

/* return if stack is empty or not (meaning contains any elements) */
int StackIsEmpty(const stack_t *stack);

#endif /* __STACK_INT_H__  */

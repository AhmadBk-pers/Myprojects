#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include "stack_int.h"
/*#include <stdio.h>*/

 struct stack
{
    size_t capacity;
    size_t size;
    int *base_stack_element;
};

/* Create new stack of given capacity */
stack_t *StackCreate(size_t capacity)
{
    stack_t *new_stack = malloc(sizeof(stack_t) +
                            capacity * sizeof(int));
    int *base_stack_element = NULL;

    if (!new_stack)
    {
        return NULL;
    }

    base_stack_element = (int *)(new_stack + 1);
    /* casting to char * to make it increment by byte steps,
        instead of sizeof(stack_memory) steps */
    /*printf("%lu %lu %lu\n", &(*stack_memory), &(*new_stack), &(*base_stack_element));
*/
    new_stack->capacity = capacity;
    new_stack->size = 0;
    new_stack->base_stack_element = base_stack_element;

    return new_stack;
}

/* destroy the whole stack */
void StackDestroy(stack_t *stack)
{
    assert(stack);

    free(stack);
}

/* add an element to the top of the stack */
void StackPush(stack_t *stack, int elem)
{
    assert(stack);
    assert(stack->size != stack->capacity);

    *(stack->base_stack_element + stack->size) = elem;
    ++(stack->size);
}

/* removes top element from the stack */
void StackPop(stack_t *stack)
{
    assert(stack);
    /* assert(0 != stack->size);*/
    if (stack->size > 0)
    {
        --(stack->size);
    }
}

/* returns last element */
int StackPeek(const stack_t *stack)
{
    assert(stack);
    /* assert(0 != stack->size);*/

    return stack->base_stack_element[stack->size - 1];
}

/* return number of elements in stack */
size_t StackSize(const stack_t *stack)
{
    assert(stack);

    return stack->size;
}

/* return stack capacity */
size_t StackCapacity(const stack_t *stack)
{
    assert(stack);

    return stack->capacity;
}

/* return if stack is empty or not (meaning contains any elements) */
int StackIsEmpty(const stack_t *stack)
{
    assert(stack);

    return (0 == stack->size);
}

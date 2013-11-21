#include <stdlib.h>
#include "stack.h"

Stack*
stack_new(void)
{
	return (Stack*)calloc(1, sizeof(Stack));
}

void
stack_push(Stack *stack, void *data)
{
	stack->list = slist_insert(stack->list, data, 0);
}

void*
stack_peek(Stack *stack)
{
	return slist_get(stack->list, 0);
}

void*
stack_pop(Stack *stack)
{
	void *data = slist_get(stack->list, 0);

	stack->list = slist_remove(stack->list, 0);

	return data;
}

void
stack_destroy(Stack *stack)
{
	slist_destroy(stack->list);

	free(stack);
}

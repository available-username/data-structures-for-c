#ifndef _STACK_H_
#define _STACK_H_

#include "slist.h"

typedef struct _Stack {
	SList *list;
	uint32_t size;
} Stack;

Stack*
stack_new(void);

void
stack_push(Stack *stack, void *data);

void*
stack_peek(Stack *stack);

void*
stack_pop(Stack *stack);

void
stack_destroy(Stack *stack);

uint32_t
stack_size(Stack *stack);

#endif /* _STACK_H_ */

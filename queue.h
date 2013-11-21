#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdint.h>
#include "dlist.h"
#include "common.h"

typedef struct {
	DList *head;
	DList *tail;
	uint32_t size;
} Queue;

Queue *
queue_new(void);

void
queue_destroy(Queue *queue);

void
queue_add_as_head(Queue *queue,
	void *data);

void
queue_add_as_tail(Queue *queue,
	void *data);

void *
queue_peek_head(Queue *queue);

void *
queue_peek_tail(Queue *queue);

void *
queue_remove_head(Queue *queue);

void *
queue_remove_tail(Queue *queue);

uint32_t
queue_size(Queue *queue);

void
queue_foreach_from_head(Queue *queue,
	foreach func, void *userdata);

void
queue_foreach_from_tail(Queue *queue,
	foreach func, void *userdata);

#endif /* _QUEUE_H_ */

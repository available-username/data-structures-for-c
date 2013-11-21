#include <stdlib.h>
#include "queue.h"

Queue *
queue_new(void)
{
	Queue *queue = calloc(1, sizeof(Queue));

	queue->size = 0;

	return queue;
}

void
queue_destroy(Queue *queue)
{
	if (queue->head != NULL) {
		dlist_destroy(queue->head);
	}

	free(queue);
}

void
queue_add_as_head(Queue *queue,
	void *data)
{
	if (queue->head == NULL) {
		queue->head = dlist_insert(queue->head, data, 0);

		queue->tail = queue->head;
	} else {
		queue->head = dlist_insert(queue->head, data, 0);
	}

	queue->size++;
}

void
queue_add_as_tail(Queue *queue,
	void *data)
{
	if (queue->head == NULL) {
		queue_add_as_head(queue, data);
	} else {
		DList *tmp = NULL;
		
		tmp = dlist_insert(tmp, data, 0);

		tmp->prev = queue->tail;
		queue->tail->next = tmp;
		queue->tail = tmp;

		queue->size++;
	}
}

void *
queue_peek_head(Queue *queue)
{
	return queue->size > 0 ? queue->head->data : NULL;
}

void *
queue_peek_tail(Queue *queue)
{
	return queue->size > 0 ? queue->tail->data : NULL;
}

void *
queue_remove_head(Queue *queue)
{
	void *data;

	if (queue->size > 0) {
		DList *tmp = queue->head;

		data = queue->head->data;
		queue->head = queue->head->next;

		tmp->prev = NULL;
		tmp->next = NULL;

		dlist_remove(tmp, 0);

		if (queue->head == NULL) {
			queue->tail = NULL;
		}

		queue->size--;
	} else {
		data = NULL;
	}

	return data;
}

void *
queue_remove_tail(Queue *queue) {
	void *data;

	if (queue->size > 0) {
		DList * tmp = queue->tail;

		data = queue->tail->data;
		queue->tail = queue->tail->prev;

		tmp->prev = NULL;
		tmp->next = NULL;

		dlist_remove(tmp, 0);

		if (queue->tail == NULL) {
			queue->head = NULL;
		}

		queue->size--;
	} else {
		data = NULL;
	}

	return data;
}

uint32_t
queue_size(Queue *queue)
{
	return queue->size;
}

void
queue_foreach_from_head(Queue *queue,
	foreach func, void *userdata)
{
	DList *list = queue->head;

	while (list != NULL) {
		func(list->data, userdata);
		list = list->next;
	}
}

void
queue_foreach_from_tail(Queue *queue,
	foreach func, void *userdata)
{
	DList *list = queue->tail;

	while (list != NULL)  {
		func(list->data, userdata);
		list = list->prev;
	}
}


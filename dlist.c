#include <stdlib.h>
#include "dlist.h"

DList*
dlist_insert(DList *list, void *data,
	uint32_t position)
{
	DList *node;
	DList *previous;
	DList *current;
	uint32_t i;

	node = (DList*)malloc(sizeof(DList));
	node->data = data;

	if (list == NULL) {
		node->prev = NULL;
		node->next = NULL;
		return node;
	}

	previous = NULL;
	current = list;

	for (i = 0; i < position; i++) {
		previous = current;
		current = current->next;
	}

	node->prev = previous;
	node->next = current;

	if (previous != NULL) {
		previous->next = node;
	} else {
		/* The element is inserted as the new head of the list
		 */
		list = node;
	}

	if (current != NULL) {
		current->prev = node;
	}

	return list;
}

DList*
dlist_remove(DList *list,
	uint32_t position)
{
	DList *previous;
	DList *current;
	uint32_t i;

	if (list == NULL) {
		return NULL;
	}

	previous = NULL;
	current = list;

	for (i = 0; i < position; i++) {
		previous = current;
		current = current->next;
	}

	if (previous != NULL) {
		previous->next = current->next;
	} else {
		list = current->next;
	}

	if (current->next != NULL) {
		current->next->prev = previous;
	}

	free(current);

	return list;
}

void*
dlist_get(DList *list,
	uint32_t position)
{
	while (position-- > 0) {
		list = list->next;
	}

	return list->data;
}

void
dlist_destroy(DList *list)
{
	while (list != NULL) {
		DList *tmp = list->next;

		free(list);
		list = tmp;
	}
}

uint32_t
dlist_size(DList *list)
{
	uint32_t size = 0;

	while (list != NULL) {
		list = list->next;
		size++;
	}

	return size;
}

void
dlist_foreach(DList *list, foreach func, void* userdata)
{
	DList *node;

	for (node = list; node != NULL; node = node->next) {
		func(node->data, userdata);
	}
}

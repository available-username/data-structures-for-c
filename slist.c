#include <stdlib.h>
#include "common.h"
#include "slist.h"

SList*
slist_insert(SList *list, void *data,
	uint32_t position)
{
	SList *node;
	SList *previous;
	SList *current;
	uint32_t i;

	node = (SList*) malloc(sizeof(SList));
	node->data = data;

	/* If the head of the list is NULL this will be the first element in the
	 * list.
	 */
	if (list == NULL) {
		node->next = NULL;
		return node;
	}

	/* Iterate through the list and insert at the proper position.
	*/
	previous = NULL;
	current = list;

	/* Note that if the position is after the last node's next, this will
	 * probably result in a segfault. It's the responsibility of the client
	 * to keep track of the number of items in the list.
	 */
	for (i = 0; i < position; i++) {
		previous = current;
		current = current->next;
	}

	node->next = current;

	if (previous != NULL) {
		previous->next = node;
	} else {
		list = node;
	}

	return list;
}

void*
slist_get(SList *list,
	uint32_t position)
{
	/* Could result in a segfault, it's the responsibility of the client to
	 * keep track of how many elements are in the list.
	 */
	while (position--) {
		list = list->next;
	}

	return list->data;
}

void
slist_destroy(SList *list)
{
	while (list != NULL) {
		SList *tmp = list;

		list = list->next;
		free(tmp);
	}
}

SList*
slist_remove(SList *list,
	uint32_t position)
{
	SList *previous;
	SList *current;
	uint32_t i;

	/* If the list is empty just return NULL.
	 */
	if (list == NULL) {
		return NULL;
	}

	previous = NULL;
	current = list;

	/* Note that if the position is after the last node's next, this will
	 * probably result in a segfault. It's the responsibility of the client
	 * to keep track of the number of items in the list.
	 */
	for (i = 0; i < position; i++) {
		previous = current;
		current = current->next;
	}

	if (previous == NULL) {
		list = current->next;
	} else {
		previous->next = current != NULL ? current->next : NULL;
	}

	free(current);

	return list;
	
}

uint32_t
slist_size(SList *list)
{
	uint32_t size = 0;

	while (list != NULL) {
		list = list->next;
		size++;
	}

	return size;
}

void
slist_foreach(SList *list, foreach func, void* userdata)
{
	while (list != NULL) {
		func(list->data, userdata);
		list = list->next;
	}
}


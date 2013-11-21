#ifndef _DLIST_H_
#define _DLIST_H_

#include <stdint.h>
#include "common.h"


typedef struct _DList DList;

/**
 * A double linked list node.
 */
struct _DList {
	void *data;
	DList *prev;
	DList *next;
};

/**
 * \brief Inserts a new data element into the list. If the list is \c NULL it
 * will be created.
 *
 * \param list The list to insert into or \c NULL
 * \param position The position to insert the element in. To insert at the
 * beginning of the list set position to 0, to insert at the end of the list
 * set the position to the size of the list.
 * \return The new head of the list.
 */
DList*
dlist_insert(DList *list, void *data,
	uint32_t position);

/**
 * \brief Removes an element from the list.
 *
 * \param list The lit to remove an element from.
 * \param position the position of the element to remove.
 * \return The new head of the list.
 */
DList*
dlist_remove(DList *list,
	uint32_t position);

/**
 * Get an element in the list.
 *
 * \param list The list to get an element from.
 * \param position The position of the element to get.
 * \return The element at position \c position.
 */
void*
dlist_get(DList *list,
	uint32_t position);

/**
 * \brief Destroys a list and deallocates all resources kept by the list. Note
 * the elements in the list will not be freed.
 *
 * \brief list The list to destroy.
 */
void
dlist_destroy(DList *list);

/**
 * Get the size of the list.
 *
 * \param list The list to get the size of.
 * \return The number of elements kept in the list.
 */
uint32_t
dlist_size(DList *list);

/**
 * Runs a function for each element of the list.
 *
 * \param list The list to apply the function on.
 * \param func The function to apply to each element.
 * \param userdata An optional pointer to supply to the function \c func.
 */
void
dlist_foreach(DList *list, foreach func, void* userdata);

#endif /* _DLIST_H_ */

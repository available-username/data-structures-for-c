#ifndef _SLIST_H_
#define _SLIST_H_

#include <stdint.h>


typedef struct _SList SList;

/**
 * A function pointer to apply to each element of the list.
 *
 * \param data An element contained within the list.
 * \param userdata An optional pointer supplied to the function.
 */
typedef void (*foreach)(void *data, void *userdata);

/**
 * A singel linked list node.
 */
struct _SList {
	void *data;
	SList *next;
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
SList*
slist_insert(SList *list, void *data,
	uint32_t position);

/**
 * \brief Removes an element from the list.
 *
 * \param list The lit to remove an element from.
 * \param position the position of the element to remove.
 * \return The new head of the list.
 */
SList*
slist_remove(SList *list,
	uint32_t position);

/**
 * Get an element in the list.
 *
 * \param list The list to get an element from.
 * \param position The position of the element to get.
 * \return The element at position \c position.
 */
void*
slist_get(SList *list,
	uint32_t position);

/**
 * \brief Destroys a list and deallocates all resources kept by the list. Note
 * the elements in the list will not be freed.
 *
 * \brief list The list to destroy.
 */
void
slist_destroy(SList *list);

/**
 * Get the size of the list.
 *
 * \param list The list to get the size of.
 * \return The number of elements kept in the list.
 */
uint32_t
slist_size(SList *list);

/**
 * Runs a function for each element of the list.
 *
 * \param list The list to apply the function on.
 * \param func The function to apply to each element.
 * \param userdata An optional pointer to supply to the function \c func.
 */
void
slist_foreach(SList *list, foreach func, void* userdata);

#endif /* _SLIST_H_ */

#ifndef _COMMON_H_
#define _COMMON_H_

#define NELEMS(a) (sizeof(a) / sizeof((a)[0]))

#define SWAP(T, a, b) do { \
	T __t = (a);           \
	(a) = (b);             \
	(b) = __t;             \
} while(0)

/**
 * A function pointer to apply to each element of a collection.
 *
 * \param data An element contained within the collection.
 * \param userdata An optional pointer supplied to the function.
 */
typedef void (*foreach)(void *data, void *userdata);

#endif /* _COMMON_H_ */

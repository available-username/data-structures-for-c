#include <stdio.h>
#include <check.h>
#include "check_queue.h"
#include "queue.h"

START_TEST(check_queue_add_as_head)
{
	Queue *queue;
	uint64_t i;

	queue = queue_new();
	fail_unless(queue != NULL);

	for (i = 0; i < 10; i++) {
		queue_add_as_head(queue, (void*)i);

		fail_unless(queue_size(queue) == i + 1);
	}

	for (; i > 0; i--) {
		uint64_t v;

		v = (uint64_t)queue_peek_head(queue);
		fail_unless(v == i - 1);
		fail_unless(queue_size(queue) == i);
		
		v = (uint64_t)queue_remove_head(queue);
		fail_unless(v == i - 1);
		fail_unless(queue_size(queue) == i - 1);
	}

	queue_destroy(queue);
}
END_TEST

static void
my_print(void *data, void *userdata)
{
	(void)userdata;
	printf("%ld ", (uint64_t)data);
}

START_TEST(check_queue_add_as_tail)
{
	Queue *queue;
	uint64_t i;

	queue = queue_new();
	fail_unless(queue != NULL);

	for (i = 0; i < 10; i++) {
		queue_add_as_tail(queue, (void*)i);

		fail_unless(queue_size(queue) == i + 1);
	}

	queue_foreach_from_head(queue, my_print, NULL);
	queue_foreach_from_tail(queue, my_print, NULL);

	for (; i > 0; i--) {
		uint32_t size;
		uint64_t v;

		v = (uint64_t)queue_peek_tail(queue);
		fail_unless(v == i - 1, "Got %ld, expected %ld", v, i - 1);

		size = queue_size(queue);
		fail_unless(size == i, "Got %d, expected %d", size, i);
		
		v = (uint64_t)queue_remove_tail(queue);
		fail_unless(v == i - 1, "Got %d, expected %d", v, i - 1);

		size = queue_size(queue);
		fail_unless(queue_size(queue) == i - 1, "Got %d, expected %d", size, i);
	}

	queue_destroy(queue);
}
END_TEST

Suite *
queue_suite(void)
{
	Suite *suite = suite_create("Queue suite");

	TCase *test_case = tcase_create("Queue core");

	tcase_add_test(test_case, check_queue_add_as_head);
	tcase_add_test(test_case, check_queue_add_as_tail);

	suite_add_tcase(suite, test_case);

	return suite;
}

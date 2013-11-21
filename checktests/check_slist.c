#include <stdio.h>
#include <check.h>
#include "check_slist.h"
#include "slist.h"

START_TEST(check_slist_insert)
{
	SList *list = NULL;
	SList *tmp;
	uint64_t i;

	for (i = 0; i < 10; i++) {
		list = slist_insert(list, (void*)i, i);
	}

	fail_unless(slist_size(list) == 10);

	for (i = 0, tmp = list; tmp != NULL; i++, tmp = tmp->next) {
		uint64_t v = (uint64_t)tmp->data;

		fail_unless(v == i);
	}

	slist_destroy(list);
}
END_TEST

START_TEST(check_slist_insert2)
{
	SList *list = NULL;
	uint32_t size;

	list = slist_insert(list, (void*)0, 0);
	list = slist_insert(list, (void*)2, 1);
	list = slist_insert(list, (void*)4, 2);
	list = slist_insert(list, (void*)1, 1);
	list = slist_insert(list, (void*)3, 3);
	list = slist_insert(list, (void*)5, 5);

	size = slist_size(list);
	fail_unless(size == 6, "Size is %d, expected 6", size);

	fail_unless(((uint64_t)slist_get(list, 0)) == 0);
	fail_unless(((uint64_t)slist_get(list, 1)) == 1);
	fail_unless(((uint64_t)slist_get(list, 2)) == 2);
	fail_unless(((uint64_t)slist_get(list, 3)) == 3);
	fail_unless(((uint64_t)slist_get(list, 4)) == 4);
	fail_unless(((uint64_t)slist_get(list, 5)) == 5);

	slist_destroy(list);
}
END_TEST

START_TEST(check_slist_remove)
{
	SList *list = NULL;
	uint64_t i;

	for (i = 0; i < 10; i++) {
		list = slist_insert(list, (void*)i, i);
	}

	for (i = 0; i < 10; i++) {
		fail_unless(i == (uint64_t)list->data, "i=%ld, list->data=%ld", i, (uint64_t)list->data);

		list = slist_remove(list, 0);
	}
}
END_TEST

START_TEST(check_slist_remove2)
{
	SList *list = NULL;
	uint32_t size;

	list = slist_insert(list, (void*)0, 0);
	list = slist_insert(list, (void*)1, 1);
	list = slist_insert(list, (void*)2, 2);

	size = slist_size(list);
	fail_unless(size == 3, "Size is %d, expected 3", size);

	list = slist_remove(list, 1);

	size = slist_size(list);
	fail_unless(size == 2, "Size is %d, expected 2", size);

	fail_unless(((uint64_t)slist_get(list, 0)) == 0);
	fail_unless(((uint64_t)slist_get(list, 1)) == 2);

	slist_destroy(list);
}
END_TEST

static void
test_foreach(void *data, void *userdata)
{
	uint64_t *i = (uint64_t*)data;

	*i = *i * (uint64_t)userdata;
}

START_TEST(check_slist_foreach)
{
	SList *list = NULL;
	uint64_t array[10];
	uint64_t multiplier = 10;
	uint64_t i;

	for (i = 0; i < 10; i++) {
		array[i] = i;

		list = slist_insert(list, array + i, i);
	}

	slist_foreach(list, test_foreach, (void*)multiplier);

	for (i = 0; i < 10; i++) {
		uint64_t* v = (uint64_t*)slist_get(list, i);

		fail_unless(*v == i * multiplier);
	}

	slist_destroy(list);
}
END_TEST

Suite *
slist_suite(void)
{
	Suite *suite = suite_create("SList suite");

	TCase *test_case = tcase_create("SList core");

	tcase_add_test(test_case, check_slist_insert);
	tcase_add_test(test_case, check_slist_insert2);
	tcase_add_test(test_case, check_slist_remove);
	tcase_add_test(test_case, check_slist_remove2);
	tcase_add_test(test_case, check_slist_foreach);

	suite_add_tcase(suite, test_case);

	return suite;
}

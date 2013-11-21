#include <stdio.h>
#include <check.h>
#include "check_stack.h"
#include "stack.h"

START_TEST(check_stack)
{
	Stack *stack = NULL;
	uint64_t i;

	stack = stack_new();

	fail_unless(stack != NULL);

	for (i = 0; i < 10; i++) {
		uint64_t v;

		stack_push(stack, (void*)i);

		v = (uint64_t) stack_peek(stack);

		fail_unless(v == i);
	}

	for (; i > 0; i--) {
		uint64_t v;

		v = (uint64_t) stack_pop(stack);

		fail_unless(v == i - 1, "Got %ld, expected %ld", v, i - 1);
	}

	stack_destroy(stack);
}
END_TEST

Suite *
stack_suite(void)
{
	Suite *suite = suite_create("Stack suite");

	TCase *test_case = tcase_create("Stack core");

	tcase_add_test(test_case, check_stack);

	suite_add_tcase(suite, test_case);

	return suite;
}

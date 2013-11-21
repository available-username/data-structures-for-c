#include <stdlib.h>
#include <check.h>
#include "check_slist.h"
#include "check_dlist.h"
#include "check_stack.h"
#include "check_queue.h"
#include "check_tree.h"

int main(void)
{
		SRunner *runner;
		int number_failed;

		runner = srunner_create(slist_suite());
		srunner_add_suite(runner, dlist_suite());
		srunner_add_suite(runner, stack_suite());
		srunner_add_suite(runner, queue_suite());
		srunner_add_suite(runner, tree_suite());

		srunner_run_all(runner, CK_NORMAL);

		number_failed = srunner_ntests_failed(runner);

		srunner_free(runner);

		return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

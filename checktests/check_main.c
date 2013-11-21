#include <stdlib.h>
#include <check.h>
#include "check_slist.h"

int main(void)
{
		Suite *slistsuite = slist_suite();
		SRunner *runner = srunner_create(slistsuite);
		int number_failed;

		srunner_run_all(runner, CK_NORMAL);

		number_failed = srunner_ntests_failed(runner);

		srunner_free(runner);

		return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

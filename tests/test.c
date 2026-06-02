#include <err.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include <stdlib.h>

void test_something_0(void) {
    CU_ASSERT_EQUAL(2, 2);
}

int main(void) {

	if (CU_initialize_registry() != CUE_SUCCESS)
      errx(EXIT_FAILURE, "can't initialize test registry");

	CU_pSuite numSuite = CU_add_suite("num", NULL, NULL); // create suite

  if (CU_get_error() != CUE_SUCCESS)
      errx(EXIT_FAILURE, "%s", CU_get_error_msg()); // check for error

  CU_add_test(numSuite, "num(0)", test_something_0); // add test to suite

  CU_basic_run_tests(); // run tests

  CU_cleanup_registry(); // cleanup registery

	return 0;
}

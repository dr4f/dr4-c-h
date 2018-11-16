#ifndef TEST_FAILURES_HEADER
#define TEST_FAILURES_HEADER

#include <stdio.h>

/* This file acts as a small utility for unit tests in C.
 * If a test fails, the executable can be run manually to see which lines the failure
 * occurred at.
 */

static unsigned test_failure_count = 0;

static void test_failure_check_failed( const char *check, unsigned lineno ) {
    fprintf( stderr, "FAILED at line %u: %s\n", lineno, check );
    ++test_failure_count;
}

#define TEST_FAIL_CHECK( PREDICATE )                          \
    do {                                            \
        if ( !(PREDICATE) )                         \
            test_failure_check_failed( #PREDICATE, __LINE__ );   \
    } while (0)

/* Body of main() function in a MAKE_TEST file.
 * must be final statement of the main() function.
 */
#define TEST_FAIL_RETURN if(test_failure_count > 0) {   \
                                puts("TESTS FAILED"); \
                                return 3; \
                            } else { \
                                  puts("TESTS PASSED");    \
                                  return 0; \
                            }

#endif // TEST_FAILURES_HEADER
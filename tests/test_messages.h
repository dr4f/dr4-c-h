#ifndef TESTINCLUDE_TEST_MESSAGES_H
#define TESTINCLUDE_TEST_MESSAGES_H

#include <stdio.h>
#include <stdlib.h>

#define TEST_MESSAGE_PASSED puts("TESTS PASSED")
#define TEST_MESSAGE_FAILED puts("TESTS FAILED")

#define TEST_MESSAGE_FAIL_NAME(name) printf("Failed test named: %s\n", #name)

#define TEST_MESSAGE_COND(b) if(b) { TEST_MESSAGE_PASSED; } else { TEST_MESSAGE_FAILED; }

#define TEST_MESSAGE_CALL_COND(c) if((c)()) { TEST_MESSAGE_PASSED; } else { TEST_MESSAGE_FAILED; }

// Runs through a list of generic callable elements of some given length
// The elements need to be callable via <elem>() syntax.
#define TEST_MESSAGE_LIST(lst, len) do { \
	unsigned i; \
	for(i = 0; i < len; i++) { \
           if(!(lst[i]())) { \
                   TEST_MESSAGE_FAILED; \ exit(1); \
           } \
	} \
	TEST_MESSAGE_PASSED; \
} while (0)


/* Defines a simple test case that provides a message to print when this test fails.
 * @param message a message to display if the test fails.
 * @param case a callable function pointer.
 */
struct test_message_case_t {
	const char * message;
	int (*test)(void);
};

// Runs through an array of test_message_case_t 
// Calls each one, if one fails, displays it's message and exits.
#define TEST_MESSAGE_CASE_LIST(lst, len) do { \
	unsigned i; \
	for(i = 0; i < len; i++) { \
           if(!(lst[i].test())) { \
                   printf("Test failed, reason: '%s'\n", lst[i].message);\
                   TEST_MESSAGE_FAILED; \
                   exit(1);\
           } \
	} \
	TEST_MESSAGE_PASSED; \
} while (0)

// Counts test structs inside some array to use with TEST_MESSAGE_CASE_LIST
#define TEST_MESSAGE_COUNT(arr) (sizeof(arr)/sizeof(struct test_message_case_t))


#endif // TESTINCLUDE_TEST_MESSAGES_H
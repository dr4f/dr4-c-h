#include "dr4-h.h"

#include "test_failures.h"

static void test_read_row_str_1(void)
{
	char output[100];
	unsigned char bytes[40];
	const char* rfmt = "bb";
	unsigned worked = dr4h_write_row_fmt(bytes, rfmt, 1, 0);
	TEST_FAIL_CHECK(worked == 21);
	(void) _dr4h_read_row_str(output, bytes, ',');
	TEST_FAIL_CHECK(strcmp("True,False\n", output) == 0);
}

/* Tests combo of none and bool
 */
static void test_read_row_str_2(void)
{
	char output[100];
	unsigned char bytes[40];
	const char* rfmt = "nb";
	unsigned worked = dr4h_write_row_fmt(bytes, rfmt, 0);
	TEST_FAIL_CHECK(worked == 20);
	(void) _dr4h_read_row_str(output, bytes, ',');
	TEST_FAIL_CHECK(strcmp("None,False\n", output) == 0);
}

int main(int argc, char const *argv[])
{
	test_read_row_str_1();
	test_read_row_str_2();
	TEST_FAIL_RETURN
	return 0;
}
#include "dr4-h.h"

#include "test_failures.h"

static void test_read_row_str(void)
{
	char output[100];
	unsigned char bytes[40];
	const char* rfmt = "bb";
	unsigned worked = dr4h_write_row_fmt(bytes, rfmt, 1, 0);
	TEST_FAIL_CHECK(worked == 21);
	(void) _dr4h_read_row_str(output, bytes, ',');
	TEST_FAIL_CHECK(strcmp("True,False\n", output) == 0);
}

int main(int argc, char const *argv[])
{
	test_read_row_str();
	TEST_FAIL_RETURN
	return 0;
}
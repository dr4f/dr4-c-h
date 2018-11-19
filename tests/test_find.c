#include "dr4-h.h"

#include "test_failures.h"


static void test_dr4h_body_data_eq(void)
{
	unsigned char data1[2] = { DR4H_TYPE_BOOL, 1 };
	unsigned char data2[2] = { DR4H_TYPE_BOOL, 1 };
	TEST_FAIL_CHECK(_dr4h_body_data_eq(data1, data2));
}

/* Tests inlcude coverage for wildcard case.
 */
static void test_dr4h_row_is_eq(void)
{
	const char* fmt_test_1 = "b*";
	const char* fmt_test_2 = "bn";
	unsigned char bytes_1[100];
	unsigned char bytes_2[100];
	unsigned worked1 = dr4h_row_write_fmt(bytes_1, fmt_test_1, 1);
	unsigned workd2 = dr4h_row_write_fmt(bytes_2, fmt_test_2, 1);
	TEST_FAIL_CHECK(worked1); // at least one check on the fmt write

	TEST_FAIL_CHECK(_dr4h_row_is_eq(bytes_1, bytes_2));
}

/* This test tests both find functions in the API,
 * as well as compatibility between the wild type and the find functions
 */
static void test_dr4h_find_row_funcs(void)
{
	void* result;
	unsigned row_count;
	static unsigned char row_data[512];
	unsigned char row_find[50];
	const char* fmt_find = "b*b";
	unsigned find_worked = dr4h_row_write_fmt(row_find, fmt_find, 1, 1);
	TEST_FAIL_CHECK(find_worked);
	void* writer = row_data;
	writer += dr4h_row_write_fmt(writer, "bbb", 1, 0, 1);
	writer += dr4h_row_write_fmt(writer, "bbb", 1, 1, 1);
	fprintf(stderr, "The rows pointer is %p, the writer pointer is %p\n", row_data, writer);
	result = dr4h_find_row(row_data, row_find, writer - (void*)row_data);
	row_count = dr4h_find_rows(row_data, row_find, writer - (void*)row_data);
	TEST_FAIL_CHECK(result == row_data);
	TEST_FAIL_CHECK(row_count == 2);
}

int main(int argc, char const *argv[])
{
	test_dr4h_body_data_eq();
	test_dr4h_row_is_eq();
	test_dr4h_find_row_funcs();
	TEST_FAIL_RETURN
	return 0;
}
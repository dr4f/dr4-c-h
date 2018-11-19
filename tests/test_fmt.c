#include "dr4-h.h"

#include "test_failures.h"

static void test_dr4h_calc_size_fmt(void)
{
	const char* fmt_test = "nbn";
	uint32_t len_hold = 0;
	size_t result = _dr4h_calc_size_fmt(fmt_test, &len_hold);
	TEST_FAIL_CHECK(len_hold == 3);
	TEST_FAIL_CHECK(result == 25);
}

static void test_dr4h_row_write_fmt_1(void)
{
	const char* fmt_test = "b";
	unsigned char bytes[100];
	unsigned worked = dr4h_row_write_fmt(bytes, fmt_test, 1);
	void* check_ptr = bytes;
	TEST_FAIL_CHECK(*(uint32_t*)(check_ptr) == 15); // size, len, 1 index, 1 bool, stop
	TEST_FAIL_CHECK(*(uint32_t*)(check_ptr + sizeof(uint32_t)) == 1); // 1 item
	TEST_FAIL_CHECK(*(uint32_t*)(check_ptr + 8) == 0);
	TEST_FAIL_CHECK(*(unsigned char*)(check_ptr + 13) == 1); // bool is true
}

/* Tests the macro alias to the private function
 * dr4h_write_row_fmt -> _dr4h_row_write_fmt
 */
static void test_dr4h_row_write_fmt_2(void)
{
	const char* fmt_test = "b";
	unsigned char bytes[20];
	void* check_ptr = bytes;
	unsigned worked = dr4h_write_row_fmt(bytes, fmt_test, 1);
	TEST_FAIL_CHECK(worked);
	TEST_FAIL_CHECK(*(uint32_t*)(check_ptr) == 15);
}


static void test_dr4h_row_write_fmt_return(void)
{
	const char* fmt_test = "bb";
	unsigned char bytes[40];
	void* check_ptr = bytes;
	unsigned worked = dr4h_write_row_fmt(bytes, fmt_test, 1, 1);
	TEST_FAIL_CHECK(worked == 21);
}

int main(int argc, char const *argv[])
{
	test_dr4h_calc_size_fmt();
	test_dr4h_row_write_fmt_1();
	test_dr4h_row_write_fmt_2();
	test_dr4h_row_write_fmt_return();
	TEST_FAIL_RETURN
	return 0;
}
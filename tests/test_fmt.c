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
	int worked = _dr4h_row_write_fmt(bytes, fmt_test, 1);
	void* check_ptr = bytes;
	TEST_FAIL_CHECK(*(uint32_t*)(check_ptr) == 15); // size, len, 1 index, 1 bool, stop
	TEST_FAIL_CHECK(*(uint32_t*)(check_ptr + sizeof(uint32_t)) == 1); // 1 item
	TEST_FAIL_CHECK(*(uint32_t*)(check_ptr + 8) == 0);
}

/* Tests the macro alias to the private function
 * dr4h_write_row_fmt -> _dr4h_row_write_fmt
 */
static void test_dr4h_row_write_fmt_2(void)
{
	const char* fmt_test = "b";
	unsigned char bytes[20];
	void* check_ptr = bytes;
	int worked = dr4h_write_row_fmt(bytes, fmt_test, 1);
	TEST_FAIL_CHECK(worked);
	TEST_FAIL_CHECK(*(uint32_t*)(check_ptr) == 15);
}

int main(int argc, char const *argv[])
{
	test_dr4h_calc_size_fmt();
	test_dr4h_row_write_fmt_1();
	test_dr4h_row_write_fmt_2();
	TEST_FAIL_RETURN
	return 0;
}
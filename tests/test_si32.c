#include "dr4-h.h"

#include "test_failures.h"

/* This file focuses on test cases for the si32 type in dr4-h
 */


static void test_dr4h_calc_size_si32(void)
{
	const char* fmt_test = "nin";
	uint32_t len_hold = 0;
	size_t result = _dr4h_calc_size_fmt(fmt_test, &len_hold);
	TEST_FAIL_CHECK(len_hold == 3);
	TEST_FAIL_CHECK(result == 28);
}

static void test_dr4h_si32_fmt(void)
{
	const char* fmt_test = "i";
	unsigned char bytes[100];
	unsigned worked = dr4h_row_write_fmt(bytes, fmt_test, 7);
	void* check_ptr = bytes;

	TEST_FAIL_CHECK(*(uint32_t*)(check_ptr) == 18); 
	TEST_FAIL_CHECK(*(uint32_t*)(check_ptr + sizeof(uint32_t)) == 1);
	TEST_FAIL_CHECK(*(uint32_t*)(check_ptr + 8) == 0);
	TEST_FAIL_CHECK(*(unsigned char*)(check_ptr + 12) == DR4H_TYPE_SI32);
	TEST_FAIL_CHECK(*(int32_t*)(check_ptr + 13) == 7);
}

int main(int argc, char const *argv[])
{
	test_dr4h_calc_size_si32();
	test_dr4h_si32_fmt();
	TEST_FAIL_RETURN
	return 0;
}
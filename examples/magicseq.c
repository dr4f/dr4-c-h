#include "dr4-h.h"


static const unsigned char test_bytes[4] = {
	83, 95, 120, 1
};

int main(int argc, char const *argv[])
{
	printf("The magic sequence is %u %u %u\n", DR4H_MAGIC[0], DR4H_MAGIC[1], DR4H_MAGIC[2]);
	printf("The sequence test_bytes, %s the magic test.\n", DR4H_CHECK_MAGIC(test_bytes) ? "passes" : "fails");
	return 0;
}
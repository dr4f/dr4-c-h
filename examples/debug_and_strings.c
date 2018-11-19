#include "dr4-h.h"


// Used to write row into
static unsigned char example_data[200];

int main(int argc, char const *argv[])
{
	char output[256];
	const char* fmt_string = "nbb";
	unsigned bytes_written = dr4h_row_write_fmt(example_data, fmt_string, 1, 0);
	unsigned chars_written = _dr4h_read_row_str(output, example_data, ',');
	printf("Row written is %u bytes long\n", bytes_written);
	printf("The string form is %u characters long\n", chars_written);
	printf("The string form is: %s", output);
	puts("The debug information appears below");
	_dr4h_row_debug_info(stdout, example_data);
	return 0;
}
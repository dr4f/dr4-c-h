#include "dr4-h.h"
#include <stdlib.h>

/* This file is an example implementation of how 
 * dr4 can be used to continously append data to file, much like a csv or logs,
 * but in a binary typed formed.
 */

#define DATA_APPENDER_BUF_SZ 512

/* Used for stringifying the recently constructed data row.
 */
static char APPEND_ROW_BUF[DATA_APPENDER_BUF_SZ];

static const char* USAGE_STR = "Usage: $ row_appender <num of rows> <path of output file>";

static inline void
clean_append_buf(void)
{
	memset(APPEND_ROW_BUF, '\0', (size_t)DATA_APPENDER_BUF_SZ);
}

struct data_append_t
{
	unsigned char row_buf[DATA_APPENDER_BUF_SZ];
	const char* path;
	FILE* fp;
};

int data_append_init(struct data_append_t* app, const char* path)
{
	app->fp = fopen(path, "a+b");
	if(app->fp == NULL)
	{
		fprintf(stderr, "Error: Cannot write to file at path '%s'\n", path);
		return 0;
	}
	app->path = path;
	_dr4h_file_write_magic(app->fp);
	return 1;
}

static void
data_append_push(struct data_append_t* app, int b1, int b2)
{
	unsigned bytes_of_row = dr4h_row_write_fmt(app->row_buf, "bb", b1, b2);
	fwrite(app->row_buf, bytes_of_row, 1, app->fp);
}

static void
data_append_close(struct data_append_t* app)
{
	fclose(app->fp);
}

int main(int argc, char const *argv[])
{
	struct data_append_t writer;
	long rows_to_make;
	long j;
	unsigned row_pack_worked;
	const char* path_output;
	size_t file_out_size = 0;
	puts("----Data Appending Example-------");
	if(argc != 3)
	{
		fprintf(stderr, "Example Error: Expected 3 cmd args, got %d\n", argc);
		fprintf(stderr, "%s\n", USAGE_STR);
		exit(1);
	}
	rows_to_make = strtol(argv[1], NULL, 10);
	path_output = argv[2];
	printf("Now Creating and Appending %ld rows.\n", rows_to_make);
	if(!data_append_init(&writer, path_output))
	{
		fprintf(stderr, "Error: Could not initialize data append instance, exiting.\n");
		exit(1);
	}
	clean_append_buf();
	for(j = 0; j < rows_to_make; j++)
	{
		data_append_push(&writer, 1, 1);
		dr4h_row_to_str(APPEND_ROW_BUF, writer.row_buf, ',');
		printf("Wrote the row: %s", APPEND_ROW_BUF);
		printf("To the file %s\n", path_output);
	}
	rewind(writer.fp);
	__get_file_ptr_size(writer.fp, &file_out_size);
	data_append_close(&writer);
	printf("After row appending, file size is now %lu\n", file_out_size);
	puts("-----Finished Appending Rows to File Example-------");
	return 0;
}
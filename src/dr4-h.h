#ifndef DR4_H_HEADER
#define DR4_H_HEADER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <assert.h>

/**
 * @author Joshua Weinstein
 * @email jweinst1@berkeley.edu
 * @file A single-file header of the dr4-h library
 */

#ifdef __cplusplus
extern "C" {
#endif

/** DR4H TYPE DEFINES  **/

#define DR4H_TYPE_STOP 0
#define DR4H_TYPE_NONE 1
#define DR4H_TYPE_BOOL 2

/***********************/

/**
 * Two macros that write either a false
 * or true data value to a pointer of 
 * unsigned char.
 */
#define DR4H_BOOL_WRITE_T(ptr) \
	              ptr[0] = DR4H_TYPE_BOOL; \
	              ptr[1] = 1

#define DR4H_BOOL_WRITE_F(ptr) \
	              ptr[0] = DR4H_TYPE_BOOL; \
	              ptr[1] = 0

/* Writes the DR4 magic sequence to a pointer of 
 * unsigned char.
 */
#define DR4H_WRITE_MAGIC(ptr) \
	              ptr[0] = 83; \
	              ptr[1] = 94; \
	              ptr[2] = 121

#define DR4H_CHECK_MAGIC(ptr) (ptr[0] == 83 && ptr[1] == 94 && ptr[2] == 121)


// A magic sequence that MUST occur at the start of every *.dr4 file.
static const unsigned char DR4H_MAGIC[3] = {83, 94, 121};
// Pad of 4 0 bytes that are meant to provide a safety cap on a series of rows.
static const unsigned char DR4H_FILE_END[4] = {0, 0, 0, 0};

/****Util Functions******/

/* @brief Fast inline function to get size of file
 *        that is already opened.
 */
static inline void
__get_file_ptr_size(FILE* fp, size_t* sz)
{
        fseek(fp, 0L, SEEK_END);
        *sz = ftell(fp);
        rewind(fp);
}


static void*
__safe_malloc_bytes(size_t size)
{
	void* arr = malloc(size);
	if(arr == NULL) 
	{
		fprintf(stderr, "Out of Memory Error: 'malloc()' returned NULL, exiting.");
		exit(2);
	}
	return arr;
}

static void
__safe_realloc_bytes(void** data, size_t size, size_t growth)
{
	void* new_data = realloc(*data, size + growth);
	if(new_data == NULL) 
	{
		fprintf(stderr, "Out of Memory Error: 'realloc()' returned NULL, exiting.");
		exit(2);
	}	
	*data = new_data;
}

/* Function that safely expands and appends bytes to an existing buffer,
 * without the use of special structures.
 */
static void
__safe_append_bytes(void** data,
	                size_t* len,
	                size_t* size, 
	                void* add, 
	                size_t add_size)
{
	if((*size) - (*len) <= add_size)
	{
		__safe_realloc_bytes(data, *size, *size);
		*size *= 2;
	}
	memcpy((*data) + *len, add, add_size);
}

/***************************/

/**
 * Special sizing function that calculates the memory needed for a row of some field arrangement.
 * All rows have a header that needs at least 12 bytes of memory, followed by aa data body.
 * The code for this format string is as follows
 * - n a None type
 * -b a Bool type
 * Note: + 1 is always added for the stop byte
 * Note: For every field in the row, 4 is added to the total size
 *       to account for one additional index slot.
 */
static size_t
_dr4h_calc_size_fmt(const char* fmt, uint32_t* length)
{
	*length = 0;
	// Starts at 8, one uint32 for size, one for length
	size_t total = 8;
	while(*fmt)
	{
		switch(*fmt)
		{
			case 'n':
			   total++;
			   break;
			case 'b':
			   total += 2;
			   break;
			default:
			   fprintf(stderr, "Error: Unrecognized fmt char '%c' in _dr4h_calc_size\n", *fmt);
			   return 0;
		}
		*length += 1;
		total += 4;
		++fmt;
	} 
	return total + 1;
}

/** Formatted row writing ~
 * This function is a va_arg function that will write a 
 * row of dr4 data with a row header and row body
 * Example, (buf, "nb", 1) -> [20, 2, 0, 1, 1, 2, 1, 0]
 * Above, 20, is the size of the entire row including the 
 *    the stop byte.
 * The 2 is the length of the row in number of fields/items.
 * Then the array of int's represents the offsets of each field in
 *    the row body.
 *
 * Returns 1 if success, 0 otherwise
 * NOTE: This function always writes a stop byte at the end of a row.
 */
static int
_dr4h_row_write_fmt(void* buf, const char* fmt, ...)
{
	int grab_int;
	uint32_t* offsets;
	void* body_begin;
	va_list fmt_arg_lst;
	uint32_t row_len = 0;
	size_t row_size = _dr4h_calc_size_fmt(fmt, &row_len);
	uint32_t offset_i = 0;
	if(row_len == 0)
	{
		fprintf(stderr, "Error: Attempted to write empty row in _dr4h_row_write_fmt\n");
		return 0;
	}
	// Writing the header 
	*(uint32_t*)buf = row_size;
	buf += sizeof(uint32_t);
	*(uint32_t*)buf = row_len;
	buf += sizeof(uint32_t);
	// advance past index slots
	offsets = (uint32_t*)buf;
	buf += sizeof(uint32_t) * row_len;
	// Used for calculating offset.
	body_begin = buf;
	// Ready to start data writing.
	va_start(fmt_arg_lst, fmt);
    while(*fmt)
    {
    	*offsets = buf - body_begin;
    	switch(*fmt)
    	{
    		case 'n':
    		    *(unsigned char*)buf = DR4H_TYPE_NONE;
    		    buf++;
    		    break;
    		case 'b':
    		    *(unsigned char*)(buf++) = DR4H_TYPE_BOOL;
    		    grab_int = va_arg(fmt_arg_lst, int);
    		    *(unsigned char*)(buf++) = grab_int;
    		    break;
    		default:
			   fprintf(stderr, "Error: Unrecognized fmt char '%c' in _dr4h_row_write_fmt\n", *fmt);
			   va_end(fmt_arg_lst);
			   return 0;    		    
    	}
    	++fmt;
    }
    *(unsigned char*)(buf++) = DR4H_TYPE_STOP;
	va_end(fmt_arg_lst);
	return 1;
}
// Allows function to be used with public name.
#define dr4h_write_row_fmt _dr4h_row_write_fmt

/* Writes the magic byte sequence to beginning of a file.
 * Returns 1 if successful, 0 otherwise.
 */
static inline int
_dr4h_file_write_magic(FILE* fp)
{
	rewind(fp);
	return 3 == fwrite(DR4H_MAGIC, 1, 3, fp);
}



// Macro that evaluates to the size of the current row pointed to.
#define DR4H_ROWP_SIZE(row) (*(uint32_t*)(row->data))
// Macro that derefences to the number of fields in the current row.
#define DR4H_ROWP_LEN(row) (*(uint32_t*)(row->data + 4))
// Macro that evaluates to a pointer to the index -> offsets array of the row.
#define DR4H_ROWP_INDEXES(row) ((uint32_t*)(row->data + 8))
/* getitem[] macro for rows
 * Evaluates to the field at some offset from the row header, at an index.
 * |size|len|indexes...|f0|f1...|fn|STOP
 */
#define DR4H_ROWP_ITEM_AT(row, ind) ((unsigned char*) (row->data + DR4H_ROW_INDEXES(row)[ind]))
// Macro that moves the row pointer up by one row
// This macro also stores the size of the last row,
// such that the previous row can be back referenced.
#define DR4H_ROWP_INC(row) \
               row->last = DR4H_ROWP_SIZE(row); \
               row->data += DR4H_ROWP_SIZE(row)
// Inits a row ptr to get setup for reading/writing on a binary array.
#define DR4H_ROWP_INIT(row, ptr) \
               row->data = ptr; \
               row->last = 0

// Macro that references previous row
// Defaults to NULL if last is zero.
#define DR4H_ROWP_PREV(row) ( row->last != 0 ? (row->data - row->last) : NULL )

/**
 * A struct representing a pointer to a formatted row of binary data.
 * This row references binary data stored by it's pointer via offsets.
 * The first offset is a uint32 of the entire size of the row, including
 * the stop byte. byte 0-3
 * The second offset is at 4-7, a uint32 of the total number of items in the row.
 * This is type is meant to be used privately, to aid in reading and writing dr4 format
 *     
 */
struct dr4h_row_ptr_t
{
	void* data;
	uint32_t last;
};   



#ifdef __cplusplus
}
#endif

#endif // DR4_H_HEADER
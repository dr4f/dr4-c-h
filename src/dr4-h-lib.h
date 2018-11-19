#ifndef DR4H_LIBRARY_HEADER
#define DR4H_LIBRARY_HEADER

#include "dr4-h.h"

/* This header is a public API interface for compiling
 * the single header dr4-h into a static library.
 */

#ifdef __cplusplus
extern "C" {
#endif


extern unsigned 
dr4h_row_write_fmt(void* buf, const char* fmt, ...);

extern unsigned 
dr4h_find_rows(void* rows, void* row, size_t upto);


extern void* 
dr4h_find_row(void* rows, void* row, size_t upto);


extern unsigned 
dr4h_row_to_str(char* dst, void* row, char delim);

extern unsigned 
dr4h_map_rows(void* rows,
	          void* packed,
	          uint32_t index,
	          size_t upto);
extern int 
dr4h_rows_to_file(const char* path, void* rows, size_t upto);

extern size_t 
dr4h_size_of_row(const char* fmt, uint32_t* length);


#ifdef __cplusplus
}
#endif

#endif // DR4H_LIBRARY_HEADER
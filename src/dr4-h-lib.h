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



#ifdef __cplusplus
}
#endif

#endif // DR4H_LIBRARY_HEADER
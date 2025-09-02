#ifndef _READ_H_INCLUDED_
#define _READ_H_INCLUDED_

#include <stdint.h>
#include <stdbool.h>

// return true on success and false on failure.
bool read_file_for_hex_colors(const char *path, uint32_t *out, uint32_t out_length);

#endif

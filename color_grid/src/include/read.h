#ifndef _READ_H_INCLUDED_
#define _READ_H_INCLUDED_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <sys/stat.h>

#include "engine_clock.h"

typedef struct read_file_change_t {
    engine_clock_t clock;
    uint64_t file_last_change_date;
    uint64_t file_current_change_date;
    struct stat file_stat;
} read_file_change_t;

// return true on success and false on failure.
bool read_file_for_hex_colors(const char *path, uint32_t *out, size_t out_length,
                              size_t *return_length);
bool read_file_for_hex_color_changes(read_file_change_t *state, float interval,
                                     const char *path, uint32_t *out, size_t out_length,
                                     size_t *return_length);

#endif

#include <string.h>
#include <stdio.h>

#include "include/read.h"
#include "include/hex_color.h"
#include "include/optional.h"

bool read_file_for_hex_colors(const char *path, uint32_t *out, size_t out_length,
                              size_t *return_length)
{
    FILE *file_ptr;
    if ((file_ptr = fopen(path, "r")) == NULL) {
        return false;
    }
    char buf[1024];
    char *buf_ptr;
    char *word;
    size_t out_idx = 0;
    while (fgets(buf, sizeof(buf), file_ptr)) {
        buf_ptr = buf;
        while ((word = strtok_r(buf_ptr, " \n", &buf_ptr))) {
            if (out_idx > out_length - 1) {
                *return_length = out_idx;
                return true;
            }
            optional_uint32_t color = hex_color_from_string(word);
            if (color.has_value == false) {
                continue;
            }
            out[out_idx++] = color.value;
        }
    }
    *return_length = out_idx;
    fclose(file_ptr);
    return true;
}

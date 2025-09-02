#ifndef _DRAW_H_INCLUDED_
#define _DRAW_H_INCLUDED_

#include <stdint.h>
#include <stddef.h>

#include "image.h"

void draw_color_grid(const image_t *image, uint32_t *colors, size_t colors_length,
                     uint32_t row, uint32_t col, uint32_t px_in_row, uint32_t px_in_col);

#endif

#include <stdio.h>

#include "include/draw.h"
#include "include/hex_color.h"

static inline uint8_t *draw_get_pixel_from_coord(const image_t *image, int x, int y)
{
    return &image->data[(x + y * image->width) * image->bytes];
}

void draw_color_grid_vertically_flipped(const image_t *image, uint32_t *colors,
                                        size_t colors_length, uint32_t row, uint32_t col,
                                        uint32_t px_in_row, uint32_t px_in_col)
{
    (void)row;
    uint8_t *ptr;
    uint8_t color[3];
    size_t idx;
    for (int y = image->height - 1; y >= 0; y--) {
        for (int x = 0; x < image->width; x++) {
            ptr = draw_get_pixel_from_coord(image, x, y);
            idx = (x / px_in_col) + ((image->height - 1 - y) / px_in_row) * col;
            hex_color_split(colors[idx], color);
            if (idx < colors_length) {
                 ptr[0] = color[0];
                 ptr[1] = color[1];
                 ptr[2] = color[2];
            }
            else {
                 ptr[0] = 0;
                 ptr[1] = 0;
                 ptr[2] = 0;
            }
        }
    }
}

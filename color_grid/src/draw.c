#include "include/draw.h"

void draw_color_grid(const image_t *image, uint32_t *colors, size_t colors_length,
                     uint32_t row, uint32_t col, uint32_t px_in_row, uint32_t px_in_col)
{
    (void)row;
    uint8_t *ptr = &image->data[0];
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            size_t idx = ((x / px_in_col) + (y / px_in_row) * col) * 3;
            if (idx < colors_length) {
                 ptr[0] = colors[idx + 0];
                 ptr[1] = colors[idx + 1];
                 ptr[2] = colors[idx + 2];
            }
            else {
                 ptr[0] = 0;
                 ptr[1] = 0;
                 ptr[2] = 0;
            }
            ptr += image->bytes;
        }
    }
}

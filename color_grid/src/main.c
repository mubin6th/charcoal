#include <stdio.h>
#include <stdlib.h>

#include "include/arg.h"
#include "include/read.h"
#include "include/image.h"
#include "include/draw.h"

static const int EXIT_ERROR = 255;

int main(int argc, char **argv)
{
    arg_t *arg = arg_get(argv, argc);
    if (arg->path == NULL) {
        argparse_help_cb_no_exit(&arg->parser, arg->option);
        return EXIT_ERROR;
    }

    uint32_t colors[1024];
    size_t colors_length;
    read_file_for_hex_colors(arg->path, colors,
                             sizeof(colors) / sizeof(uint32_t), &colors_length);
    if (arg->col == -1) {
        arg->col = colors_length;
    }

    image_t image = {
        .data = malloc(arg->col * arg->width * arg->row * arg->height),
        .width = arg->col * arg->width,
        .height = arg->row * arg->height,
        .bytes = 3
    };
    draw_color_grid(&image, colors, colors_length, arg->row, arg->col,
                    arg->height, arg->width);
    image_write(&image, "colorgrid.png");
    image_free(&image);

    return 0;
}

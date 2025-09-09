#include <stdio.h>
#include <stdlib.h>

#include "include/version.h"
#include "include/arg.h"
#include "include/read.h"
#include "include/image.h"
#include "include/draw.h"
#include "include/window.h"
#include "include/gl.h"
#include "include/image_view.h"

static const int EXIT_ERROR = 255;

void run_image_view(arg_t *arg);

int main(int argc, char **argv)
{
    arg_t *arg = arg_get(argv, argc);
    if (arg->version) {
        fprintf(stdout, "colorgrid v%d.%d.%d\n",
                VERSION_MAJOR, VERSION_MINOR,VERSION_PATCH);
        return 0;
    }
    if (arg->path == NULL) {
        argparse_help_cb_no_exit(&arg->parser, arg->option);
        return EXIT_ERROR;
    }

    uint32_t colors[1024];
    size_t colors_length;
    if (!read_file_for_hex_colors(arg->path, colors,
                                  sizeof(colors) / sizeof(uint32_t), &colors_length))
    {
        fprintf(stderr, "error: failed to load file.\n");
        return EXIT_ERROR;
    }
    if (arg->col == -1) {
        arg->col = colors_length;
    }
    if (arg->watch) {
        run_image_view(arg);
        return 0;
    }
    image_t image;
    image_init(&image, arg->col * arg->width, arg->row * arg->height, 3);
    draw_color_grid(&image, colors, colors_length, arg->row, arg->col, arg->height,
                    arg->width);
    image_write(&image, "colorgrid.png");
    image_free(&image);
    return 0;
}

void run_image_view(arg_t *arg)
{
    window_t *window;
    if ((window = window_init(640, 480, "colorgrid")) == NULL) {
        fprintf(stderr, "error: failed to initialize window.\n");
        return;
    }
    if (!gl_init()) {
        fprintf(stderr, "error: failed to initialize opengl.\n");
        return;
    }
    window_process_callbacks();
    image_view_buffer_t view_buffer;
    image_view_init(&view_buffer);
    while (!glfwWindowShouldClose(window->window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        image_view_draw(&view_buffer, window, arg);
        glfwPollEvents();
        glfwSwapBuffers(window->window);
    }
    image_view_deinit(&view_buffer);
    window_deinit();
}

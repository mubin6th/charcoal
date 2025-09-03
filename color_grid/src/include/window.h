#ifndef _WINDOW_H_INCLUDED_
#define _WINDOW_H_INCLUDED_

#include <stdbool.h>
#include "../../include/GLFW/glfw3.h"

typedef struct window_t {
    GLFWwindow *window;
    int width;
    int height;
    char *title;
} window_t;

window_t *window_init(int initial_width, int initial_height, const char *title);
void window_deinit();

#endif

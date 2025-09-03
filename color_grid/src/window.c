#include <string.h>
#include <stdlib.h>

#include "include/window.h"

static window_t window_g;

window_t *window_init(int initial_width, int initial_height, const char *title)
{
    window_g.width = initial_width;
    window_g.height = initial_height;
    size_t title_length = strlen(title) + 1;
    window_g.title = malloc(title_length);
    strncpy(window_g.title, title, title_length);

    if (!glfwInit()) {
        return NULL;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
    window_g.window = glfwCreateWindow(initial_width, initial_height, title, NULL, NULL);
    if (window_g.window == NULL) {
        return NULL;
    }
    glfwMakeContextCurrent(window_g.window);

    return &window_g;
}

void window_deinit()
{
    free(window_g.title);
    glfwDestroyWindow(window_g.window);
}

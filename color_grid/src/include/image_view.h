#ifndef _IMAGE_VIEW_H_INCLUDED_
#define _IMAGE_VIEW_H_INCLUDED_

#include "../../include/glad/glad.h"

typedef struct image_view_buffer_t {
    float vertices[5 * 4];
    GLuint vbo;
    GLuint vao;
} image_view_buffer_t;

void image_view_init(image_view_buffer_t *self);
void image_view_deinit(image_view_buffer_t *self);
void image_view_draw(image_view_buffer_t *self);

#endif

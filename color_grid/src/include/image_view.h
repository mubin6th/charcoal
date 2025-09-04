#ifndef _IMAGE_VIEW_H_INCLUDED_
#define _IMAGE_VIEW_H_INCLUDED_

#include "../../include/glad/glad.h"

typedef struct image_view_vertex_t {
    float pos[3];
    float tex_coords[2];
} image_view_vertex_t;

typedef struct image_view_buffer_t {
    image_view_vertex_t vertices[4];
    GLuint vbo;
    GLuint vao;
} image_view_buffer_t;

void image_view_init(image_view_buffer_t *self);
void image_view_deinit(image_view_buffer_t *self);
void image_view_draw(image_view_buffer_t *self);

#endif

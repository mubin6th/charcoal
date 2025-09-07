#ifndef _IMAGE_VIEW_H_INCLUDED_
#define _IMAGE_VIEW_H_INCLUDED_

#include "image.h"
#include "window.h"
#include "read.h"
#include "arg.h"
#include "../../include/glad/glad.h"
#include "../../include/linmath.h"

typedef struct image_view_vertex_t {
    float pos[3];
    float tex_coords[2];
} image_view_vertex_t;

typedef struct image_view_buffer_t {
    image_view_vertex_t vertices[4];
    GLuint vbo;
    GLuint vao;
    GLuint shader_program;
    linmath_mat4x4 projection;
    linmath_mat4x4 view;
    read_file_change_t file_change_state;
    uint32_t colors[1024];
    size_t colors_length;
    image_t image;
    GLuint texture_id;
    int view_width;
    int view_height;
} image_view_buffer_t;

void image_view_init(image_view_buffer_t *self);
void image_view_deinit(image_view_buffer_t *self);
void image_view_draw(image_view_buffer_t *self, window_t *window, arg_t *arg);

#endif

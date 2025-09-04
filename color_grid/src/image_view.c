#include <stdint.h>
#include <stddef.h>

#include "include/image_view.h"
#include "../include/glad/glad.h"

static inline void image_view_set_vertex_2d(image_view_vertex_t *vertex, float *pos,
                                         float *tex_coords)
{
    vertex->pos[0] = pos[0];
    vertex->pos[1] = pos[1];
    vertex->pos[2] = 0.0f;
    vertex->tex_coords[0] = tex_coords[0];
    vertex->tex_coords[1] = tex_coords[1];
}

void image_view_init(image_view_buffer_t *self)
{
    uint32_t indices[] = {
        0, 1, 2,
        0, 3, 2
    };
    GLuint ebo;
    glGenVertexArrays(1, &self->vao);
    glGenBuffers(1, &self->vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(self->vao);
    glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
    glBufferData(GL_ARRAY_BUFFER, 5 * 4 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(image_view_vertex_t),
                          offsetof(image_view_vertex_t, pos));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(image_view_vertex_t),
                          offsetof(image_view_vertex_t, tex_coords));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &ebo);
}

void image_view_deinit(image_view_buffer_t *self)
{
    glDeleteVertexArrays(1, &self->vao);
    glDeleteBuffers(1, &self->vbo);
}

void image_view_draw(image_view_buffer_t *self)
{
    // example data
    image_view_set_vertex_2d(&self->vertices[0], (float[2]){-0.5f, 0.5f},
                             (float[2]){0.0f, 1.0f});
    image_view_set_vertex_2d(&self->vertices[1], (float[2]){-0.5f,-0.5f},
                             (float[2]){0.0f, 0.0f});
    image_view_set_vertex_2d(&self->vertices[2], (float[2]){ 0.5f,-0.5f},
                             (float[2]){1.0f, 0.0f});
    image_view_set_vertex_2d(&self->vertices[3], (float[2]){ 0.5f, 0.5f},
                             (float[2]){1.0f, 1.0f});

    glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(self->vertices), self->vertices);
    glBindVertexArray(self->vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

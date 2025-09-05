#include <stdint.h>
#include <stddef.h>

#include "include/image_view.h"
#include "include/shader.h"
#include "../include/glad/glad.h"

static const double pi = 3.141592653589793238;

static const char *image_view_vertex_shader =
    "#version 330\n"
    "layout (location = 0) in vec3 pos;\n"
    "layout (location = 1) in vec2 tex_coords;\n"
    "out vec2 v_tex_coords;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projection * view * vec4(pos, 1.0f);\n"
    "   v_tex_coords = tex_coords;\n"
    "}"
;
static const char *image_view_fragment_shader =
    "#version 330\n"
    "out vec4 out_color;\n"
    "in vec2 v_tex_coords;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   out_color = vec4(v_tex_coords.x, v_tex_coords.y, 0.0f, 1.0f);\n"
    "}"
;

static inline void image_view_set_vertex_2d(image_view_vertex_t *vertex, float *pos,
                                         float *tex_coords)
{
    vertex->pos[0] = pos[0];
    vertex->pos[1] = pos[1];
    vertex->pos[2] = 0.0f;
    vertex->tex_coords[0] = tex_coords[0];
    vertex->tex_coords[1] = tex_coords[1];
}

void image_view_init(image_view_buffer_t *self, window_t *window)
{
    self->window = window;
    self->shader_program = shader_init(image_view_vertex_shader,
                                       image_view_fragment_shader);
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(self->vertices), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(image_view_vertex_t),
                          (void*)offsetof(image_view_vertex_t, pos));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(image_view_vertex_t),
                          (void*)offsetof(image_view_vertex_t, tex_coords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &ebo);

    linmath_mat4x4_identity(self->projection);
    linmath_mat4x4_perspective(self->projection, 120.0f * (pi / 180),
                               (float)self->window->width / self->window->height,
                               0.1f, 100.0f);
}

void image_view_deinit(image_view_buffer_t *self)
{
    glDeleteVertexArrays(1, &self->vao);
    glDeleteBuffers(1, &self->vbo);
}

void image_view_draw(image_view_buffer_t *self)
{
    linmath_mat4x4_identity(self->view);
    linmath_mat4x4_translate(self->view, 0.0f, 0.0f, -2.0f);
    glUniformMatrix4fv(glGetUniformLocation(self->shader_program, "view"), 1,
                       GL_FALSE, &self->view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(self->shader_program, "projection"), 1,
                       GL_FALSE, &self->projection[0][0]);

    // example data
    image_view_set_vertex_2d(&self->vertices[0], (float[2]){-0.5f, 0.5f},
                             (float[2]){0.0f, 1.0f});
    image_view_set_vertex_2d(&self->vertices[1], (float[2]){-0.5f,-0.5f},
                             (float[2]){0.0f, 0.0f});
    image_view_set_vertex_2d(&self->vertices[2], (float[2]){ 0.5f,-0.5f},
                             (float[2]){1.0f, 0.0f});
    image_view_set_vertex_2d(&self->vertices[3], (float[2]){ 0.5f, 0.5f},
                             (float[2]){1.0f, 1.0f});

    glUseProgram(self->shader_program);
    glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(self->vertices), self->vertices);
    glBindVertexArray(self->vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

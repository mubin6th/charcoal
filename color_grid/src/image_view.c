#include <stdint.h>
#include <stddef.h>

#include "include/image_view.h"
#include "include/shader.h"
#include "include/draw.h"
#include "include/texture.h"
#include "../include/glad/glad.h"

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
    "uniform sampler2D texture_0;\n"
    "void main()\n"
    "{\n"
    "   out_color = texture(texture_0, v_tex_coords);\n"
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


static inline void image_view_get_view_size(image_view_buffer_t *self)
{
    if (self->window->width / self->image.aspect_ratio <= self->window->height) {
        self->view_width = self->window->width;
        self->view_height = self->window->width / self->image.aspect_ratio;
        return;
    }
    self->view_width = self->window->height * self->image.aspect_ratio;
    self->view_height = self->window->height;
}

void image_view_init(image_view_buffer_t *self, window_t *window)
{
    self->window = window;
    self->shader_program = shader_init(image_view_vertex_shader,
                                       image_view_fragment_shader);
    self->file_change_state.file_last_change_date = 0;
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
}

void image_view_deinit(image_view_buffer_t *self)
{
    glDeleteVertexArrays(1, &self->vao);
    glDeleteBuffers(1, &self->vbo);
}

void image_view_draw(image_view_buffer_t *self, arg_t *arg)
{
    if (read_file_for_hex_color_changes(&self->file_change_state, 0.15f, arg->path,
                                        self->colors,
                                        sizeof(self->colors) / sizeof(uint32_t),
                                        &self->colors_length))
    {
        int row = ceil((double)self->colors_length / arg->col);
        image_init(&self->image, arg->width * arg->col, arg->height * row, 3);
        draw_color_grid_vertically_flipped(&self->image, self->colors,
                                           self->colors_length, row, arg->col,
                                           arg->height, arg->width);
        texture_deinit(&self->texture_id);
        texture_init(&self->texture_id, &self->image);
        image_free(&self->image);
    }

    linmath_mat4x4_identity(self->view);
    linmath_mat4x4_identity(self->projection);
    linmath_mat4x4_translate(self->view, 0.0f, 0.0f, -1.0f);
    linmath_mat4x4_ortho(self->projection,
                         -self->window->width / 2.0f, self->window->width / 2.0f,
                         -self->window->height / 2.0f, self->window->height / 2.0f,
                         0.1f, 100.0f);

    glUniformMatrix4fv(glGetUniformLocation(self->shader_program, "view"), 1,
                       GL_FALSE, &self->view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(self->shader_program, "projection"), 1,
                       GL_FALSE, &self->projection[0][0]);

    image_view_get_view_size(self);
    image_view_set_vertex_2d(&self->vertices[0],
                             (float[2]){
                                 -(float)self->view_width / 2,
                                  (float)self->view_height / 2
                             },
                             (float[2]){0.0f, 1.0f});
    image_view_set_vertex_2d(&self->vertices[1],
                             (float[2]){
                                 -(float)self->view_width / 2,
                                 -(float)self->view_height / 2
                             },
                             (float[2]){0.0f, 0.0f});
    image_view_set_vertex_2d(&self->vertices[2],
                             (float[2]){
                                  (float)self->view_width / 2,
                                 -(float)self->view_height / 2
                             },
                             (float[2]){1.0f, 0.0f});
    image_view_set_vertex_2d(&self->vertices[3],
                             (float[2]){
                                  (float)self->view_width / 2,
                                  (float)self->view_height / 2
                             },
                             (float[2]){1.0f, 1.0f});

    texture_bind(&self->texture_id, 0);
    glUseProgram(self->shader_program);
    glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(self->vertices), self->vertices);
    glBindVertexArray(self->vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

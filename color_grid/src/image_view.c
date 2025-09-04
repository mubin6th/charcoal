#include <stdint.h>
#include <stddef.h>

#include "include/image_view.h"
#include "../include/glad/glad.h"

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void*)(3 * sizeof(float)));
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
    glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 5 * 4 * sizeof(float), self->vertices);
    glBindVertexArray(self->vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

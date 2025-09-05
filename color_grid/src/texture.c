#include "include/texture.h"

bool texture_init(GLuint *self, image_t *image)
{
    if (image->data == NULL) {
        return false;
    }
    glGenTextures(1, self);
    glBindTexture(GL_TEXTURE_2D, *self);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, image->data);
    glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}

void texture_bind(GLuint *self, size_t slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, *self);
}

void texture_deinit(GLuint *self)
{
    glDeleteTextures(1, self);
}

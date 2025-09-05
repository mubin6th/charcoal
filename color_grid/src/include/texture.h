#ifndef _TEXTURE_H_INCLUDED_
#define _TEXTURE_H_INCLUDED_

#include <stddef.h>
#include <stdbool.h>

#include "image.h"
#include "../../include/glad/glad.h"

bool texture_init(GLuint *self, image_t *image);
void texture_bind(GLuint *self, size_t slot);
void texture_deinit(GLuint *self);

#endif

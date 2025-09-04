#ifndef _SHADER_H_INCLUDED_
#define _SHADER_H_INCLUDED_

#include "../../include/glad/glad.h"

GLuint shader_init(const char *vertex_shader, const char *fragment_shader);
void shader_deinit(GLuint *shader_program);

#endif

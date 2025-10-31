#include <stdio.h>
#include "include/shader.h"

static void shader_print_error_if_any(FILE *stream, GLuint shader,
        GLenum shader_type)
{
    int success;
    char buf[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success) {
        return;
    }
    glGetShaderInfoLog(shader, sizeof(buf), NULL, buf);
    const char *shader_type_string =
        (shader_type == GL_VERTEX_SHADER ? "vertex_shader" : "fragment_shader");
    fprintf(stream, "[error][%s]: %s", shader_type_string, buf);
}

GLuint shader_init(const char *vertex_shader,
        const char *fragment_shader)
{
    GLuint vertex_shader_bin = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_bin = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertex_shader_bin, 1, &vertex_shader, NULL);
    glShaderSource(fragment_shader_bin, 1, &fragment_shader, NULL);
    glCompileShader(vertex_shader_bin);
    glCompileShader(fragment_shader_bin);
    shader_print_error_if_any(stderr, vertex_shader_bin, GL_VERTEX_SHADER);
    shader_print_error_if_any(stderr, fragment_shader_bin, GL_FRAGMENT_SHADER);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader_bin);
    glAttachShader(shader_program, fragment_shader_bin);
    glLinkProgram(shader_program);

    glDeleteShader(vertex_shader_bin);
    glDeleteShader(fragment_shader_bin);
    return shader_program;
}

void shader_deinit(GLuint *shader_program)
{
    glDeleteProgram(*shader_program);
}

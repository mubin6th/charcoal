#include "include/gl.h"
#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"

bool gl_init()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return false;
    }
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    return true;
}

#include "include/engine_clock.h"
#include "../include/GLFW/glfw3.h"

inline void engine_clock_set_current(engine_clock_t *self)
{
    self->current = glfwGetTime();
}

inline void engine_clock_refresh(engine_clock_t *self)
{
    self->last = self->current;
    self->current = glfwGetTime();
    self->delta = self->current - self->last;
}

#ifndef _CLOCK_H_INCLUDED_
#define _CLOCK_H_INCLUDED_

typedef struct engine_clock_t {
    float current;
    float last;
    float delta;
} engine_clock_t;

void engine_clock_set_current(engine_clock_t *self);
void engine_clock_refresh(engine_clock_t *self);

#endif

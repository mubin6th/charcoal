#ifndef _OPTIONAL_H_INCLUDED_
#define _OPTIONAL_H_INCLUDED_

#include <stdbool.h>
#include <stdint.h>

// willing to write features of C++
// but not write in C++.

#define optional_t_generate_M(type, name) \
    typedef struct optional_##name##_t { \
        type value; \
        bool has_value; \
    } optional_##name##_t

optional_t_generate_M(uint32_t, uint32);

#endif

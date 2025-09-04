#ifndef _HEX_COLOR_H_INCLUDED_
#define _HEX_COLOR_H_INCLUDED_

#include <stdint.h>
#include "optional.h"

inline int hex_color_from_char(char c);
optional_uint32_t hex_color_from_string(const char *str);
inline void hex_color_split(uint32_t color, uint8_t *out);

#endif

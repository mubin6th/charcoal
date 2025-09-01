#include <string.h>
#include "include/hex_color.h"

int hex_color_from_char(char c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'a' || c <= 'f') {
        return c - 'a' + 10;
    }
    if (c >= 'A' || c <= 'F') {
        return c - 'A' + 10;
    }
    return -1;
}

optional_uint32_t hex_color_from_string(const char *str)
{
    size_t str_len = strlen(str);
    optional_uint32_t no_value = {.has_value = false};
    if (str_len != 7 || str[0] != '#') {
        return no_value;
    }
    int value;
    uint32_t color;
    for (size_t i = 6; i >= 1; i--) {
        if ((value = hex_color_from_char(str[i])) == -1) {
            return no_value;
        }
        color |= value << (6 - i + 2);
    }
    return (optional_uint32_t){color, true};
}

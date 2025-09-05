#ifndef _IMAGE_H_INCLUDED_
#define _IMAGE_H_INCLUDED_

#include <stdint.h>
#include <stdbool.h>

typedef struct image_t {
    uint8_t *data;
    int width;
    int height;
    int bytes;
} image_t;

bool image_init(image_t *self, int width, int height, int bytes);
void image_write(image_t *self, const char *path);
void image_free(image_t *self);

#endif

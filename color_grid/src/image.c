#include <stdint.h>
#include <string.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

#include "include/image.h"

bool image_init(image_t *self, int width, int height, int bytes)
{
    *self = (image_t){
        .width = width,
        .height = height,
        .aspect_ratio = (double)width / height,
        .bytes = bytes,
        .data = malloc(width * height * bytes),
    };
    return self->data != NULL;
}

void image_write(image_t *self, const char *path)
{
    size_t path_size = strlen(path);
    size_t k = 0;
    for (size_t i = path_size - 1; i >= 0; i--) {
        if (path[i] == '.') {
            k = i + 1;
            break;
        }
    }
    if (!k) {
        return;
    }

    const char *type = &path[k];
    if (strcmp(type, "jpg") == 0 || strcmp(type, "jpeg") == 0) {
        // if quality is 100 then the filesize tends to be much bigger than original.
        stbi_write_jpg(path, self->width, self->height, self->bytes, self->data, 90);
    }
    else if (strcmp(type, "png") == 0) {
        stbi_write_png(path, self->width, self->height, self->bytes, self->data,
                       self->width * self->bytes);
    }
    else if (strcmp(type, "bmp") == 0) {
        stbi_write_bmp(path, self->width, self->height, self->bytes, self->data);
    }
    else if (strcmp(type, "tga") == 0) {
        stbi_write_tga(path, self->width, self->height, self->bytes, self->data);
    }
}

void image_free(image_t *self)
{
    free(self->data);
}

#include <stdio.h>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"
#include "../include/argparse.h"

// we use variable instead of macros when possible.
const int EXIT_ERR = 255;

typedef struct _Image {
    uint8_t *data;
    int width;
    int height;
    int bytes;
} Image;
typedef struct _TileData {
    int r, c, w, h;
} TileData;

void getWritePath(const char *path, char *out);
void loadImage(Image *self, const char *path);
void writeImage(Image *self, const char *path);
void freeImage(Image *self);
uint32_t getColorHexFromChar(char c);
void drawColorGrid(Image *img,
                   int r, int c,
                   int px_in_row, int px_in_col,
                   uint8_t *color_list, size_t color_list_len);

int main(int argc, char **argv) {
    const char *input_path = NULL;
    TileData tile_data = {
        .c = 0,
        .r = 1,
        .w = 64,
        .h = 64
    };

    const char *const usages[] = {
        "colorgrid [arguments] [parameters]",
        NULL
    };
    struct argparse_option arg_options[] = {
        OPT_STRING('i', "input", &input_path, "path to text file.",
                   NULL, 0, 0),
        OPT_INTEGER('r', "rows", &tile_data.r,
                   "the number of rows. default: 9.",
                   NULL, 0, 0),
        OPT_INTEGER('c', "columns", &tile_data.c,
                   "the number of columns. default: 9.",
                   NULL, 0, 0),
        OPT_INTEGER('x', "width", &tile_data.w,
                   "tile width. default: 64.",
                   NULL, 0, 0),
        OPT_INTEGER('y', "height", &tile_data.h,
                   "tile height. default: 64.",
                   NULL, 0, 0),
        OPT_HELP(),
        OPT_END()
    };
    struct argparse arg_parser;
    argparse_init(&arg_parser, arg_options, usages, 0);
    argparse_describe(&arg_parser,
                      "A program to take hex separated colors from "
                      "file and make a color grid.", NULL);
    argparse_parse(&arg_parser, argc, (const char **)argv);

    if (input_path == NULL) {
        argparse_help_cb_no_exit(&arg_parser, arg_options);
        return EXIT_ERR;
    }

    FILE *file_ptr;
    if ((file_ptr = fopen(input_path, "r")) == NULL) {
        fprintf(stderr, "error: failed to load file.\n");
        return EXIT_ERR;
    }

    char line_buf[1 << 7];
    char *line_ptr;
    char *word;
    uint8_t color_arr[(1 << 10) * 3];
    uint8_t crnt_color[3];
    size_t color_arr_idx = 0;

    while ((fgets(line_buf, sizeof(line_buf), file_ptr)) != NULL) {
        line_ptr = line_buf;
        while ((word = strtok_r(line_ptr, " \n", &line_ptr))) {
            size_t word_len = strlen(word);

            if (word_len != 7 || word[0] != '#') {
                continue;
            }
            char flag = 0;
            memset(crnt_color, 0, sizeof(crnt_color));
            uint8_t *crnt_color_ptr = &crnt_color[0];
            for (size_t i = 1; i < word_len; i++) {
                if ((line_buf[i] < '0' || line_buf[i] > '9') &&
                    (line_buf[i] < 'a' || line_buf[i] > 'f') &&
                    (line_buf[i] < 'A' || line_buf[i] > 'F'))
                {
                    flag = 1;
                    break;
                }
                if (i % 2 == 1 && i != 1) {
                    crnt_color_ptr++;
                }
                *crnt_color_ptr |=
                    getColorHexFromChar(line_buf[i])
                    << (i % 2 ? 4 : 0);
            }

            if (!flag) {
                color_arr[color_arr_idx + 0] = crnt_color[0];
                color_arr[color_arr_idx + 1] = crnt_color[1];
                color_arr[color_arr_idx + 2] = crnt_color[2];

                color_arr_idx += 3;
            }
        }
    }

    fclose(file_ptr);

    if (!tile_data.c) {
        tile_data.c = color_arr_idx / 3;
    }

    Image img;
    drawColorGrid(&img,
                  tile_data.r, tile_data.c,
                  tile_data.h, tile_data.w,
                  color_arr, color_arr_idx);
    writeImage(&img, "colorgrid.png");
    freeImage(&img);

    return 0;
}

void loadImage(Image *self, const char *path) {
    self->data = stbi_load(path,
                           &self->width, &self->height,
                           &self->bytes, 0);
}

void writeImage(Image *self, const char *path) {
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
        // if quality is 100 then the filesize tends to be
        // much bigger than original.
        stbi_write_jpg(path, self->width, self->height, self->bytes,
                       self->data, 90);
    }
    else if (strcmp(type, "png") == 0) {
        stbi_write_png(path, self->width, self->height, self->bytes,
                       self->data, self->width * self->bytes);
    }
    else if (strcmp(type, "bmp") == 0) {
        stbi_write_bmp(path, self->width, self->height, self->bytes,
                       self->data);
    }
    else if (strcmp(type, "tga") == 0) {
        stbi_write_tga(path, self->width, self->height, self->bytes,
                       self->data);
    }
}

void freeImage(Image *self) {
    free(self->data);
}

uint32_t getColorHexFromChar(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    else if (c >= 'a' || c <= 'f') {
        return c - 'a' + 10;
    }
    else if (c >= 'A' || c <= 'F') {
        return c - 'A' + 10;
    }

    return UINT32_MAX;
}

void drawColorGrid(Image *img,
                   int r, int c,
                   int px_in_row, int px_in_col,
                   uint8_t *color_list, size_t color_list_len)
{
    img->width = c * px_in_col;
    img->height = r * px_in_row;
    img->bytes = 3;
    img->data = malloc(img->width * img->height * img->bytes);

    uint8_t *ptr = &img->data[0];
    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            size_t idx = ((x / px_in_col) +
                          (y / px_in_row) * c) * 3;

            if (idx < color_list_len) {
                 ptr[0] = color_list[idx + 0];
                 ptr[1] = color_list[idx + 1];
                 ptr[2] = color_list[idx + 2];
            }
            else {
                 ptr[0] = 0;
                 ptr[1] = 0;
                 ptr[2] = 0;
            }

            ptr += img->bytes;
        }
    }
}

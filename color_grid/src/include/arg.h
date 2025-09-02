#ifndef _ARG_H_INCLUDED_
#define _ARG_H_INCLUDED_

#include "../../include/argparse.h"

typedef struct arg_t {
    struct argparse parser;
    struct argparse_option *option;
    const char *path;
    int row;
    int col;
    int width;
    int height;
} arg_t;

arg_t *arg_get(char **argv, int argc, char *usage, struct argparse_option *options);

#endif

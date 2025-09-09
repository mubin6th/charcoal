#include <stddef.h>
#include "include/arg.h"

static arg_t arg_g = {
    .path = NULL,
    .row = 1,
    .col = -1,
    .width = 64,
    .height = 64,
    .watch = false,
    .version = false
};
static const char *arg_description =
    "A program to take hex separated colors from file and make a color grid.";
static const char *const arg_usages[] = {
    "colorgrid [arguments...]",
    NULL
};
static struct argparse_option arg_options[] = {
    OPT_STRING('i', "input", &arg_g.path, "path to text file.", NULL, 0, 0),
    OPT_INTEGER('r', "rows", &arg_g.row, "the number of rows. default: 1. "
                "row is arbitary on watch mode.", NULL, 0,
                0),
    OPT_INTEGER('c', "columns", &arg_g.col, "the number of columns. default: 0.",
                NULL, 0, 0),
    OPT_INTEGER('x', "width", &arg_g.width, "tile width. default: 64.", NULL, 0, 0),
    OPT_INTEGER('y', "height", &arg_g.height, "tile height. default: 64.", NULL, 0,
                0),
    OPT_BOOLEAN('w', "watch", &arg_g.watch, "preview changes to color palette. helpful "
                "when editing.", NULL, 0, 0),
    OPT_BOOLEAN('v', "version", &arg_g.version, "print version of colorgrid.", NULL, 0,
                0),
    OPT_HELP(),
    OPT_END()
};


arg_t *arg_get(char **argv, int argc)
{
    arg_g.option = arg_options;
    argparse_init(&arg_g.parser, arg_options, arg_usages, 0);
    argparse_describe(&arg_g.parser, arg_description, NULL);
    argparse_parse(&arg_g.parser, argc, (const char **)argv);
    return &arg_g;
}

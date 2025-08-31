# colorgrid

A tool to generate image from a colorscheme file.

A colorscheme file can be any file where hex colors are separated by spaces. The colors
can be in every newline or in between paragraphs.

The help command of the tool below:
```
Usage: colorgrid [arguments] [parameters]
A program to take hex separated colors from file and make a color grid.

    -i, --input=<str>     path to text file.
    -r, --rows=<int>      the number of rows. default: 1.
    -c, --columns=<int>   the number of columns. default: 0.
    -x, --width=<int>     tile width. default: 64.
    -y, --height=<int>    tile height. default: 64.
    -h, --help            show this help message and exit.
```

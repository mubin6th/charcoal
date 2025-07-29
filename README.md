<div align="center">
    <h1>charcoal</h1>
    <p>A calm, dark, yet bright color scheme.</p>

**[Preview] | [Install] | [Contribute]**
</div>

## Preview
`will be added soon...`

## Install
Currently the theme is only available Neovim. The
(echasnovski/mini.nvim)[https://github.com/echasnovski/mini.nvim] plugin set is used for
this colorscheme. To install the theme, add the following to your **lazy.nvim**:
```lua
{ -- Collection of various small independent plugins/modules
    "echasnovski/mini.nvim",
    config = function()
        require("mini.base16").setup({
            palette = {
                base00 = "#120f09", -- background
                base01 = "#1e1812", -- brigher background (for status bars, line number,
                --                     folding marks)
                base02 = "#35291d", -- selection background
                base03 = "#66553f", -- comments, invisibles, line highlighting
                base04 = "#a28662", -- dark foreground (for status bars)
                base05 = "#c0a179", -- foreground
                base06 = "#d6b891", -- bright foreground
                base07 = "#292016", -- bright background
                base08 = "#887254", -- variables, xml tags, markup link text, markup lists,
                --                     diff deleted
                base09 = "#d6b891", -- integer, boolean, constants, xml attributes, markup link
                --                     url
                base0A = "#c0a179", -- classes, markup bold, search text background
                base0B = "#927a60", -- strings, inherited class, markup code, diff inserted
                base0C = "#a28662", -- data types, support, regular expressions,
                --                     escape characters, markup, quotes
                base0D = "#d6b891", -- functions, methods, attribute ids, headings
                base0E = "#a28662", -- keywords, storage, selector, markup italic, diff changed
                base0F = "#887254", -- deprecated, opening/closing embedded language tags,
                --                     e.g. `<?php ?>`
            },
            use_cterm = true,
            plugins = {
                default = false,
                ["echasnovski/mini.nvim"] = true,
            },
        })
    end,
},
```

## Contribute
Currently, there are no accent color to the theme. I would like to add accent colors as
they are sometimes required for applications. If you want to **suggest** any change to
the palette, let me know. I will kindly take your opinion, Insha'allah.

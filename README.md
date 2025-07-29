<div align="center">
    <h1>charcoal</h1>
    <p>A calm, dark, yet bright color scheme.</p>

**[Preview] | [Install] | [Contribute]**
</div>

## Preview
`will be added soon...`

## Install
Currently the theme is only available Neovim. The
[echasnovski/mini.nvim](https://github.com/echasnovski/mini.nvim) plugin set is used for
this colorscheme. To install the theme, add the following to your **lazy.nvim**:
```lua
{
    "echasnovski/mini.nvim",
    config = function()
        require("mini.base16").setup({
            palette = {
                base00 = "#120f09",
                base01 = "#1e1812",
                base02 = "#35291d",
                base03 = "#66553f",
                base04 = "#a28662",
                base05 = "#c0a179",
                base06 = "#d6b891",
                base07 = "#292016",
                base08 = "#887254",
                base09 = "#d6b891",
                base0A = "#c0a179",
                base0B = "#927a60",
                base0C = "#a28662",
                base0D = "#d6b891",
                base0E = "#a28662",
                base0F = "#887254",
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

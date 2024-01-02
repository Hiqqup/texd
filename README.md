Deviations from vim (probably a lot more than listed here):

scrolling is acually reasonable when having multiple lines, dont care put this in you vim config:
```lua 
vim.keymap.set('n', 'k', "v:count == 0 ? 'gk' : 'k'", { expr = true, silent = true })
vim.keymap.set('n', 'j', "v:count == 0 ? 'gj' : 'j'", { expr = true, silent = true })
```


### TODO:
- implement multiple lines for command

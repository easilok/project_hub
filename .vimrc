" set tabstop=4
" set softtabstop=4
" set shiftwidth=4
" set noexpandtab

" set colorcolumn=90
" highlight ColorColumn ctermbg=lightgray

packadd termdebug
let g:termdebug_popup = 1
let g:termdebug_wide = 163

let &path.="inc,lib,../inc,"

set makeprg=make\ -C\ src

" let g:loaded_youcompleteme = 1
let g:ycm_filepath_completion_use_working_dir = 0

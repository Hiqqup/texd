
#include "key.h"


void key_process_input(int c, struct Buffer* buf)
{
    switch (buf->mode) {
    case MODE_INSERT:
        switch (c) {
        case 'h':
            buf->term_x--;
            break;
        case 'l':
            buf->term_x++;
            break;
        case 'j':
            if (buf->term_y < buf->term_rows) {
                buf->term_y++;
            } else
                buf->first = list_mov_xy(0, 1, buf->term_cols, buf->first);
            break;
        case 'k':
            if (buf->term_y > 0) {
                buf->term_y--;
            } else
                buf->first = list_mov_xy(0, -1, buf->term_cols, buf->first);
            break;
        }
        break;
    }
}

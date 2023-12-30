
#include "key.h"

void scroll_next(struct Buffer* buf)
{
    node_t* cur = buf->first;
    cur = cur->next;
    int col = 0;
    while (cur->val != '\n' && cur->val != LIST_STOPPER && col++ < buf->term_cols - 1) {
        cur = cur->next;
    }
    node_t* tmp = cur;

    if (tmp->val == LIST_STOPPER)
        return;
    buf->first = tmp;
}

void scroll_prev(struct Buffer* buf)
{
    if (buf->first->val == LIST_STOPPER)
        return;

    node_t* cur = buf->first;
    cur = cur->prev;
    int col = 0;
    while (cur->val != '\n' && cur->val != LIST_STOPPER && col++ < buf->term_cols - 1) {
        cur = cur->prev;
    }
    buf->first = cur;
}


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
                buf->first = list_mov_xy(0, 2, buf->term_cols, buf->first);
            break;
        case 'k':
            if (buf->term_y > 0) {
                buf->term_y--;
            } else
                buf->first = list_mov_xy(0, -2, buf->term_cols, buf->first);
            break;
        }
        break;
    }
}

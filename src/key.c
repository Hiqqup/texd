
#include "list.h"

void move_cursor(struct Buffer* buf, int direction)
{ /* 1 for down -1 for up*/
    if ((direction == 1 && buf->term_y < buf->term_rows) || (direction == -1 && buf->term_y > 0)) {
        buf->term_y += direction;
    } else
        buf->first = list_mov_y(direction, buf->term_cols, buf->first);
    buf->current_linebreak = list_mov_y(direction, buf->term_cols, buf->current_linebreak);
    int dist = list_offset_from_y(1, buf->term_cols, buf->current_linebreak) - 1;
    dist = dist < buf->wanabe_x ? dist : buf->wanabe_x;
    buf->term_x = dist;
    buf->current = list_mov_offset(buf->current_linebreak, dist);
}
void move_cursor_up(struct Buffer* buf)
{
    if (buf->term_y > 0) {
        buf->current_linebreak = list_mov_y(-1, buf->term_cols, buf->current_linebreak);
        buf->term_y--;
    } else
        buf->first = list_mov_y(-1, buf->term_cols, buf->first);
}

void key_process_input(int c, struct Buffer* buf)
{
    switch (buf->mode) {
    case MODE_INSERT:
        switch (c) {
        case 'h':
            if (buf->term_x != 0) {
                buf->wanabe_x--;
                buf->term_x--;
                buf->current = buf->current->prev;
            };
            break;
        case 'l':
            if (buf->current->next != list_mov_y(1, buf->term_cols, buf->current_linebreak)) {
                buf->wanabe_x++;
                buf->term_x++;
                buf->current = buf->current->next;
            }
            break;
        case 'j':
            if (list_mov_y(2, buf->term_cols, buf->current_linebreak)->val != LIST_STOPPER)
                move_cursor(buf, 1);

            break;
        case 'k':
            move_cursor(buf, -1);
            break;
        }
        break;
    }
}

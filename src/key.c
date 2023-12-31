
#include "key.h"
#include "list.h"
// tmp
// #include<stdio.h>

void move_cursor_vert(struct Buffer* buf, int direction)
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
void move_cursor_right(struct Buffer* buf)
{
    buf->wanabe_x++;
    buf->term_x++;
    buf->current = buf->current->next;
}
void move_cursor_right_block(struct Buffer* buf)
{
    if (buf->current->next->next != list_mov_y(1, buf->term_cols, buf->current_linebreak)) {
        move_cursor_right(buf);
    }
}
void move_cursor_right_line(struct Buffer* buf)
{
    if (buf->current->next != list_mov_y(1, buf->term_cols, buf->current_linebreak)) {
        move_cursor_right(buf);
    }
}
void move_cursor_left(struct Buffer* buf)
{
    if (buf->term_x != 0) {
        buf->wanabe_x--;
        buf->term_x--;
        buf->current = buf->current->prev;
    };
}

void key_process_input(int c, struct Buffer* buf)
{
    switch (buf->mode) {
    case MODE_NORMAL:
        switch (c) {
        case 'h':
            move_cursor_left(buf);
            break;
        case 'l':
            move_cursor_right_block(buf);
            break;
        case 'j':
            if (list_mov_y(2, buf->term_cols, buf->current_linebreak)->val != LIST_STOPPER)
                move_cursor_vert(buf, 1);
            break;
        case 'k':
            move_cursor_vert(buf, -1);
            break;
        case 'i':
            buf->mode = MODE_INSERT;
            break;
        case 'a':
            move_cursor_right_line(buf);
            buf->mode = MODE_INSERT;
            break;
        }
        break;
    case MODE_INSERT:
        if (!iscntrl(c)) {
            list_insert(buf->current, c);
            move_cursor_right_line(buf);
            return;
        }

        // printf("%d\n",c);
        switch (c) {
        case KEY_ENTER:
            list_insert(buf->current, '\n');
            buf->wanabe_x = 0;
            move_cursor_vert(buf, 1);
            break;
        case KEY_ESC:
            move_cursor_left(buf);
            buf->mode = MODE_NORMAL;
            break;
        case KEY_BACKSPACE:
            if (buf->current->prev) {
                buf->current = buf->current->prev;
                list_delete(buf->current, buf->current->next->next);
                buf->wanabe_x--;
                buf->term_x--;
            }
            break;
        }
        break;
    case MODE_COMMAND:
        break;
    }
}

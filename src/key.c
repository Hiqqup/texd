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
    if (dist)
        dist--;
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
    node_t* next_lb = list_mov_y(1, buf->term_cols, buf->current_linebreak);
    if (buf->current->next != next_lb && buf->current->next->next != next_lb) {
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

void exit_command_mode(struct Buffer* buf)
{
    buf->term_y = buf->before_command_y;
    buf->term_x = buf->before_command_x;
    buf->mode = MODE_NORMAL;
}
void backspace_delete(struct Buffer* buf)
{
    int i = 0;
    do{
    if (buf->current->val == '\n') {
        buf->wanabe_x = buf->term_cols;
        move_cursor_vert(buf, -1);
        buf->wanabe_x = buf->term_x;
        move_cursor_right_line(buf);
        list_delete(buf->current, buf->current->next->next);
    } else if (buf->current->val != LIST_STOPPER) {
        move_cursor_left(buf);
        list_delete(buf->current, buf->current->next->next);
    }
    }while (i++ <3 && buf->current->val == ' ');
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
        case ':':
            buf->before_command_y = buf->term_y;
            buf->before_command_x = buf->term_x;
            buf->term_y = buf->term_rows + 1;
            buf->term_x = 1;
            buf->command[0] = ':';
            buf->mode = MODE_COMMAND;
            break;
        }
        break;
    case MODE_INSERT:
        if (!iscntrl(c)) {
            list_insert(buf->current, c);
            move_cursor_right_line(buf);
            return;
        }

        switch (c) {
        case KEY_TAB:
            list_insert(buf->current, ' ');
            move_cursor_right_line(buf);
            for (int i = 0; i < buf->editor_tabwidth && buf->term_x % buf->editor_tabwidth != 0; i++) {
                list_insert(buf->current, ' ');
                move_cursor_right_line(buf);
            }
            break;
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
                backspace_delete(buf);
            break;
        }
        break;
    case MODE_COMMAND:
        if (!iscntrl(c)) {
            buf->command[buf->term_x++] = c;
        }
        switch (c) {
        case KEY_BACKSPACE:
            if (buf->term_x > 1)
                buf->term_x--;
            else
                exit_command_mode(buf);
            break;
        case KEY_ENTER:
            buf->command[buf->term_x] = '\0';
            command_execute(buf);
            exit_command_mode(buf);
            break;
            /* intentionally no break*/
        case KEY_ESC:
            exit_command_mode(buf);
            break;
        }
        break;
    }
}

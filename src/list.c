#include "list.h"
node_t* list_init()
{
    node_t* first = malloc(sizeof(node_t));
    node_t* last = malloc(sizeof(node_t));
    if (first == NULL || last == NULL)
        die("malloc - list init");
    first->val = LIST_STOPPER;
    last->val = LIST_STOPPER;
    first->next = last;
    last->prev = first;
    return first;
}
node_t* list_insert(node_t* node, LIST_VAL_T c)
{
    node_t* ins = malloc(sizeof(node_t));
    if (ins == NULL)
        die("malloc - list insert");
    ins->val = c;
    node->next->prev = ins;
    ins->next = node->next;
    ins->prev = node;
    node->next = ins;
    return ins;
}
void list_free(node_t* entry)
{
    node_t* right = entry->next;
    while (right->val != LIST_STOPPER) {
        right = right->next;
        free(right->prev);
    }
    free(right);
    while (entry->val != LIST_STOPPER) {
        entry = entry->prev;
        free(entry->next);
    }
    free(entry);
}
node_t* move_ptr_line(node_t* start, bool up, int* steps_it_took, unsigned short int width)
{
    int col = 0;
    if (!up) {
        if (start->next == NULL)
            return start;
        start = start->next;
        (*steps_it_took)++;
        while (start->val != LIST_STOPPER && start->val != '\n' && col++ < width - 1) {
            start = start->next;
            (*steps_it_took)++;
        }
        if (start->val != '\n' && start->next->val == '\n') {
            (*steps_it_took)++;
            return start->next;
        } // to deal with lines that are exactly with long
    } else {
        if (start->prev == NULL)
            return start;
        start = start->prev;
        (*steps_it_took)--;
        while (start->val != LIST_STOPPER && start->val != '\n') {
            start = start->prev;
            (*steps_it_took)--;
            col--;
        }
        if (col % width == 0)
            col++;
        col = ((col / width)) * width;
        while (col++) {
            start = start->next;
            (*steps_it_took)++;
        }
    }

    return start;
}
int list_offset_from_xy(short int x, short int y, unsigned short int width, node_t* cur)
{
    int res = 0;
    move_ptr_line(cur, true, &res, width);
    // move prt to cur of line count steps
    // move ptr y cords up or down:
    res = 0;
    for (int i = 0; i < abs(y); i++) {
        cur = move_ptr_line(cur, y < 0, &res, width);
    }
    // could refactor here to return int offset like originally planned
    //  move ptr to according position
    return res + x;
}
void list_mov_offset(node_t** start, int offset)
{
    if (offset < 0) {
        for (int i = 0; i < -offset; i++) {
            if ((*start)->prev)
                (*start) = (*start)->prev;
        }
    } else {
        for (int i = 0; i < offset; i++) {
            if ((*start)->next)
                (*start) = (*start)->next;
        }
    }
}
node_t* list_mov_xy(short int x, short int y, unsigned short int width, node_t* start)
{
    list_mov_offset(&start, list_offset_from_xy(x, y, width, start));
    return start;
    // just put in first as it is
    // go to corrosponding linebreak, count steps
}

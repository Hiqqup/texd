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
void list_delete(node_t* from, node_t* to)
{
    /*expecing the ptrs in right order*/
    node_t* to_free = from->next;
    to_free->prev = NULL;
    from->next = to;
    to->prev->next = NULL;
    to->prev = from;
    list_free(to_free);
}
void list_free(node_t* entry)
{
    while (entry->prev)
        entry = entry->prev;
    node_t* to_free = entry;
    while (entry->next) {
        free(to_free);
        to_free = entry;
        entry = entry->next;
    }
    free(entry);
}
node_t* list_move_ptr_line(node_t* start, bool up, int* steps_it_took, unsigned short int width)
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
        if (start->val != '\n' && start->next && start->next->val == '\n') {
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
int list_offset_from_y(short int y, unsigned short int width, node_t* cur)
{
    int res = 0;
    list_move_ptr_line(cur, true, &res, width);
    // move prt to cur of line count steps
    // move ptr y cords up or down:
    res = 0;
    for (int i = 0; i < abs(y); i++) {
        cur = list_move_ptr_line(cur, y < 0, &res, width);
    }
    // could refactor here to return int offset like originally planned
    //  move ptr to according position
    return res;
}
node_t* list_mov_offset(node_t* start, int offset)
{
    if (offset < 0) {
        for (int i = 0; i < -offset; i++) {
            if (start->prev)
                start = start->prev;
        }
    } else {
        for (int i = 0; i < offset; i++) {
            if (start->next)
                start = start->next;
        }
    }
    return start;
}
node_t* list_mov_y(short int y, unsigned short int width, node_t* start)
{
    return list_mov_offset(start, list_offset_from_y(y, width, start));
    // just put in first as it is
    // go to corrosponding linebreak, count steps
}
int list_ptr_distance(node_t* ptr1, node_t* ptr2)
{
    /*ripple from ptr2*/
    int left = 0;
    int right = 0;
    node_t* ptr3 = ptr2;
    while (ptr2 != ptr1 && ptr3 != ptr1) {
        if (ptr2->prev) {
            ptr2 = ptr2->prev;
            left++;
        }
        if (ptr3->next) {
            ptr3 = ptr3->prev;
            right++;
        }
    }
    return left > right ? -left : right;
}

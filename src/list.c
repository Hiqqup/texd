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
node_t* move_ptr_line(node_t* start, bool up, int* steps_it_took)
{
    // takes in a start pointer and goes to to the next linebreak
    // gotta add lines spanning multiple lines later
    //
    if (!up) {
        node_t* tmp = start;
        int counter = 1;
        while (tmp->val != LIST_STOPPER && tmp->val != '\n') {
            tmp = tmp->next;
            counter++;
        }
        if (tmp->val != LIST_STOPPER && tmp->next != NULL) {
            (*steps_it_took) += counter;
            start = tmp;
        }
    } else {
        (*steps_it_took)--;
        while (start->val != LIST_STOPPER && start->val != '\n') {
            start = start->prev;
            (*steps_it_took)--;
        }
    }

    return start;
}
node_t* list_mov_xy(short int x, short int y, unsigned short int width, node_t* start)
{
    // just put in first as it is
    // go to corrosponding linebreak, count steps
    node_t* cur = start;
    int res = 0;
    move_ptr_line(cur, true, &res);
    // move prt to cur of line count steps
    // move ptr y cords up or down:
    res = 0;
    if (y < 0) { // up
        for (int i = 0; i < -y && cur->prev != NULL; i++) {
            cur = move_ptr_line(cur->prev, true, &res);
        }
    } else { // down
        for (int i = 0; i < y && cur->next != NULL; i++) {
            cur = move_ptr_line(cur->next, false, &res);
        }
    }
    // could refactor here to return int offset like originally planned
    //  move ptr to according position
    res += x;
    if (res < 0) {
        for (int i = 0; i < -res; i++) {
            start = start->prev;
        }
    } else {
        for (int i = 0; i < res; i++) {
            start = start->next;
        }
    }
    return start;
}

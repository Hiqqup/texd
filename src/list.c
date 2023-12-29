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
void list_free(node_t* entry){
    node_t* right = entry->next;
    while(right->val != LIST_STOPPER){
        right = right->next;
        free(right->prev);
    }
    free(right);
    while(entry->val != LIST_STOPPER){
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
        while (start->val != LIST_STOPPER && start->val != '\n') {
            start = start->next;
            (*steps_it_took)++;
        }
    } else {
        while (start->val != LIST_STOPPER && start->val != '\n') {
            start = start->prev;
            (*steps_it_took)--;
        }
    }

    return start;
}
short int xy_to_list(short int x, short int y,unsigned short int width, node_t* start)
{
    // just put in first as it is
    // go to corrosponding linebreak, count steps
    int steps_to_linebegin = 0; // gonna add that later on
    while (start->val != LIST_STOPPER && start->val != '\n') {
        move_ptr_line(start, true, &steps_to_linebegin);
    } // move prt to start of line count steps
    // move ptr y cords up or down:
    int res = 0;
    if (y < 0) { // up
        for (int i = 0; i < -y; i++) {
            start = move_ptr_line(start->prev, true, &res);
        }
    } else { // down
        for (int i = 0; i < y; i++) {
            start = move_ptr_line(start->next, false, &res);
        }
    }
    return res+x;
}

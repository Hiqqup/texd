
#ifndef MAIN_H
#define MAIN_H
#include <errno.h>
#include <stdlib.h>

#define LIST_STOPPER '\0'
#define LIST_VAL_T char
typedef struct node {
    struct node* prev;
    struct node* next;
    LIST_VAL_T val;
} node_t;

enum Mode {
    MODE_NORMAL,
    MODE_INSERT,
    MODE_COMMAND,
};
struct Buffer {
    node_t* first; // first character on the screen;//to be exact the char before that
    node_t* current;
    node_t* current_linebreak;
    char* filename;
    unsigned short int term_cols;
    unsigned short int term_rows;
    unsigned short int wanabe_x; // where cursor wants to be
    unsigned short int term_x; // position of cursor
    unsigned short int term_y;
    unsigned short int before_command_y;
    unsigned short int before_command_x;
    unsigned short int editor_tabwidth;
    enum Mode mode;
    char* command;
};
void die(const char* s);
void exit_editor();
#endif // MAIN_H

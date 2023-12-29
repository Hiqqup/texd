
#ifndef MAIN_H
#define MAIN_H
#include<stdlib.h>
#include<errno.h>

#define LIST_STOPPER '\0'
#define LIST_VAL_T char
typedef struct node {
    struct node* prev;
    struct node* next;
    LIST_VAL_T val;
}node_t;

enum Mode{
    MODE_INSERT,
};
struct Buffer{
    node_t* first;//first character on the screen;//to be exact the char before that
    node_t* current;
    char* filename;
    unsigned short int term_cols;
    unsigned short int term_rows;
    unsigned short int term_x;// position of cursor
    unsigned short int term_y;
    enum Mode mode;
};
void die(const char* s);
#endif//MAIN_H

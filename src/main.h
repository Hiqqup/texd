
#ifndef MAIN_H
#define MAIN_H
#include<stdlib.h>
#include<errno.h>


#define LIST_STOPPER '\0'
typedef struct node {
    struct node* prev;
    struct node* next;
    char val;
}node_t;

struct Buffer{
    node_t* first;//first character on the screen;
    node_t* current;
    char* filename;
    unsigned short int term_cols;
    unsigned short int term_rows;
    unsigned short int term_x;// position of cursor
    unsigned short int term_y;
};
node_t* list_insert(node_t* node, char c);//return insertion //insert after
node_t* list_init();
void die(const char* s);
#endif//MAIN_H

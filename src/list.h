#ifndef LIST_H
#define LIST_H
#include "main.h"
#include <stdbool.h>

void list_free(node_t* entry);
node_t* list_insert(node_t* node, char c);//return insertion //insert after
node_t* list_init();
//node_t* move_ptr_line(node_t* start, bool up, int* steps_it_took); //may be only temporary
short int xy_to_list(short int x, short int y,unsigned short int width, node_t* start);
#endif//LIST_H

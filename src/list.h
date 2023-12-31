#ifndef LIST_H
#define LIST_H
#include "main.h"
#include <stdbool.h>

void list_free(node_t* entry);
node_t* list_insert(node_t* node, char c); // return insertion //insert after
node_t* list_init();
// node_t* move_ptr_line(node_t* start, bool up, int* steps_it_took); //may be only temporary
void list_delete(node_t* from, node_t* to);
node_t* list_mov_y( short int y, unsigned short int width, node_t* start);
int list_offset_from_y( short int y, unsigned short int width, node_t* cur);
node_t* list_mov_offset(node_t* start, int offset);
int list_ptr_distance(node_t* ptr1, node_t* ptr2);

#endif // LIST_H


#ifndef IO_H
#define IO_H
#include <stdio.h>
#include "main.h"
#include <string.h>
#include <unistd.h>
struct PrintBuffer{
    char* content;
    unsigned int top;
    unsigned int size;
};
void fileio_to_list(char* filename, node_t* node);
void output_print_buffer(struct Buffer* buf);
#endif//IO_H

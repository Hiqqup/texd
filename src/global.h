#ifndef GLOBAL_H
#define GLOBAL_H

#include <errno.h>
#include <stdlib.h>


void die(const char* s);

typedef struct charArr{
    char* c;
    size_t length;
}charArr;
struct buffer{
    charArr filename; // a string containing the filename
    charArr* lines;
    unsigned int line_count;
    unsigned short int term_rows;
    unsigned short int term_cols;
    unsigned int dx;// document x and y pos
    unsigned int dy;
    charArr render;
};
#define TABWIDTH 4
#endif // GLOBAL_H

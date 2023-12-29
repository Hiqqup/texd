#ifndef TERM_H
#define TERM_H

#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdbool.h>
#include <stdio.h>


void term_enable_raw_mode();
void term_exit_editor();
void term_clean_screen();
int term_get_input();
bool term_get_dimensions(unsigned short int* rows, unsigned short int* cols);
enum KEYS  {
    ESC_KEY = 27,
};

#define TERM_TICK 200
#define CTRL_KEY(k) ((k) & 0x1f)


#endif // TERM_H

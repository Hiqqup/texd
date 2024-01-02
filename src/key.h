
#ifndef KEY_H
#define KEY_H
#include "list.h"
#include "main.h"
#include "command.h"
#include <ctype.h>
#include <stdbool.h>
void key_process_input(int c, struct Buffer* buf);
enum Key {
    KEY_TAB = 9,
    KEY_ENTER = 13,
    KEY_ESC = 27,
    KEY_BACKSPACE = 127,
};
#endif // KEY_H

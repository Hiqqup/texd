
#include "fileio.h"
#include "global.h"
#include "term.h"
#include <stdbool.h> //tmp
#include <stdio.h> //tmp
#include <string.h>

void die(const char* s)
{
    perror(s);
    exit(1);
}

struct buffer main_buffer;
void init(int argc, char** argv)
{
    if (argc >= 2) {
        main_buffer.filename.c = argv[1];
        main_buffer.filename.length = strlen(argv[1]);
        fileio_read_file(&main_buffer);
    }

    // charArr* lines;
    main_buffer.dx = 0;
    main_buffer.dy = 0;
    if (!term_get_dimensions(&main_buffer.term_rows, &main_buffer.term_cols)) {
        die("get_term_size");
    }
    main_buffer.render.length = main_buffer.term_rows * main_buffer.term_cols;
}
int main(int argc, char** argv)
{
    term_enable_raw_mode();
    init(argc, argv);

    /*tmp loop to check if input works*/
    while (1) {
        char c = term_get_input();
        c++;//begone warninig;
    }
    term_exit_editor();
    return 0;
}

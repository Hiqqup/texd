
#include "main.h"
#include "io.h"
#include "key.h"
#include "term.h"
#include "list.h"

/** genral functions **/
void die(const char* s)
{
    perror(s);
    exit(1);
}

/** programm contorl flow **/
struct Buffer buf;
void init(int argc, char** argv)
{
    buf.first = list_init();
    if (argc >= 2) {
        buf.filename = argv[1];
        fileio_to_list(buf.filename, buf.first);
    }
    term_get_dimensions(&buf.term_rows, &buf.term_cols);
    buf.term_rows -= 1; // 3; // to have a little extra space for bars

    buf.term_y = 0;
    buf.term_x = 0;
    buf.mode = MODE_INSERT;
}

int main(int argc, char** argv)
{
    term_clean_screen();
    term_enable_raw_mode();
    init(argc, argv);

    // printf("term dimesions: %i x %i \n",buf.term_cols, buf.term_rows);
    /*tmp loop to check if input works*/
    // LIST_VAL_T c = 0;
    output_print_buffer(&buf);
    while (1) {
        key_process_input(term_get_input(), &buf);
        output_print_buffer(&buf);
        // printf("first val: %c \n",buf.first->val);
        // printf("first val: %i ,linbrak val: %i \n",buf.first->val, '\n');
    }
    list_free(buf.first);
    term_exit_editor();
    return 0;
}

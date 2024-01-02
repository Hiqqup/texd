
#include "main.h"
#include "io.h"
#include "key.h"
#include "list.h"
#include "term.h"

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
    buf.current_linebreak = buf.first;
    buf.current = buf.first;
    if (argc >= 2) {
        buf.filename = argv[1];
        fileio_to_list(buf.filename, buf.first);
    } else {
        buf.filename = "[No Name]";
    }
    term_get_dimensions(&buf.term_rows, &buf.term_cols);
    buf.term_rows -= 2; // 3; // to have a little extra space for bars

    buf.term_y = 0;
    buf.term_x = 0;
    buf.wanabe_x = 0;
    buf.before_command_y = 0;
    buf.mode = MODE_NORMAL;
    buf.editor_tabwidth = 4;

    buf.command = malloc(sizeof(char) * buf.term_cols);
    buf.command[0] = '\0';
}
int main(int argc, char** argv)
{
    term_clean_screen();
    term_enable_raw_mode();
    init(argc, argv);

    output_print_buffer(&buf);
    while (1) {
        key_process_input(term_get_input(), &buf);
        output_print_buffer(&buf);
    }
    exit_editor(&buf);
    return 0;
}
void exit_editor(struct Buffer* bufr)
{
    free(bufr->command);
    list_free(bufr->first);
    term_exit_editor();
    exit(0);
}

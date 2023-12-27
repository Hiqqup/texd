
#include "main.h"
#include "io.h"
#include "term.h"

void die(const char* s)
{
    perror(s);
    exit(1);
}
node_t* list_init()
{
    node_t* first = malloc(sizeof(node_t));
    node_t* last = malloc(sizeof(node_t));
    if (first == NULL || last == NULL)
        die("malloc - list init");
    first->val = LIST_STOPPER;
    last->val = LIST_STOPPER;
    first->next = last;
    last->prev = first;
    return first;
}
node_t* list_insert(node_t* node, char c)
{
    node_t* ins = malloc(sizeof(node_t));
    if (ins == NULL)
        die("malloc - list insert");
    ins->val = c;
    node->next->prev = ins;
    ins->next = node->next;
    ins->prev = node;
    node->next = ins;
    return ins;
}

struct Buffer buf;
void init(int argc, char** argv)
{
    buf.current = list_init();
    buf.first = buf.current;
    if (argc >= 2) {
        buf.filename = argv[1];
        fileio_to_list(buf.filename, buf.current);
    }
    term_get_dimensions(&buf.term_rows, &buf.term_cols);

    buf.term_y = 10;
        buf.term_x = 0;
}

int main(int argc, char** argv)
{
    term_enable_raw_mode();
    init(argc, argv);

    //printf("term dimesions: %i x %i \n",buf.term_cols, buf.term_rows);
    output_print_buffer(&buf);
    /*tmp loop to check if input works*/
    while (1) {
        char c = term_get_input();
        c++; // begone warninig;
    }
    term_exit_editor();
    return 0;
}

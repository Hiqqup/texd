
#include "io.h"
#include "main.h"
void fileio_to_list(char* filename, node_t* node)
{
    FILE* fp = fopen(filename, "r");
    if (fp == NULL)
        die("fopen");
    char c;
    do {
        c = fgetc(fp);
        node = list_insert(node, c);
    } while (c != EOF);
    fclose(fp);
}

void print_buffer_append(struct PrintBuffer* print_buf, const char* string, unsigned short int length)
{
    if (length + print_buf->top >= print_buf->size)
        die("print_buffer_append");
    memcpy(print_buf->content + print_buf->top, string, length);
    print_buf->top += length;
}
void print_buffer_from_contents(struct PrintBuffer* print_buf, struct Buffer* buf)
{
    int row = 0;
    int col = 0;
    node_t* cur = buf->first->next;
    while (cur->val != LIST_STOPPER && row < buf->term_rows) {
        print_buffer_append(print_buf, &cur->val, 1);
        if (cur->val == '\n') {
            print_buffer_append(print_buf, "\x1b[K", 3);
            row++;
            col = 0;
        }
        if (cur->val != '\n' /*and other escape sequences that dont advance the cursor*/) {
            col++;
        }
        if (col > buf->term_cols) {
            print_buffer_append(print_buf, "\x1b[K", 3);
            row++;
            col = 0;
        }// gotta figure out how to correctly render multilines
        cur = cur->next;
    }
    col = 0;
    while (cur->val != LIST_STOPPER && cur->val != '\n' && col++ < buf->term_cols) {
        print_buffer_append(print_buf, &cur->val, 1);
        cur = cur->next;
    }
}

void output_print_buffer(struct Buffer* buf)
{
    // check if screen is full or if were at the end
    unsigned int size = buf->term_cols * buf->term_rows * 2;
    struct PrintBuffer print_buffer = {
        .content = malloc(size * sizeof(char)),
        .top = 0,
        .size = size,
    };

    print_buffer_append(&print_buffer, "\x1b[?25l", 6); // hide cursor
    print_buffer_append(&print_buffer, "\x1b[H", 3); // move to the top
    print_buffer_append(&print_buffer, "\x1b[K", 3);

    print_buffer_from_contents(&print_buffer, buf);

    print_buffer_append(&print_buffer, "\x1b[?25h", 6); // show cursor

    char move_buffer[32];
    snprintf(move_buffer, sizeof(move_buffer), "\x1b[%d;%dH", buf->term_y + 1, buf->term_x + 1);
    print_buffer_append(&print_buffer, move_buffer, strlen(move_buffer)); // show cursor

    write(STDOUT_FILENO, print_buffer.content, print_buffer.top);
    free(print_buffer.content);
}

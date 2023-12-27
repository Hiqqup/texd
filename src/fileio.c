
#include "fileio.h"
void fileio_read_file(struct buffer* buffer)
{
    buffer->line_count = 1;
    FILE* fp = fopen(buffer->filename.c, "r");
    char c;
    do {
        c = getc(fp);
        if (c == '\n')
            buffer->line_count++;
    } while (c != EOF);
    rewind(fp);
    buffer->lines = malloc(sizeof(charArr) * buffer->line_count);
    int row = 0;
    do {
        c = getc(fp);
        buffer->lines[row].length++;
        if (c == '\t')
            buffer->lines[row].length += TABWIDTH - 1;
        if (c == '\n'){
            row++;
            buffer->lines[row].length++;
        }
    } while (c != EOF);
    rewind(fp);
    row = 0;
    int col = 0;
    buffer->lines[row].c = malloc(sizeof(char) * buffer->lines[row].length);
    do {
        c = getc(fp);
        if (c == '\t') {
            for (int i = 0; i < TABWIDTH; i++)
                buffer->lines[row].c[col++] = c;
        } else
            buffer->lines[row].c[col++] = c;
        if (c == '\n') {
            buffer->lines[row].c[col++] = '\r';
            col = 0;
            row++;
            buffer->lines[row].c = malloc(sizeof(char) * buffer->lines[row].length);
        }
    } while (c != EOF);
    fclose(fp);
}

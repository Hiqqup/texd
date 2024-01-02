
#include "command.h"

void command_execute(struct Buffer* buf)
{
    if (strcmp(buf->command, ":w") == 0) {
        fileio_save(buf);
    };
    if (strcmp(buf->command, ":q") == 0) {
        exit_editor(buf);
    };
    if (strcmp(buf->command, ":wq") == 0) {
        fileio_save(buf);
        exit_editor(buf);
    };
}

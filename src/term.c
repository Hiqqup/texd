
#include "term.h"
#include "global.h"

struct termios orig_termios;

bool get_cursor_position(unsigned short int* rows, unsigned short int* cols)
{
    char buf[32];
    unsigned int i = 0;
    if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4)
        return -1;
    while (i < sizeof(buf) - 1) {
        if (read(STDIN_FILENO, &buf[i], 1) != 1)
            break;
        if (buf[i] == 'R')
            break;
        i++;
    }
    buf[i] = '\0';
    if (buf[0] != '\x1b' || buf[1] != '[')
        return false;
    if (sscanf(&buf[2], "%hu;%hu", rows, cols) != 2)
        return false;
    return true;
}
bool term_get_dimensions(unsigned short int* rows, unsigned short int* cols)
{
    struct winsize ws;

    if (  ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12)
            return false;
        return get_cursor_position(rows, cols);
    } else {
        *cols = ws.ws_col;
        *rows = ws.ws_row;
        return true;
    }
}

void term_clean_screen()
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
}

void term_exit_editor()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
    // i could add that it clears the screen but i like it not doing it for now
}
int term_get_input()
{
    int c = '\0';
    if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
        die("read - input");
    return c;
    // i wont bother with escape sequences yet
}
void term_enable_raw_mode()
{
    struct termios raw;
    if (tcgetattr(STDIN_FILENO, &raw) == -1)
        die("tcgetattr");
    orig_termios = raw;
    raw.c_iflag &= ~(
        BRKINT | // idk
        INPCK | // idk
        ISTRIP | // idk
        ICRNL | // fix ctrl m
        IXON); // disable ctrl s crl q
    raw.c_oflag &= ~(
        OPOST); // basically turns \r\n into just \n
    raw.c_cflag |= CS8; // idk
    raw.c_lflag &= ~(
        ECHO | // as the name suggests
        ICANON | // byte by byte instead of line by line
        // ISIG| // disable ctrl c and ctrl z // ill disable it for development
        IEXTEN); // disable ctrl v
    raw.c_cc[VMIN] = 0; // min amount of bytes before read can return
    raw.c_cc[VTIME] = TERM_TICK; // max time before read returns
    // guss were doing everything with read
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

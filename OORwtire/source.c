#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CTRL(x) ((x) & 0x1F)

typedef struct {
    char *data;
    size_t size;
    size_t cursor;
} Buffer;

Buffer load_file(const char *path) {
    FILE *f = fopen(path, "rb");
    Buffer b = {NULL, 0, 0};

    if (!f) return b;

    fseek(f, 0, SEEK_END);
    b.size = ftell(f);
    rewind(f);

    b.data = malloc(b.size + 1);
    fread(b.data, 1, b.size, f);
    fclose(f);
    return b;
}

void save_file(const char *path, Buffer *b) {
    FILE *f = fopen(path, "wb");
    fwrite(b.data, 1, b.size, f);
    fclose(f);
}

int main(int argc, char **argv) {
    if (argc != 2) return 1;

    Buffer buf = load_file(argv[1]);
    if (!buf.data) buf.data = calloc(1, 1);

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    while (1) {
        erase();
        mvprintw(0, 0, "--- OORwrite [%s] ---", argv[1]);
        for (size_t i = 0; i < buf.size; i++)
            mvaddch(2 + i, 0, buf.data[i] ? buf.data[i] : '~');

        mvprintw(buf.cursor + 2, 0, "_");

        int ch = getch();

        if (ch == CTRL('q')) break;
        else if (ch == CTRL('s')) save_file(argv[1], &buf);
        else if (ch == KEY_RIGHT) buf.cursor++;
        else if (ch == KEY_LEFT && buf.cursor > 0) buf.cursor--;
        else {
            if (buf.cursor >= buf.size) {
                buf.data = realloc(buf.data, buf.cursor + 1);
                buf.size = buf.cursor + 1;
            }
            buf.data[buf.cursor++] = ch;
        }
    }

    endwin();
    free(buf.data);
    return 0;
}

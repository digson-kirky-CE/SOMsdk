#include <ncurses.h>
#include <stdio.h>

void start_tui(const char *filename) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    FILE *f = fopen(filename, "r");
    if (!f) {
        printw("Cannot open %s\n", filename);
    } else {
        char line[256];
        int y = 0;
        while (fgets(line, sizeof(line), f)) {
            mvprintw(y++, 0, "%s", line);
        }
        fclose(f);
    }

    printw("\nPress any key to exit...");
    refresh();
    getch();
    endwin();
}

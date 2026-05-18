#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEFAULT_FILE "data.txt"
#define WORKDIR "./workdir"

void start_tui(const char *filename);

int main(int argc, char *argv[]) {
    int do_copy = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0 ||
            strcmp(argv[i], "-do") == 0) {
            do_copy = 1;
        }
    }

    if (do_copy) {
        system("mkdir -p workdir");
        char cmd[512];
        snprintf(cmd, sizeof(cmd),
                 "cp %s %s/", DEFAULT_FILE, WORKDIR);
        system(cmd);
        printf("Copied to workdir\n");
    }

    // 启动 TUI
    start_tui(DEFAULT_FILE);
    return 0;
}

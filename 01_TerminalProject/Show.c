#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>

#include <ncurses.h>

#define DX 5
#define DY 7

#define ESC 27

int validate_filename(const char *filename) {
    return filename && strlen(filename);
}

int file_exists(const char *filename) {
    return access(filename, F_OK) == 0;
}

void display_file(const char *filename, WINDOW *win) {
    FILE *file = fopen(filename, "r");
    if (file) {
        char line[256];
        int line_num = 0;
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = '\0';
            mvwaddnstr(win, line_num++, 0, line, getmaxx(win) - 1);
        }
        fclose(file);
    } else {
        wprintw(win, "Could not open file: %s", filename);
    }
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    if (argc != 2) {
        printf("Provide a filename!\n");
        return 1;
    }

    const char *filename = argv[1];

    if (!validate_filename(filename)) {
        fprintf(stderr, "Invalid filename %s\n", filename);
        return 1;
    }

    if (!file_exists(filename)) {
        fprintf(stderr, "File %s does not exist!\n", filename);
        return 1;
    }

    // ***
    // conf
    initscr(); 
    noecho();
    cbreak(); // break every symbol
    keypad(stdscr, TRUE); // enable special keys

    // frame
    WINDOW *frame = newwin(LINES-2*DX, COLS-2*DX, DX, DX);
    box(frame, 0, 0);
    mvwaddstr(frame, 0, 4, filename);
    wrefresh(frame);

    // win
    WINDOW *win = newwin(LINES-2*DY, COLS-2*DY, DY, DY);
    scrollok(win, TRUE);
    keypad(win, TRUE);

    display_file(filename, win);
    wrefresh(win);

    int c;
    /* int scroll_pos = 0; */
    /* int max_lines = getmaxy(win); */
    while ((c = wgetch(win)) != ESC) {
        switch(c) {
            case KEY_UP:
                wscrl(win, -1);
                break;
            case KEY_DOWN:
                wscrl(win, 1);
                break;
            default:
                // do nothing for other keys
                break;
        }
        wrefresh(win);
    }

    delwin(win);
    delwin(frame);
    endwin();

    return 0;
}

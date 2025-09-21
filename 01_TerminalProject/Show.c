#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <ncurses.h>

#define DX 3
#define DY 6
#define ESC 27

// store file lines in memory
static char **lines = NULL;
static size_t line_count = 0;

int validate_filename(const char *filename) {
    return filename && strlen(filename);
}

int file_exists(const char *filename) {
    return access(filename, F_OK) == 0;
}

void load_file(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return;

    int max_lines = 100;
    lines = malloc(max_lines * sizeof(char *));
    line_count = 0; // global line_count

    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), f)) {
        size_t len = strlen(buffer);
        if (buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }

        // check if we need more space
        if ((int)line_count >= max_lines) {
            max_lines *= 2;
            lines = realloc(lines, max_lines * sizeof(char *));
        }
        
        lines[line_count] = malloc(strlen(buffer) + 1);
        strcpy(lines[line_count], buffer);
        line_count++;
    }

    fclose(f);
}

void draw_lines(WINDOW *win, int start) {
    werase(win);
    int maxy = getmaxy(win);
    int maxx = getmaxx(win) - 1;
    for (int i = 0; i < maxy && (size_t)(start + i) < line_count; i++) {
        mvwaddnstr(win, i, 0, lines[start + i], maxx);
    }
    wrefresh(win);
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];

    if (!validate_filename(filename)) {
        fprintf(stderr, "Invalid filename\n");
        return 1;
    }

    if (!file_exists(filename)) {
        fprintf(stderr, "File does not exist: %s\n", filename);
        return 1;
    }

    load_file(filename);
    if (line_count == 0) {
        fprintf(stderr, "Could not read file: %s\n", filename);
        return 1;
    }

    // conf
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    //

    // frame
    WINDOW *frame = newwin(LINES-2*DX, COLS-2*DX, DX, DX);
    box(frame, 0, 0);
    mvwaddstr(frame, 0, 4, filename);
    wrefresh(frame);

    // win
    WINDOW *win = newwin(LINES-2*DY, COLS-2*DY, DY, DY);
    scrollok(win, TRUE);
    keypad(win, TRUE);

    int scroll_pos = 0;
    draw_lines(win, scroll_pos);

    int c;
    while ((c = wgetch(win)) != ESC) {
        int maxy = getmaxy(win);
        switch (c) {
            case KEY_UP:
                if (scroll_pos > 0) 
                    scroll_pos--;
                break;
            case KEY_DOWN:
                if ((size_t)(scroll_pos + maxy) < line_count) 
                    scroll_pos++;
                break;
            case KEY_NPAGE:
                scroll_pos += maxy;
                if ((size_t)scroll_pos >= line_count) {
                    scroll_pos = line_count - maxy;
                    if (scroll_pos < 0) 
                        scroll_pos = 0;
                }
                break;
            case KEY_PPAGE:
                scroll_pos -= maxy;
                if (scroll_pos < 0) 
                    scroll_pos = 0;
                break;
        }
        draw_lines(win, scroll_pos);
    }

    delwin(win);
    delwin(frame);
    endwin();

    for (size_t i = 0; i < line_count; i++) free(lines[i]);
    free(lines);
    return 0;
}

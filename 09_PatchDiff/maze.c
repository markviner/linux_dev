#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 6

typedef struct {
    int visited;
    int walls[4];
} Cell;

Cell maze[SIZE][SIZE];

void init_maze() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            maze[i][j].visited = 0;
            for (int k = 0; k < 4; k++) {
                maze[i][j].walls[k] = 1;
            }
        }
    }
}

void generate_maze(int x, int y) {
    maze[x][y].visited = 1;
    
    int dirs[4][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}};
    int order[4] = {0, 1, 2, 3};
    
    for (int i = 0; i < 4; i++) {
        int j = rand() % 4;
        int tmp = order[i];
        order[i] = order[j];
        order[j] = tmp;
    }
    
    for (int i = 0; i < 4; i++) {
        int dir = order[i];
        int nx = x + dirs[dir][0];
        int ny = y + dirs[dir][1];
        
        if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && !maze[nx][ny].visited) {
            maze[x][y].walls[dir] = 0;
            maze[nx][ny].walls[(dir + 2) % 4] = 0;
            generate_maze(nx, ny);
        }
    }
}

void print_maze() {
    int height = SIZE * 2 + 1;
    int width = SIZE * 2 + 1;
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i % 2 == 0) {
                if (j % 2 == 0) {
                    printf("#");
                } else {
                    int cell_y = j / 2;
                    int cell_x = i / 2;
                    if (i == 0 || i == height - 1) {
                        printf("#");
                    } else {
                        if (maze[cell_x - 1][cell_y].walls[2]) {
                            printf("#");
                        } else {
                            printf(".");
                        }
                    }
                }
            } else {
                if (j % 2 == 0) {
                    int cell_x = i / 2;
                    int cell_y = j / 2;
                    if (j == 0 || j == width - 1) {
                        printf("#");
                    } else {
                        if (maze[cell_x][cell_y - 1].walls[1]) {
                            printf("#");
                        } else {
                            printf(".");
                        }
                    }
                } else {
                    printf(".");
                }
            }
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));
    
    init_maze();
    generate_maze(0, 0);
    print_maze();
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define SIZE 2048

typedef struct fold {
    char axis;
    int value;
} Fold;

int main()
{
    FILE* f = fopen("../input.txt", "rb");
    char line[32];
    char (* grid)[SIZE] = malloc(sizeof(*grid) * SIZE);
    Fold folds[16];
    int foldCount = 0;
    memset(grid, '.', SIZE * SIZE);

    // read points
    while (readStrFromLine(line, sizeof(line), f) && *line) {
        int x;
        int y;
        sscanf(line, "%d,%d", &x, &y);
        grid[y][x] = '#';
    }

    // read folds
    while (readStrFromLine(line, sizeof(line), f)) {
        sscanf(line, "%*s %*s %c=%d", &folds[foldCount].axis, &folds[foldCount].value);
        foldCount++;
    }

    // execute folds
    // always checks the whole array, so not very efficient
    for (int i = 0; i < foldCount; ++i) {
        if (folds[i].axis == 'x') {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = folds[i].value + 1; k < SIZE; ++k) {
                    if (grid[j][k] == '#') {
                        grid[j][k] = '.';
                        grid[j][k - 2 * (k - folds[i].value)] = '#';
                    }
                }
            }
        } else {
            for (int j = folds[i].value + 1; j < SIZE; ++j) {
                for (int k = 0; k < SIZE; ++k) {
                    if (grid[j][k] == '#') {
                        grid[j][k] = '.';
                        grid[j - 2 * (j - folds[i].value)][k] = '#';
                    }
                }
            }
        }
        if (i == 0) {
            // count #s
            int hashCount = 0;
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < SIZE; ++k) {
                    if (grid[j][k] == '#') {
                        hashCount++;
                    }
                }
            }

            printf("Part 1: %d\n", hashCount);
        }
    }

    printf("Part 2:\n");
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 50; ++j) {
            if (grid[i][j] == '#') {
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    free(grid);
    fclose(f);
    return 0;
}

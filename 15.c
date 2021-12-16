// not really proud of this one
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define SIZE 100

bool minDistance(int (* riskMatrix)[5 * SIZE], int (* distancesMatrix)[5 * SIZE], int i, int j, bool part2)
{
    int len = part2 ? 5 * SIZE : SIZE;
    bool result = false;
    if (distancesMatrix[i][j] != -1) {
        if (i - 1 >= 0) {
            int newValue = distancesMatrix[i][j] + riskMatrix[i - 1][j];
            if (newValue < distancesMatrix[i - 1][j] || distancesMatrix[i - 1][j] == -1) {
                distancesMatrix[i - 1][j] = newValue;
                result = true;
            }
        }
        if (i + 1 < len) {
            int newValue = distancesMatrix[i][j] + riskMatrix[i + 1][j];
            if (newValue < distancesMatrix[i + 1][j] || distancesMatrix[i + 1][j] == -1) {
                distancesMatrix[i + 1][j] = newValue;
                result = true;
            }
        }
        if (j - 1 >= 0) {
            int newValue = distancesMatrix[i][j] + riskMatrix[i][j - 1];
            if (newValue < distancesMatrix[i][j - 1] || distancesMatrix[i][j - 1] == -1) {
                distancesMatrix[i][j - 1] = newValue;
                result = true;
            }
        }
        if (j + 1 < len) {
            int newValue = distancesMatrix[i][j] + riskMatrix[i][j + 1];
            if (newValue < distancesMatrix[i][j + 1] || distancesMatrix[i][j + 1] == -1) {
                distancesMatrix[i][j + 1] = newValue;
                result = true;
            }
        }
    }

    return result;
}

int generateDistMatrix(int (* riskMatrix)[5 * SIZE], int (* distancesMatrix)[5 * SIZE], bool part2)
{
    memset(distancesMatrix, -1, sizeof(int[5 * SIZE][5 * SIZE]));
    distancesMatrix[0][0] = riskMatrix[0][0];

    bool stop = false;
    int len = part2 ? 5 * SIZE : SIZE;
    while (!stop) {
        stop = true;
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < len; ++j) {
                if (minDistance(riskMatrix, distancesMatrix, i, j, part2)) {
                    stop = false;
                }
            }
        }
    }

    return distancesMatrix[len - 1][len - 1] - distancesMatrix[0][0];
}

int main()
{
    FILE* f = fopen("../input.txt", "rb");
    int (* riskMatrix)[5 * SIZE] = malloc(sizeof(int[5 * SIZE][5 * SIZE]));

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int c = fgetc(f);
            riskMatrix[i][j] = c - '0';
        }
        // get new line
        fgetc(f);
    }

    int (* distancesMatrix)[5 * SIZE] = malloc(sizeof(int[5 * SIZE][5 * SIZE]));

    printf("Part 1: %d\n", generateDistMatrix(riskMatrix, distancesMatrix, false));

    // populate 5x5
    int j = 0;
    for (int i = 0; i < 5; ++i) {
        if (i != 0) {
            for (int k = 0; k < SIZE; ++k) {
                memcpy(&riskMatrix[SIZE * i + k][0], &riskMatrix[SIZE * (i - 1) + k][SIZE],
                       SIZE * 4 * sizeof(int));
            }
            j = 3;
        }
        for (; j < 4; ++j) {
            for (int k = 0; k < SIZE; ++k) {
                for (int l = 0; l < SIZE; ++l) {
                    int value = riskMatrix[SIZE * i + k][SIZE * j + l];
                    if (value + 1 > 9) {
                        riskMatrix[SIZE * i + k][SIZE * j + l + SIZE] = 1;
                    } else {
                        riskMatrix[SIZE * i + k][SIZE * j + l + SIZE] = value + 1;
                    }
                }
            }
        }
    }

    printf("Part 2: %d\n", generateDistMatrix(riskMatrix, distancesMatrix, true));

    free(riskMatrix);
    free(distancesMatrix);
    fclose(f);
    return 0;
}

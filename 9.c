#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define SIZE 128

bool isLowPoint(char heightMap[SIZE][SIZE], int i, int j, int hmX, int hmY)
{
    return !((i - 1 >= 0 && heightMap[i - 1][j] <= heightMap[i][j]) ||
             (i + 1 < hmY && heightMap[i + 1][j] <= heightMap[i][j]) ||
             (j - 1 >= 0 && heightMap[i][j - 1] <= heightMap[i][j]) ||
             (j + 1 < hmX && heightMap[i][j + 1] <= heightMap[i][j]));
}

int findBasin(char heightMap[SIZE][SIZE], bool basinMap[SIZE][SIZE], int i, int j, int hmX, int hmY, char ref)
{
    if (i < 0 || i >= hmY || j < 0 || j >= hmX || heightMap[i][j] == '9' || basinMap[i][j] == true) {
        return 0;
    } else if (heightMap[i][j] > ref) {
        basinMap[i][j] = true;
        return 1 + findBasin(heightMap, basinMap, i - 1, j, hmX, hmY, heightMap[i][j]) +
               findBasin(heightMap, basinMap, i + 1, j, hmX, hmY, heightMap[i][j]) +
               findBasin(heightMap, basinMap, i, j - 1, hmX, hmY, heightMap[i][j]) +
               findBasin(heightMap, basinMap, i, j + 1, hmX, hmY, heightMap[i][j]);
    }

    return 0;
}

int main()
{
    FILE* f = fopen("../input.txt", "rb");
    char heightMap[SIZE][SIZE];
    bool basinMap[SIZE][SIZE];
    memset(basinMap, 0, sizeof(basinMap));
    int hmX = 0;
    int hmY = 0;

    char line[128];
    while (readStrFromLine(line, sizeof(line), f)) {
        char* start = line;
        hmX = 0;
        do {
            sscanf(start, "%c", &heightMap[hmY][hmX++]);
            start += 1;
        } while (*start);
        hmY++;
    }

    int sumRiskLevel = 0;
    int basins[3] = {INT_MIN, INT_MIN, INT_MIN};
    for (int i = 0; i < hmY; ++i) {
        for (int j = 0; j < hmX; ++j) {
            if (isLowPoint(heightMap, i, j, hmX, hmY)) {
                sumRiskLevel += heightMap[i][j] - '0' + 1;
                int basin = findBasin(heightMap, basinMap, i, j, hmX, hmY, -1);
                for (int k = 0; k < 3; ++k) {
                    if (basin > basins[k]) {
                        memmove(&basins[k + 1], &basins[k], (3 - k - 1) * sizeof(*basins));
                        basins[k] = basin;
                        break;
                    }
                }
            }
        }
    }

    printf("Part 1: %d\n", sumRiskLevel);
    printf("Part 2: %d\n", basins[0] * basins[1] * basins[2]);

    fclose(f);
    return 0;
}

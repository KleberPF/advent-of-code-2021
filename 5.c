#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void fillPoints(int (* points)[1000], FILE* f, bool part2)
{
    char line[32];
    while (fgets(line, sizeof(line), f)) {
        int x1, y1, x2, y2;
        sscanf(line, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);
        if (x1 == x2) {
            int step = y1 > y2 ? -1 : 1;
            int count = abs(y1 - y2);
            for (int i = 0; i <= count; i++) {
                points[y1][x1]++;
                y1 += step;
            }
        } else if (y1 == y2) {
            int step = x1 > x2 ? -1 : 1;
            int count = abs(x1 - x2);
            for (int i = 0; i <= count; i++) {
                points[y1][x1]++;
                x1 += step;
            }
        } else if (part2 && abs(x2 - x1) == abs(y2 - y1)) {
            // count diagonals
            int stepX = x1 > x2 ? -1 : 1;
            int stepY = y1 > y2 ? -1 : 1;
            int count = abs(y1 - y2);
            for (int i = 0; i <= count; i++) {
                points[y1][x1]++;
                x1 += stepX;
                y1 += stepY;
            }
        }
    }
}

int countIntersections(int (* points)[1000])
{
    int count = 0;
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            if (points[i][j] > 1) {
                count++;
            }
        }
    }

    return count;
}

int main()
{
    FILE* f = fopen("../input.txt", "rb");

    int (* points)[1000] = calloc(1000, sizeof(*points));
    fillPoints(points, f, false);
    printf("Part1: %d\n", countIntersections(points));
    memset(points, 0, sizeof(*points) * 1000);
    fseek(f, 0, SEEK_SET);
    fillPoints(points, f, true);
    printf("Part2: %d\n", countIntersections(points));
    fclose(f);
    free(points);
    return 0;
}

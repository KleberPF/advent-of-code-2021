#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int main()
{
    FILE* f = fopen("../input.txt", "rb");
    char lines[128][128];
    int lineCount = 0;
    for (; readStrFromLine(lines[lineCount], sizeof(lines[0]), f); lineCount++);

    const char* symbols = "([{<)]}>";
    int points[] = {3, 57, 1197, 25137};
    int corruptedPoints = 0;
    unsigned long long incompletePoints[128];
    int incPointsCount = 0;
    for (int i = 0; i < lineCount; ++i) {
        char stack[128];
        int stackSize = 0;
        int len = strlen(lines[i]);
        bool isCorrupted = false;
        for (int j = 0; j < len; ++j) {
            // if opening character
            char* c = memchr(symbols, lines[i][j], strlen(symbols));
            if (c - symbols < 4) {
                stack[stackSize++] = lines[i][j];
            } else {
                // closing character
                // consume character in stack
                stackSize--;
                if (stack[stackSize] != c[-4]) {
                    int index = c - symbols - 4;
                    corruptedPoints += points[index];
                    isCorrupted = true;
                    break;
                }
            }
        }

        if (!isCorrupted) {
            unsigned long long currentPoints = 0;
            // pop the stack and count the points
            while (stackSize > 0) {
                currentPoints *= 5;
                char tmp[2] = {stack[--stackSize], '\0'};
                int pt = strcspn(symbols, tmp) + 1;
                currentPoints += pt;
            }
            incompletePoints[incPointsCount++] = currentPoints;
        }
    }

    qsort(incompletePoints, incPointsCount, sizeof(*incompletePoints), compareUul);
    printf("Part 1: %d\n", corruptedPoints);
    printf("Part 2: %llu\n", incompletePoints[incPointsCount / 2]);

    fclose(f);
    return 0;
}

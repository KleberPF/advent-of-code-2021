#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

long part1(char* fileContent)
{
    int offset = 0;
    char direction[16];
    int value = 0;
    long horizontalPos = 0;
    long depth = 0;
    while (sscanf(fileContent, "%s %d%n", direction, &value, &offset) == 2) {
        if (strcmp(direction, "forward") == 0) {
            horizontalPos += value;
        } else if (strcmp(direction, "down") == 0) {
            depth += value;
        } else if (strcmp(direction, "up") == 0) {
            depth -= value;
        }

        fileContent += offset;
    }

    return horizontalPos * depth;
}

long part2(char* fileContent)
{
    int offset = 0;
    char direction[16];
    int value = 0;
    long aim = 0;
    long horizontalPos = 0;
    long depth = 0;
    while (sscanf(fileContent, "%s %d%n", direction, &value, &offset) == 2) {
        if (strcmp(direction, "forward") == 0) {
            horizontalPos += value;
            depth += aim * value;
        } else if (strcmp(direction, "down") == 0) {
            aim += value;
        } else if (strcmp(direction, "up") == 0) {
            aim -= value;
        }

        fileContent += offset;
    }

    return horizontalPos * depth;
}

int main()
{
    FILE* f = fopen("../input.txt", "rb");

    // read file into buffer
    int fileLength = getFileLength(f);
    char* fileContent = malloc(fileLength + 1);
    readFileToBuffer(fileContent, fileLength, f);

    long resultPart1 = part1(fileContent);
    long resultPart2 = part2(fileContent);

    // show results
    printf("Part 1: %ld\nPart 2: %ld\n", resultPart1, resultPart2);

    // close file and free array
    fclose(f);
    free(fileContent);
}

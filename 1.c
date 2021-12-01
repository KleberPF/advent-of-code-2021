#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#define MEASURE_SIZE 3

int part1(int *values, int lineCount)
{
    int numIncreases = 0;
    int previousValue = 0;

    for (int i = 0; i < lineCount; i++) {
        if (i != 0 && values[i] > previousValue) {
            numIncreases++;
        }
        previousValue = values[i];
    }

    return numIncreases;
}

int part2(int *values, int lineCount)
{
    int numIncreases = 0;
    int previousSum = 0;

    for (int i = 0; i < lineCount - MEASURE_SIZE + 1; i++) {
        int sum = 0;
        for (int j = 0; j < MEASURE_SIZE; j++) {
            sum += values[i + j];
        }
        if (i != 0 && sum > previousSum) {
            numIncreases++;
        }

        previousSum = sum;
    }

    return numIncreases;
}

int main()
{
    FILE *f = fopen("../input.txt", "r");
    if (f) {
        int *values = malloc(sizeof(*values) * 2048);

        // read ints from file
        int lineCount = 0;
        char line[16];
        for (; readIntFromLine(line, sizeof(line), f, &values[lineCount++]););

        // run part1 and part2
        int numIncreases = part1(values, lineCount);
        int numIncreasesPt2 = part2(values, lineCount);

        // show results
        printf("Part 1: %d\nPart 2: %d\n", numIncreases, numIncreasesPt2);
        
        // close file and free array
        fclose(f);
        free(values);
    }
}

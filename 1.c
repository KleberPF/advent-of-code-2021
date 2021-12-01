#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#define MEASURE_SIZE 3

int valuesSum(const int *values, int start, int count)
{
    int sum = 0;
    for (int j = 0; j < count; j++) {
        sum += values[start + j];
    }

    return sum;
}

int part1(const int *values, int lineCount)
{
    int numIncreases = 0;
    int previousValue = values[0];

    for (int i = 1; i < lineCount; i++) {
        if (values[i] > previousValue) {
            numIncreases++;
        }
        previousValue = values[i];
    }

    return numIncreases;
}

int part2(const int *values, int lineCount)
{
    int numIncreases = 0;
    int previousSum = valuesSum(values, 0, MEASURE_SIZE);

    for (int i = 1; i < lineCount - MEASURE_SIZE + 1; i++) {
        int sum = valuesSum(values, i, MEASURE_SIZE);
        if (sum > previousSum) {
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

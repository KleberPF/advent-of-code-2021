#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define POS_COUNT 2000

int calculateFuelUsage(int* crabs, int crabCount, bool part1)
{
    int smallestFuelUsage = INT_MAX;
    for (int i = 0; i < POS_COUNT; i++) {
        // calculate fuel usage
        int fuelUsage = 0;
        for (int j = 0; j < crabCount; j++) {
            if (part1) {
                fuelUsage += abs(crabs[j] - i);
            } else {
                int distance = abs(crabs[j] - i);
                fuelUsage += ((distance + 1) * distance) / 2;
            }
        }
        if (fuelUsage < smallestFuelUsage) {
            smallestFuelUsage = fuelUsage;
        }
    }

    return smallestFuelUsage;
}

int main()
{
    FILE* f = fopen("../input.txt", "rb");
    int crabs[1024];
    int crabCount = 0;
    while (fscanf(f, "%d,", &crabs[crabCount++]) == 1);
    crabCount--;

    int smallestFuelUsagePt1 = calculateFuelUsage(crabs, crabCount, true);
    int smallestFuelUsagePt2 = calculateFuelUsage(crabs, crabCount, false);

    printf("Part 1: %d\nPart 2: %d\n", smallestFuelUsagePt1, smallestFuelUsagePt2);

    fclose(f);
    return 0;
}

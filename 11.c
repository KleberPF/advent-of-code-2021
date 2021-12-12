#include <stdio.h>
#include <string.h>

#include "utils.h"

#define SIZE 10
#define STEP_COUNT 100

void increaseEnergy(int octopuses[16][16])
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            octopuses[i][j]++;
        }
    }
}

// thought about allocating more memory and starting at (1, 1) but this will do
void flash(int octopuses[16][16], int i, int j)
{
    if (i - 1 >= 0) {
        octopuses[i - 1][j]++;
        if (j - 1 >= 0) {
            octopuses[i - 1][j - 1]++;
        }
        if (j + 1 < SIZE) {
            octopuses[i - 1][j + 1]++;
        }
    }
    if (j - 1 >= 0) { octopuses[i][j - 1]++; }
    if (j + 1 < SIZE) { octopuses[i][j + 1]++; }
    if (i + 1 < SIZE) {
        octopuses[i + 1][j]++;
        if (j - 1 >= 0) {
            octopuses[i + 1][j - 1]++;
        }
        if (j + 1 < SIZE) {
            octopuses[i + 1][j + 1]++;
        }
    }
}

// not the most efficient, but will do
int flashAll(int octopuses[16][16], bool flashed[16][16])
{
    int flashCount = 0;
    bool running = true;
    while (running) {
        running = false;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (octopuses[i][j] > 9 && !flashed[i][j]) {
                    flash(octopuses, i, j);
                    flashed[i][j] = true;
                    flashCount++;
                    running = true;
                }
            }
        }
    }

    // set octopuses that flashed to 0
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (flashed[i][j]) {
                octopuses[i][j] = 0;
            }
        }
    }

    // reset flashed array
    memset(flashed, 0, sizeof(bool) * 16 * 16);

    return flashCount;
}

bool isAllZeros(int octopuses[16][16])
{
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (octopuses[i][j] != 0) {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    FILE* f = fopen("../input.txt", "rb");
    char buffer[16][16];
    int octopuses[16][16];
    bool flashed[16][16];
    memset(flashed, false, sizeof(flashed));

    for (int i = 0; readStrFromLine(buffer[i], sizeof(buffer[0]), f); i++);

    // get int array
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            octopuses[i][j] = buffer[i][j] - '0';
        }
    }

    int flashCount = 0;
    bool running = true;
    for (int i = 0; running; ++i) {
        increaseEnergy(octopuses);
        flashCount += flashAll(octopuses, flashed);
        if (i + 1 == STEP_COUNT) {
            printf("Part 1: %d\n", flashCount);
        }
        // check if all zeros
        if (isAllZeros(octopuses)) {
            printf("Part 2: %d\n", i + 1);
            running = false;
        }
    }

    fclose(f);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

typedef enum rating {
    CO2,
    O2,
} Rating;

int findRating(int* numbers, int l, int r, int bitPos, Rating rating)
{
    while (l != r) {
        int offBitCount = 0;
        for (int i = l; i <= r; i++) {
            if (!((numbers[i] >> (bitPos - 1)) % 2)) {
                offBitCount++;
            } else {
                break;
            }
        }

        // check if all bits are equal
        if (offBitCount > 0 && offBitCount != r - l + 1) {
            bool cond = offBitCount > (r - l + 1) / 2;
            if (rating == CO2) {
                cond = !cond;
            }
            if (cond) {
                l += offBitCount;
            } else {
                r = l + offBitCount - 1;
            }
        }

        bitPos--;
    }

    return numbers[l];
}

int main()
{
    FILE* f = fopen("../input.txt", "rb");
    char numbers[1024][16];
    int numCount = 0;

    int setBitCount[16] = {0};
    for (; readStrFromLine(numbers[numCount], sizeof(numbers[numCount]), f); numCount++) {
        for (int i = 0; numbers[numCount][i] != 0; i++) {
            numbers[numCount][i] == '1' ? setBitCount[i]++ : setBitCount[i]--;
        }
    }
    int length = strlen(numbers[0]);

    // gamma and epsilon rate
    int gammaRate = 0;
    int epsilonRate = 0;
    for (int i = 0; i < length; i++) {
        gammaRate <<= 1;
        epsilonRate <<= 1;
        if (setBitCount[i] > 0) {
            gammaRate++;
        } else {
            epsilonRate++;
        }
    }

    printf("Part 1: %d\n", gammaRate * epsilonRate);

    // part 2
    int numbersInt[1024];
    for (int i = 0; i < numCount; i++) {
        numbersInt[i] = strToBin(numbers[i]);
    }

    // sort array
    qsort(numbersInt, numCount, sizeof(*numbersInt), compareInts);

    int l = 0;
    int r = numCount - 1;

    printf("Part 2: %d\n", findRating(numbersInt, l, r, length, CO2) *
                           findRating(numbersInt, l, r, length, O2));
}

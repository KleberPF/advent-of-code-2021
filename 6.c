#include <stdio.h>
#include <string.h>

unsigned long long getFishCount(int* input, int inputCount, int days)
{
    unsigned long long fishesPrev[9] = {0};
    unsigned long long fishes[9] = {0};

    for (int i = 0; i < inputCount; i++) {
        fishesPrev[input[i]]++;
    }

    for (int i = 0; i < days; i++) {
        memset(fishes, 0, sizeof(fishes));
        for (int j = 0; j < 9; j++) {
            if (fishesPrev[j] != 0) {
                if (j == 0) {
                    fishes[0] = 0;
                    fishes[6] = fishesPrev[0];
                    fishes[8] = fishesPrev[0];
                } else {
                    fishes[j - 1] += fishesPrev[j];
                }
            }
        }
        memcpy(fishesPrev, fishes, sizeof(fishes));
    }

    unsigned long long fishCount = 0;
    for (int i = 0; i < 9; i++) {
        fishCount += fishes[i];
    }

    return fishCount;
}

int main(void)
{
    FILE* f = fopen("input.txt", "r");
    int input[1024];
    int inputCount = 0;

    while (fscanf(f, "%d,", &input[inputCount++]) == 1)
        ;
    inputCount--;

    printf("Part 1: %llu\n", getFishCount(input, inputCount, 80));
    printf("Part 2: %llu\n", getFishCount(input, inputCount, 256));

    return 0;
}

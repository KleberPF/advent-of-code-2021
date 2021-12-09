#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "utils.h"

int main()
{
    FILE* f = fopen("../input.txt", "rb");
    char sequences[1024][10][8];
    char digits[1024][4][8];
    int digitsCount = 0;

    char line[128];
    while (readStrFromLine(line, sizeof(line), f)) {
        char* token = strtok(line + strcspn(line, "|") + 2, " ");
        int count = 0;
        do {
            strcpy(digits[digitsCount][count++], token);
        } while ((token = strtok(NULL, " ")));
        token = strtok(line, " ");
        count = 0;
        do {
            strcpy(sequences[digitsCount][count++], token);
        } while ((token = strtok(NULL, " ")));
        digitsCount++;
    }

    // part 1
    int uniqueCount = 0;
    for (int i = 0; i < digitsCount; i++) {
        for (int j = 0; j < 4; ++j) {
            int len = strlen(digits[i][j]);
            if (len == 2 || len == 3 || len == 4 || len == 7) {
                uniqueCount++;
            }
        }
    }
    printf("%d\n", uniqueCount);

    // part 2
    int total = 0;
    for (int i = 0; i < digitsCount; i++) {
        // count letters
        char solution[7] = {0};
        bool lettersFound[7] = {0};
        int letterCount[7] = {0};
        for (int j = 0; j < 10; j++) {
            int len = strlen(sequences[i][j]);
            for (int k = 0; k < len; k++) {
                letterCount[sequences[i][j][k] - 'a']++;
            }
        }

        // figure out c, e and f
        for (int j = 0; j < 7; ++j) {
            switch (letterCount[j]) {
                case 4:
                    solution[4] = 'a' + j;
                    lettersFound[j] = true;
                    break;
                case 6:
                    solution[5] = 'a' + j;
                    lettersFound[j] = true;
                    break;
                case 9:
                    solution[2] = 'a' + j;
                    lettersFound[j] = true;
                    break;
            }
        }

        // figure out b
        for (int j = 0; j < 10; j++) {
            int len = strlen(sequences[i][j]);
            if (len == 2) {
                if (sequences[i][j][0] == solution[2]) {
                    solution[1] = sequences[i][j][1];
                    lettersFound[sequences[i][j][1] - 'a'] = true;
                } else {
                    solution[1] = sequences[i][j][0];
                    lettersFound[sequences[i][j][0] - 'a'] = true;
                }
                break;
            }
        }

        // figure out a
        for (int j = 0; j < 7; j++) {
            if (letterCount[j] == 8) {
                if ('a' + j != solution[1]) {
                    solution[0] = 'a' + j;
                    lettersFound[j] = true;
                    break;
                }
            }
        }

        // figure out g
        for (int j = 0; j < 10; j++) {
            int len = strlen(sequences[i][j]);
            if (len == 4) {
                for (int k = 0; k < 4; k++) {
                    bool isIn = false;
                    for (int l = 0; l < 7; ++l) {
                        if (solution[l] == sequences[i][j][k]) {
                            isIn = true;
                            break;
                        }
                    }
                    if (!isIn) {
                        solution[6] = sequences[i][j][k];
                        lettersFound[sequences[i][j][k] - 'a'] = true;
                        goto found;
                    }
                }
            }
        }
        found:

        // figure out d
        for (int j = 0; j < 7; ++j) {
            if (!lettersFound[j]) {
                solution[3] = 'a' + j;
                break;
            }
        }

        // translate
        int number = 0;
        int mul = 1000;
        for (int j = 0; j < 4; ++j) {
            int len = strlen(digits[i][j]);
            for (int k = 0; k < len; ++k) {
                for (int l = 0; l < 7; ++l)
                    if (solution[l] == digits[i][j][k]) {
                        digits[i][j][k] = 'a' + l;
                        break;
                    }
            }

            /*
             * 0: 41    5: 44
             * 1: 8     6: 55
             * 2: 40    7: 10
             * 3: 34    8: 58
             * 4: 38    9: 47
             */
            int primes[7] = {2, 3, 5, 7, 11, 13, 17};
            int table[10] = {41, 8, 40, 34, 38, 44, 55, 10, 58, 47};
            int value = 0;

            for (int k = 0; k < len; ++k) {
                value += primes[digits[i][j][k] - 'a'];
            }
            for (int k = 0; k < 10; ++k) {
                if (table[k] == value) {
                    number += k * mul;
                    break;
                }
            }
            mul /= 10;
        }

        total += number;
    }

    printf("%d\n", total);

    fclose(f);
    return 0;
}

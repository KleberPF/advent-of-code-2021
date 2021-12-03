#ifndef ADVENT_OF_CODE_2021_UTILS_H
#define ADVENT_OF_CODE_2021_UTILS_H

#include <stdio.h>
#include <stdbool.h>

bool readIntFromLine(char* buffer, int length, FILE* f, int* value);

bool readStrFromLine(char* buffer, int length, FILE* f);

int getFileLength(FILE* f);

void readFileToBuffer(char* buffer, int length, FILE* f);

#endif //ADVENT_OF_CODE_2021_UTILS_H

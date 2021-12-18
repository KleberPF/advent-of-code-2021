#ifndef ADVENT_OF_CODE_2021_UTILS_H
#define ADVENT_OF_CODE_2021_UTILS_H

#include <stdio.h>
#include <stdbool.h>

bool readIntFromLine(char* buffer, int length, FILE* f, int* value);

bool readStrFromLine(char* buffer, int length, FILE* f);

int getFileLength(FILE* f);

void readFileToBuffer(char* buffer, int length, FILE* f);

unsigned long long strToBin(char* str);

int compareInts(const void* a, const void* b);

int compareUul(const void* a, const void* b);

int strRangeToBin(char* str, int l, int r);

void charToBin(char* stream, char c);

#endif //ADVENT_OF_CODE_2021_UTILS_H

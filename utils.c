#include "utils.h"

#include <stdlib.h>
#include <string.h>

bool readIntFromLine(char* buffer, int length, FILE* f, int* value)
{
    if (fgets(buffer, length, f)) {
        return sscanf(buffer, "%d", value);
    } else {
        return false;
    }
}

bool readStrFromLine(char* buffer, int length, FILE* f)
{
    char* result = fgets(buffer, length, f);
    if (result == NULL) { return false; }
    buffer[strcspn(buffer, "\n")] = 0;
    return true;
}

int getFileLength(FILE* f)
{
    fseek(f, 0, SEEK_END);
    int length = ftell(f);
    fseek(f, 0, SEEK_SET);

    return length;
}

void readFileToBuffer(char* buffer, int length, FILE* f)
{
    fread(buffer, 1, length, f);
    buffer[length] = 0;
}

unsigned long long strToBin(char* str)
{
    unsigned long long result = 0;
    for (; *str; str++) {
        result <<= 1;
        if (*str == '1') {
            result += 1;
        }
    }

    return result;
}

int compareInts(const void* a, const void* b)
{
    int arg1 = *(const int*) a;
    int arg2 = *(const int*) b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int compareUul(const void* a, const void* b)
{
    unsigned long long arg1 = *(const unsigned long long*) a;
    unsigned long long arg2 = *(const unsigned long long*) b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int strRangeToBin(char* str, int l, int r)
{
    char tmp = str[r];
    str[r] = 0;
    int result = strToBin(str + l);
    str[r] = tmp;

    return result;
}

void charToBin(char* stream, char c)
{
    char tmp[8] = {c};
    int value = strtol(tmp, NULL, 16);
    for (int i = 3; i >= 0; --i) {
        tmp[0] = ((value & (1 << i)) >> i) + '0';
        strcat(stream, tmp);
    }
}

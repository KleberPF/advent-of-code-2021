#include "utils.h"

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
    buffer[strcspn(buffer, "\r\n")] = 0;
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

int strToBin(char* str)
{
    int result = 0;
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

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

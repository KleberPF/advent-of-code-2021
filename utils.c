#include "utils.h"

bool readIntFromLine(char *buffer, int length, FILE *f, int *value)
{
    if (fgets(buffer, length, f)) {
        return sscanf(buffer, "%d", value);
    } else {
        return false;
    }
}

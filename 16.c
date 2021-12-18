#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

typedef struct packageValues {
    int versionSum;
    unsigned long long value;
} PackageValues;

PackageValues readPackage(char* stream, int* start, int end)
{
    PackageValues packageValues;
    packageValues.value = 0;
    // get version
    packageValues.versionSum = strRangeToBin(stream, *start, *start + 3);
    *start += 3;
    // get packet type
    int packetType = strRangeToBin(stream, *start, *start + 3);
    *start += 3;
    if (packetType == 4) {
        char tmp[128];
        tmp[0] = 0;
        bool running = true;
        while (running) {
            if (stream[*start] != '1') { running = false; }
            strncat(tmp, stream + *start + 1, 4);
            *start += 5;
        }
        packageValues.value += strToBin(tmp);
    } else {
        // read type id
        char typeId = stream[(*start)++];
        // get sub-packets count
        int subPacketsLen;
        PackageValues subPackets[128];
        int subPacketsCount = 0;
        if (typeId == '0') {
            subPacketsLen = strRangeToBin(stream, *start, *start + 15);
            *start += 15;
            int subPacketsEnd = *start + subPacketsLen;

            // read sub-packets
            while (*start < subPacketsEnd) {
                subPackets[subPacketsCount++] = readPackage(stream, start, subPacketsEnd);
            }
        } else if (typeId == '1') {
            subPacketsLen = strRangeToBin(stream, *start, *start + 11);
            *start += 11;
            while (subPacketsCount < subPacketsLen) {
                subPackets[subPacketsCount++] = readPackage(stream, start, end);
            }
        }

        // add version
        for (int i = 0; i < subPacketsCount; ++i) {
            packageValues.versionSum += subPackets[i].versionSum;
        }

        // process sub-packets
        switch (packetType) {
            case 0: // sum
                for (int i = 0; i < subPacketsCount; ++i) {
                    packageValues.value += subPackets[i].value;
                }
                break;
            case 1: // product
                packageValues.value = subPackets[0].value;
                for (int i = 1; i < subPacketsCount; ++i) {
                    packageValues.value *= subPackets[i].value;
                }
                break;
            case 2: // minimum
            {
                long long min = ULLONG_MAX;
                for (int i = 0; i < subPacketsCount; ++i) {
                    if (subPackets[i].value < min) {
                        min = subPackets[i].value;
                    }
                }
                packageValues.value = min;
                break;
            }
            case 3: // maximum
            {
                long long max = 0;
                for (int i = 0; i < subPacketsCount; ++i) {
                    if (subPackets[i].value > max) {
                        max = subPackets[i].value;
                    }
                }
                packageValues.value = max;
                break;
            }
            case 5: // greater than
                packageValues.value = subPackets[0].value > subPackets[1].value;
                break;
            case 6: // less than
                packageValues.value = subPackets[0].value < subPackets[1].value;
                break;
            case 7: // equal to
                packageValues.value = subPackets[0].value == subPackets[1].value;
                break;
        }
    }

    return packageValues;
}

int main()
{
    FILE* f = fopen("../input.txt", "rb");
    int fileLength = getFileLength(f);
    char* stream = malloc(2048);
    readFileToBuffer(stream, fileLength, f);
    char* binStream = malloc(6000);
    binStream[0] = 0;

    for (int i = 0; i < fileLength; ++i) {
        charToBin(binStream, stream[i]);
    }

    int start = 0;
    PackageValues packageValues = readPackage(binStream, &start, strlen(binStream));
    printf("Part 1: %d\n", packageValues.versionSum);
    printf("Part 2: %lld\n", packageValues.value);

    fclose(f);
    return 0;
}

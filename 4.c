#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

typedef struct boardData {
    int winNumber;
    int numbersToWin;
    int sumUnmarkedNumbers;
} BoardData;

int getNumbers(int* buffer, FILE* f)
{
    char numbers[512] = {0};
    char line[256] = {0};
    int numCount = 0;
    while (readStrFromLine(line, sizeof(line), f)) {
        if (strcmp(line, "") != 0) {
            strcat(numbers, line);

            char* token = strtok(numbers, ",");
            do {
                buffer[numCount++] = strtol(token, NULL, 10);
                token = strtok(NULL, ",");
            } while (token);
        } else {
            break;
        }
    }

    return numCount;
}

int getBoards(int boards[512][5][5], FILE* f)
{
    char line[64];
    int boardCount = 0;
    do {
        for (int i = 0; i < 5; i++) {
            readStrFromLine(line, sizeof(line), f);
            sscanf(line, "%d %d %d %d %d",
                   &boards[boardCount][i][0],
                   &boards[boardCount][i][1],
                   &boards[boardCount][i][2],
                   &boards[boardCount][i][3],
                   &boards[boardCount][i][4]);
        }
        boardCount++;
    } while (readStrFromLine(line, sizeof(line), f));

    return boardCount;
}

bool isBoardWon(bool board[5][5])
{
    // check rows
    for (int i = 0; i < 5; i++) {
        bool won = true;
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == false) {
                won = false;
                break;
            }
        }
        if (won) {
            return true;
        }
    }

    // check columns
    for (int j = 0; j < 5; j++) {
        bool won = true;
        for (int i = 0; i < 5; i++) {
            if (board[i][j] == false) {
                won = false;
                break;
            }
        }
        if (won) {
            return true;
        }
    }

    return false;
}

bool setNumberInBoard(int board[5][5], bool foundBoard[5][5], int number)
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == number) {
                foundBoard[i][j] = true;
                return true;
            }
        }
    }

    return false;
}

int sumOfUnmarkedNumbers(int board[5][5], bool foundBoard[5][5])
{
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (!foundBoard[i][j]) {
                sum += board[i][j];
            }
        }
    }

    return sum;
}

int main()
{
    FILE* f = fopen("../input.txt", "rb");

    // get bingo numbers
    int numbers[512];
    int numCount = getNumbers(numbers, f);

    // get bingo boards
    int boards[512][5][5];
    int boardCount = getBoards(boards, f);

    // keep found data
    bool foundBoards[512][5][5];
    memset(foundBoards, 0, sizeof(foundBoards));

    BoardData minBoard = {0, INT_MAX, 0};
    BoardData maxBoard = {0, INT_MIN, 0};

    for (int i = 0; i < boardCount; i++) {
        for (int j = 0; j < numCount; j++) {
            if (setNumberInBoard(boards[i], foundBoards[i], numbers[j])) {
                if (isBoardWon(foundBoards[i])) {
                    if (minBoard.numbersToWin > j) {
                        minBoard.numbersToWin = j;
                        minBoard.sumUnmarkedNumbers = sumOfUnmarkedNumbers(boards[i], foundBoards[i]);
                        minBoard.winNumber = numbers[j];
                    } else if (maxBoard.numbersToWin < j) {
                        maxBoard.numbersToWin = j;
                        maxBoard.sumUnmarkedNumbers = sumOfUnmarkedNumbers(boards[i], foundBoards[i]);
                        maxBoard.winNumber = numbers[j];
                    }
                    break;
                }
            }
        }
    }

    printf("Part 1: %d * %d = %d\n", minBoard.winNumber, minBoard.sumUnmarkedNumbers,
           minBoard.winNumber * minBoard.sumUnmarkedNumbers);
    printf("Part 2: %d * %d = %d\n", maxBoard.winNumber, maxBoard.sumUnmarkedNumbers,
           maxBoard.winNumber * maxBoard.sumUnmarkedNumbers);

    fclose(f);
    return 0;
}

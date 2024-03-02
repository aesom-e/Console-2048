#include <stdio.h>
#include <string.h>
#include "printTools.h"

#ifndef BOARD_H
#define BOARD_H

#ifndef max
int max(int a, int b) { if(a>b) return a; return b; }
#endif

typedef struct {
    int tiles[16];
} board;

board createBoard() {
    board ret;
    int i;
    for(i=0;i<16;i++) ret.tiles[i] = 0;
    return ret;
}

void addRandomPiece(board* boardIn) {
    int i, addition;
    char emptyTiles[16] = {0}, index = 0;
    // Fill emptyTiles with the indices of all empty tiles
    for(i=0;i<16;i++) if(boardIn->tiles[i] == 0) emptyTiles[index++] = i;
    if(rand() % 4 == 0) addition = 4;
    else addition = 2;
    boardIn->tiles[emptyTiles[rand() % index]] = addition;
}

int boardsAreEqual(board boardOne, board boardTwo) {
    int i;
    for(i=0;i<16;i++) if(boardOne.tiles[i] != boardTwo.tiles[i]) return 0;
    return 1;
}

int sizeOfNum(int num) {
    int count = 0;
    while(num >= 10) {
        count++;
        num /= 10;
    }
    return count;
}

// Prints a rainbow effect for tiles worth 2048+
void print2048OrMore(int num, int maxSize) {
    int i;
    char toPrint[32];
    const char* colours[7] = {(const char*)RED, (const char*)ORANGE, (const char*)YELLOW, (const char*)GREEN,
                              (const char*)BLUE, (const char*)PURPLE, (const char*)PINK};
    sprintf(toPrint, "[%d", num);
    for(i=0;i<maxSize-sizeOfNum(num);i++) strcat(toPrint, " ");
    strcat(toPrint, "]");
    for(i=0;i<strlen(toPrint);i++) {
        setColour(colours[i]);
        printf("%c", toPrint[i]);
    }
    setColour((const char*)WHITE);
}

void printBoard(board in) {
    int i, j, k, maxSize = 0;
    for(i=0;i<16;i++) maxSize = max(maxSize, sizeOfNum(in.tiles[i]));
    for(i=0;i<4;i++) {
        for(j=0;j<4;j++) {
            // Colour code the tiles
            switch(in.tiles[i * 4 + j]) {
                case 0:    setColour((const char*)GREY);       break;
                case 2:    setColour((const char*)WHITE);      break;
                case 4:    setColour((const char*)WHITE);      break;
                case 8:    setColour((const char*)WHITE);      break;
                case 16:   setColour((const char*)YELLOW);     break;
                case 32:   setColour((const char*)ORANGE);     break;
                case 64:   setColour((const char*)RED);        break;
                case 128:  setColour((const char*)GREEN);      break;
                case 256:  setColour((const char*)BLUE);       break;
                case 512:  setColour((const char*)PINK);       break;
                case 1024: setColour((const char*)PURPLE);     break;
                // If the tile >= 2048, this will run (assuming no error happened)
                default: print2048OrMore(in.tiles[i * 4 + j], maxSize); continue;
            }
            // Prints [(num)] but adds spaces to smaller numbers to make all tiles even
            // This works like this: [2  ] [16 ] [4  ] [128]
            // Because there needs to be 3 spaces for numbers extra spaces are appended to numbers that don't fully fill the space
            printf("[");
            if(in.tiles[i * 4 + j] != 0) printf("%d", in.tiles[i * 4 + j]);
            else printf(" ");
            for(k=0;k<maxSize-sizeOfNum(in.tiles[i * 4 + j]);k++) printf(" ");
            printf("] ");
            setColour((const char*)WHITE);
        }
        printf("\n");
    }
}

#endif
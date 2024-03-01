#include <stdio.h>
#include <string.h>
#include "printTools.h"

#ifndef BOARD_H
#define BOARD_H

#ifndef max
int max(int a, int b) { if(a>b) return a; return b; }
#endif

typedef struct {
    int pieces[16];
} board;

board createBoard() {
    board ret;
    int i;
    for(i=0;i<16;i++) ret.pieces[i] = 0;
    return ret;
}

void addRandomPiece(board* boardIn) {
    int i, addition;
    char emptyPieces[16] = {0}, index = 0;
    for(i=0;i<16;i++) if(boardIn->pieces[i] == 0) emptyPieces[index++] = i;
    if(rand() % 4 == 0) addition = 4;
    else addition = 2;
    boardIn->pieces[emptyPieces[rand() % index]] = addition;
}

int boardsAreEqual(board boardOne, board boardTwo) {
    int i;
    for(i=0;i<16;i++) if(boardOne.pieces[i] != boardTwo.pieces[i]) return 0;
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
    for(i=0;i<16;i++) maxSize = max(maxSize, sizeOfNum(in.pieces[i]));
    for(i=0;i<4;i++) {
        for(j=0;j<4;j++) {
            switch(in.pieces[i*4+j]) {
                case 0:    setColour((const char*)GREY);   break;
                case 2:    setColour((const char*)WHITE);  break;
                case 4:    setColour((const char*)WHITE);  break;
                case 8:    setColour((const char*)WHITE);  break;
                case 16:   setColour((const char*)YELLOW); break;
                case 32:   setColour((const char*)ORANGE); break;
                case 64:   setColour((const char*)RED);    break;
                case 128:  setColour((const char*)GREEN);  break;
                case 256:  setColour((const char*)BLUE);   break;
                case 512:  setColour((const char*)PINK);   break;
                case 1024: setColour((const char*)PURPLE); break;
                case 2048: print2048OrMore(2048, maxSize);      continue;
            }
            printf("[");
            if(in.pieces[i*4+j] != 0) printf("%d", in.pieces[i*4+j]);
            else printf(" ");
            for(k=0;k<maxSize-sizeOfNum(in.pieces[i*4+j]);k++) printf(" ");
            printf("] ");
            setColour((const char*)WHITE);
        }
        printf("\n");
    }
}

#endif
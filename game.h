#include <stdlib.h>
#include "board.h"
#include "move.h"
#include "input.h"
#include "printTools.h"

#ifndef GAME_H
#define GAME_H

typedef enum {
    EXIT,
    SUCCESS,
    FAILURE,
    LOSE,
    WIN
} returnCode;

int hasLost(board boardIn) {
    int i;
    for(i=0;i<16;i++) {
        if(boardIn.tiles[i] == 0) return 0;
    }

    // Check if there are any adjacent tiles that are the same value
    for(i=0;i<16;i++) {
        // Check for the tile above i
        if(i > 3) {
            if(boardIn.tiles[i] == boardIn.tiles[i-4]) return 0;
        }
        // Check for the tile below i
        if(i < 12) {
            if(boardIn.tiles[i] == boardIn.tiles[i+4]) return 0;
        }
        // Check for the tile to the left of i
        if(i % 4) {
            if(boardIn.tiles[i] == boardIn.tiles[i-1]) return 0;
        }
        // Check for the tile to the right of i
        if(i % 4 != 3) {
            if(boardIn.tiles[i] == boardIn.tiles[i+1]) return 0;
        }
    }

    return 1;
}

int hasWon(board boardIn) {
    int i;
    for(i=0;i<16;i++) {
        if(boardIn.tiles[i] == 2048) return 1;
    }
    return 0;
}

void printState(board boardIn) {
    clearConsole();
    printBoard(boardIn);
    printf("\n");
}

returnCode handleInput(board* boardIn, char userInput) {
    board testBoard = *boardIn;
    switch(userInput) {
        case 'q':
            return EXIT;
        case 'w':
            moveBoard(&testBoard, UP);
            if(boardsAreEqual(testBoard, *boardIn)) return FAILURE;
            moveBoard(boardIn, UP);
            break;
        case 'a':
            moveBoard(&testBoard, LEFT);
            if(boardsAreEqual(testBoard, *boardIn)) return FAILURE;
            moveBoard(boardIn, LEFT);
            break;
        case 's':
            moveBoard(&testBoard, DOWN);
            if(boardsAreEqual(testBoard, *boardIn)) return FAILURE;
            moveBoard(boardIn, DOWN);
            break;
        case 'd':
            moveBoard(&testBoard, RIGHT);
            if(boardsAreEqual(testBoard, *boardIn)) return FAILURE;
            moveBoard(boardIn, RIGHT);
            break;
        default: return FAILURE;
    }
    return SUCCESS;
}

returnCode playWithInput(board* boardIn, char userInput) {
    if(handleInput(boardIn, userInput) == EXIT) return EXIT;
    addRandomPiece(boardIn);
    if(hasLost(*boardIn)) return LOSE;
    if(hasWon(*boardIn)) return WIN;
    return SUCCESS;
}

returnCode play(board* boardIn) {
    char userInput = input();
    switch(handleInput(boardIn, userInput)) {
        case EXIT:
            printf("\nExiting\n");
            return EXIT;
        case FAILURE:
            // I feel as though this needs explanation. If the user pressed a key that does nothing, FAILURE is returned
            // Returning SUCCESS keeps the program going so since we don't exit, this returns SUCCESS
            return SUCCESS;
    }
    addRandomPiece(boardIn);
    printState(*boardIn);
    if(hasLost(*boardIn)) {
        printf("\nYou lost\n");
        return LOSE;
    }
    if(hasWon(*boardIn)) {
        printf("\nYou won\n");
        return WIN;
    }
    return SUCCESS;
}

#endif
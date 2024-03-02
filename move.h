#include "board.h"

#ifndef MOVE_H
#define MOVE_H

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} direction;

void combinePieces(board* boardIn, direction directionIn) {
    int i, j, k;
    switch (directionIn) {
        case UP:
            for(i=0;i<3;i++) {
                for(j=0;j<4;j++) {
                    if(boardIn->tiles[i * 4 + j] != 0) {
                        for(k=i+1;k<4;k++) {
                            if(boardIn->tiles[k * 4 + j] != 0) {
                                if(boardIn->tiles[i * 4 + j] == boardIn->tiles[k * 4 + j]) {
                                    boardIn->tiles[i * 4 + j] *= 2;
                                    boardIn->tiles[k * 4 + j] = 0;
                                }
                                break;
                            }
                        }
                    }
                }
            }
            break;
        case DOWN:
            for(i=3;i>0;i--) {
                for(j=0;j<4;j++) {
                    if(boardIn->tiles[i * 4 + j] != 0) {
                        for(k=i-1;k>=0;k--) {
                            if(boardIn->tiles[k * 4 + j] != 0) {
                                if(boardIn->tiles[i * 4 + j] == boardIn->tiles[k * 4 + j]) {
                                    boardIn->tiles[i * 4 + j] *= 2;
                                    boardIn->tiles[k * 4 + j] = 0;
                                }
                                break;
                            }
                        }
                    }
                }
            }
            break;
        case LEFT:
            for(i=0;i<4;i++) {
                for(j=0;j<3;j++) {
                    if(boardIn->tiles[i * 4 + j] != 0) {
                        for(k=j+1;k<4;k++) {
                            if(boardIn->tiles[i * 4 + k] != 0) {
                                if(boardIn->tiles[i * 4 + j] == boardIn->tiles[i * 4 + k]) {
                                    boardIn->tiles[i * 4 + j] *= 2;
                                    boardIn->tiles[i * 4 + k] = 0;
                                }
                                break;
                            }
                        }
                    }
                }
            }
            break;
        case RIGHT:
            for(i=0;i<4;i++) {
                for(j=3;j>0;j--) {
                    if(boardIn->tiles[i * 4 + j] != 0) {
                        for(k=j-1;k>=0;k--) {
                            if(boardIn->tiles[i * 4 + k] != 0) {
                                if(boardIn->tiles[i * 4 + j] == boardIn->tiles[i * 4 + k]) {
                                    boardIn->tiles[i * 4 + j] *= 2;
                                    boardIn->tiles[i * 4 + k] = 0;
                                }
                                break;
                            }
                        }
                    }
                }
            }
            break;
    }
}

void moveBoardRaw(board* boardIn, direction directionIn) {
    int i, j, k;
    for(i=0;i<4;i++) {
        switch(directionIn) {
            case UP:
                for(j=1;j<4;j++) {
                    for(k=0;k<4;k++) {
                        if(boardIn->tiles[(j - 1) * 4 + k] == 0) {
                            boardIn->tiles[(j - 1) * 4 + k] = boardIn->tiles[j * 4 + k];
                            boardIn->tiles[j * 4 + k] = 0;
                        }
                    }
                }
                break;
            case DOWN:
                for(j=0;j<3;j++) {
                    for(k=0;k<4;k++) {
                        if(boardIn->tiles[(j + 1) * 4 + k] == 0) {
                            boardIn->tiles[(j + 1) * 4 + k] = boardIn->tiles[j * 4 + k];
                            boardIn->tiles[j * 4 + k] = 0;
                        }
                    }
                }
                break;
            case LEFT:
                for(j=0;j<4;j++) {
                    for(k=1;k<4;k++) {
                        if(boardIn->tiles[j * 4 + (k - 1)] == 0) {
                            boardIn->tiles[j * 4 + (k - 1)] = boardIn->tiles[j * 4 + k];
                            boardIn->tiles[j * 4 + k] = 0;
                        }
                    }
                }
                break;
            case RIGHT:
                for(j=0;j<4;j++) {
                    for(k=0;k<3;k++) {
                        if(boardIn->tiles[j * 4 + (k + 1)] == 0) {
                            boardIn->tiles[j * 4 + (k + 1)] = boardIn->tiles[j * 4 + k];
                            boardIn->tiles[j * 4 + k] = 0;
                        }
                    }
                }
                break;
        }
    }
}

void moveBoard(board* boardIn, direction directionIn) {
    moveBoardRaw(boardIn, directionIn);
    combinePieces(boardIn, directionIn);
    moveBoardRaw(boardIn, directionIn);
}


#endif
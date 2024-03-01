#include "init.h"
#include "board.h"
#include "move.h"
#include "game.h"

int main() {
   init();
   clearConsole();
   board gameBoard = createBoard();
   addRandomPiece(&gameBoard);
   printBoard(gameBoard);
   while(play(&gameBoard) == SUCCESS);
}
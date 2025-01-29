/*

Header file defining board functions
This represents the core loop of updating the board, and checking for collisions
If a collision is present, lock the piece and resrart with a new piece

*/

#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>


void setUpBoard(int boardHeight, int boardWidth, int board[boardHeight][boardWidth]);

bool checkIfPieceFits(int sizeX, int sizeY, int pieceArr[sizeX][sizeY], int rotation, int boardX, int boardY, int boardHeight, int boardWidth, int boardArr[boardHeight][boardWidth]);

void lockPiece(int sizeX, int sizeY, int pieceArr[sizeX][sizeY], int boardHeight, int boardWidth, int boardArr[boardHeight][boardWidth], int currentXPos, int currentYPos);

void print2dArray(int sx, int sy, int array[sx][sy]);

int checkUpdatedFullLines(int boardHeight, int boardWidth, int board[boardHeight][boardWidth]);

void newPiece(int sizeX, int sizeY, int piece[sizeX][sizeY], int random);
#endif
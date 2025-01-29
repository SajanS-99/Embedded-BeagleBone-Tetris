/*

Set of functions to send the current board and piece to the 8 bu 8 led matrix
This is achieved by copying the board, reading the current board state to an unsgined char row by row
splitting up the char array in half
and sending it the the led matrices

*/
#ifndef GAMETOMATRIX_H
#define GAMETOMATRIX_H

int binaryToDecimal(int len, int arr[]);

void prepareCopyOfBoard(int sizeX, int sizeY, int pieceArr[sizeX][sizeY], int boardHeight, int boardWidth, int boardArr[boardHeight][boardWidth], int currentXPos, int currentYPos, int copyBoard[boardHeight][boardWidth], int copyRotate[boardWidth][boardHeight]);

void writeToMatrix(int boardHeight, int boardWidth, int copyBoard[boardWidth][boardHeight], int i2cFileDesc, int i2cFileDesc2);

void prepareCharArray(unsigned char charArray[], int boardWidth, int boardHeight, int binaryArray[boardWidth][boardHeight]);

void splitArray(int fullWidth, int fullHeight, int fullArray[fullWidth][fullHeight], int leftHalf[fullWidth/2][fullHeight], int rightHalf[fullWidth/2][fullHeight]);

unsigned char rightRotateBy1(unsigned char charToShift);

#endif
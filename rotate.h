/*

Header file for functiosn to help rotate the current piece, and board for sending to 8 by 8
led matrix

*/

#ifndef ROTATE_H
#define ROTATE_H


int checkRotateIndex(int xPosPiece, int yPosPiece, int rotation, int sizeX, int sizeY, int pieceArray[][sizeY]);

void updateRotate(int rotation, int sizeX, int sizeY, int pieceArray[][sizeY]);

void transpose(int sizeX, int sizeY, int array[][sizeY], int arrayToWrite[][sizeX]);

void reverseArray(int sizeY, int arrayRow[]);

// no rotate left for function
void updataRotateNonSquare(int sizeX, int sizeY, int array[][sizeY], int arrayToWrite[][sizeX]);
#endif
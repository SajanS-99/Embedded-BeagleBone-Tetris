#include "rotate.h"
#include <stdio.h>

// only eorks for n by n arrays, not n by m
// rotates the piece by shifting collumns and rows
void updateRotate(int rotation, int sizeX, int sizeY, int pieceArray[][sizeY]){

    int tempArray[sizeX][sizeY];
    //copy into array in case of overwrites
    for(int i = 0; i < sizeX; i++){
        for (int j = 0; j < sizeY; j++){
            tempArray[i][j] = pieceArray[i][j]; 
        }
    }

    switch(rotation){

        case 0:

            // do nothing
            break;
        //right
        case 1:
            // converts the rows of the original array into collumns for new
            // ie rotate by 90 degrees/right once
            for (int i = 0; i < sizeX; i++){
                for (int j = 0; j < sizeY; j++){
                    pieceArray[j][sizeX-i-1] = tempArray[i][j]; 
                }
            }
            break;
        //left
        case 2:
            //rotates by -90 degrees, ie rotate left
            for (int i = 0; i < sizeX; i++){
                for (int j = 0; j < sizeY; j++){
                    pieceArray[sizeY-j-1][i] = tempArray[i][j]; 
                }
            }
            break;

        default:

            printf("ERROR IN UPDATE ROTATE FUNCTION!\n");
            break;
    }
}

// acts if the piece is already rotated, and then checks the index whwre the piece is theortically
// rotated to get it's new index
int checkRotateIndex(int xPosPiece, int yPosPiece, int rotation, int sizeX, int sizeY, int pieceArray[][sizeY]){

    int rotatedIndex = 0;

    switch(rotation){

        case 0:

            //check no rotate
            rotatedIndex = pieceArray[xPosPiece][yPosPiece];
            break;

        case 1:

            //check right rotate
            //acts as if it was already right rotatated, and rotates left to check
            //original spots
            // if og spot is 1, then right rotated spot would also be 1
            rotatedIndex = pieceArray[sizeY-yPosPiece-1][xPosPiece];
          //  rotatedIndex = pieceArray[yPosPiece][sizeX-xPosPiece-1];
            break;

        case 2:

            //check left rotate
            rotatedIndex = pieceArray[yPosPiece][sizeX-xPosPiece-1];
            break;

        default:

            printf("WRONG ROTATION IN CHECK ROATION INDEX FUNCTION\n");
            break;
    }

    return rotatedIndex;


}

// does a matrix transpose 
void transpose(int sizeX, int sizeY, int array[][sizeY], int arrayToWrite[][sizeX]){

    for (int i = 0; i < sizeY; i++){
        for (int j = 0; j < sizeX; j++){
            arrayToWrite[i][j] = array[j][i];
        }
    }
}
//reverse an array
void reverseArray(int sizeY, int arrayRow[]){

    for (int i = 0; i < sizeY/2; i++){
        int temp = arrayRow[i];
        arrayRow[i] = arrayRow[sizeY -i - 1];
        arrayRow[sizeY -i -1] = temp;
    }

}
// no rotate left, only right
// transposing an array and reversing each row leads to a 90* rotation
void updataRotateNonSquare(int sizeX, int sizeY, int array[][sizeY], int arrayToWrite[][sizeX]){

    transpose(sizeX,sizeY,array,arrayToWrite);

    for (int i = 0; i < sizeY; i++){
        reverseArray(sizeX,arrayToWrite[i]);
    }


}
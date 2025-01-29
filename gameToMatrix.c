#include "gameToMatrix.h"
#include <stdio.h>
#include <math.h>
#include "initializeMatrix.h"
#include "board.h"
#include "rotate.h"

//assumes arr is only 1 or 0
//converts the board of 1/0's to deciaml so it can be assigned as a char
int binaryToDecimal(int len, int arr[]){

    int sum = 0;

    for (int i = 0; i < len; i++){
        sum = sum + ( arr[i] * pow(2,len-i-1));
    }

    return sum;

}

//copies original board as to not create conflict with it
//also adds the current piece position to the copied board for later
//also rotates for later
void prepareCopyOfBoard(int sizeX, int sizeY, int pieceArr[sizeX][sizeY], int boardHeight, int boardWidth, int boardArr[boardHeight][boardWidth], int currentXPos, int currentYPos, int copyBoard[boardHeight][boardWidth], int copyRotate[boardWidth][boardHeight]){
  
    for (int i = 0; i < boardHeight; i++){
        for (int j = 0; j < boardWidth; j++){
            copyBoard[i][j] = boardArr[i][j];
        }
    }
    //locks the current piece to copy board
    lockPiece(sizeX,sizeY,pieceArr,boardHeight,boardWidth,copyBoard,currentXPos,currentYPos);
    //rotate for led matrix
    updataRotateNonSquare(boardHeight,boardWidth,copyBoard,copyRotate);
        
}
//writes copied board to leds
void writeToMatrix(int boardHeight, int boardWidth, int copyBoard[boardWidth][boardHeight], int i2cFileDesc, int i2cFileDesc2){

    
    int strippedBoard[boardWidth-2][boardHeight-2];

    int a = 0;
    int b = 0;
    // strips the board of boundaries of 1/remove grid
    for (int i = 1; i < boardWidth-1; i++){
        for (int j = 1; j < boardHeight-1; j++){
            strippedBoard[a][b] = copyBoard[i][j];
            b++;
        }
        a++;
        b=0;
    }

   

    int strippedWidth = boardWidth-2;
    int strippedHeight = boardHeight-2;

    unsigned char bottomHalf[16];
    unsigned char topHalf[16];

    int leftHalf[strippedWidth][strippedHeight/2];
    int rightHalf[strippedWidth][strippedHeight/2];
    // split the stripped board into 2
    splitArray(strippedWidth,strippedHeight,strippedBoard,leftHalf, rightHalf);
    // write the 2 halves into char arrays
    prepareCharArray(bottomHalf, strippedWidth, strippedHeight, leftHalf);
    prepareCharArray(topHalf, strippedWidth, strippedHeight, rightHalf);




    // writes the boards to the leds
    writeI2cReg(i2cFileDesc, 0x00, topHalf);

    writeI2cReg(i2cFileDesc2, 0x00, bottomHalf);


    

}

// goes row by row to convert to char and assign it to the new char row
void prepareCharArray(unsigned char charArray[], int boardWidth, int boardHeight, int binaryArray[boardWidth][boardHeight/2]){
  
     for (int i = 0; i < boardWidth*2; i++){
        if (i % 2 == 1){
            charArray[i] = binaryToDecimal(boardWidth, binaryArray[(i-1)/2]);
        } else {
            charArray[i] = 0;
        }
     }

     for (int i = 1; i < 16; i+=2){
        charArray[i] = rightRotateBy1(charArray[i]);
     }
}

//splits array into two halves
void splitArray(int fullWidth, int fullHeight, int fullArray[fullWidth][fullHeight], int leftHalf[fullWidth][fullHeight/2], int rightHalf[fullWidth][fullHeight/2]){

    for (int i = 0; i < fullWidth; i++){
        for (int j = 0; j < fullHeight/2; j++){
            leftHalf[i][j] = fullArray[i][j];
        }
    }


   
 
    for (int i = 0; i < fullWidth; i++){
        for (int j = fullHeight/2; j < fullHeight; j++){
            // -8 to not go out of bounds
            rightHalf[i][j-8] = fullArray[i][j];
     
        }
    }



}

//rotates bitwise by 1, for led matrix rotation error
unsigned char rightRotateBy1(unsigned char charToShift){
    //actually right rotate, too lazy to change rn
    return (charToShift >> 1 | charToShift << 7);
} 